# What is Quantization?

Model weights are normally stored as 16-bit or 32-bit floating point numbers. Quantization represents them using fewer bits instead, 8-bit, 4-bit, sometimes lower, cutting memory and compute cost at the price of some numerical precision. The same weight matrix that needs 14 GB at 16-bit precision can often fit in under 4 GB at 4-bit, without a proportional loss in output quality if the quantization scheme is chosen carefully.

# The shared problem

Every quantization method exists to answer the same underlying need, representing a model's weights in fewer bits while losing as little output quality as possible, and deciding how much calibration effort that compression is worth.

Many methods have been built to answer that problem, but four are worth knowing well, GPTQ, AWQ, GGUF, and bitsandbytes, each trading calibration effort against deployment target in a different way.

Following the same 7B checkpoint through each of these four pipelines is the clearest way to see where they actually differ, not in the bit-width they land on, most of them target 4-bit, but in what has to happen before that checkpoint can be used at all, and where it ends up running.

# GPTQ

GPTQ quantizes a model layer by layer after training is done, using a calibration dataset to solve for the quantized weights that minimize the error introduced in that layer's output, rather than just rounding each weight independently.

```mermaid
flowchart LR
    W[Full-precision weights] --> C[Calibration data pass]
    C --> L[Layer-by-layer reconstruction]
    L --> Q[Quantized weights]
```

Calibration-driven, layer-by-layer reconstruction is the mechanism.

- A small calibration dataset, a few hundred samples, is run through the model once to capture how each layer actually behaves, rather than quantizing purely from the weight values alone.
- Quantization is solved one layer at a time, using the previous layer's already-quantized output as input, so later layers compensate for error introduced earlier.
- GPTQ typically targets 4-bit or 3-bit weights for GPU inference, paired with a kernel that dequantizes on the fly during the forward pass.

Turning the 7B checkpoint into a GPTQ model means running it through that calibration pass once, offline, before it is ever served.

```python
from auto_gptq import AutoGPTQForCausalLM, BaseQuantizeConfig

quantize_config = BaseQuantizeConfig(bits=4, group_size=128)
model = AutoGPTQForCausalLM.from_pretrained("base-model", quantize_config)
model.quantize(calibration_dataset)
model.save_quantized("base-model-gptq-4bit")
```

What comes out the other side is a separate, already-quantized checkpoint, ready to be loaded straight onto a GPU for serving. That calibration pass takes real compute time and a representative dataset, and quantizing blind without one would not reach the same accuracy.

# AWQ

AWQ, activation-aware weight quantization, observes that a small fraction of weight channels matter disproportionately to output quality, the ones that see large activation magnitudes, and protects exactly those channels from precision loss while quantizing the rest more aggressively.

```mermaid
flowchart LR
    W[Full-precision weights] --> A[Observe activation magnitudes]
    A --> S[Identify salient channels]
    S --> Q[Quantize non-salient channels harder]
```

Protecting salient channels, rather than reconstructing layer by layer, is what its conventions revolve around.

- Salience is measured by activation magnitude, not weight magnitude, since a large activation flowing through a small weight can still dominate the output.
- Rather than storing protected channels at a different bit-width, AWQ rescales the whole channel so the standard quantization grid preserves more precision on it automatically.
- Because it does not solve a layer-by-layer reconstruction problem, AWQ quantizes faster than GPTQ for a comparable quality level.

The same 7B checkpoint goes through a comparable offline step here, just a lighter one.

```python
from awq import AutoAWQForCausalLM

model = AutoAWQForCausalLM.from_pretrained("base-model")
model.quantize(tokenizer, quant_config={"zero_point": True, "q_group_size": 128, "w_bit": 4})
model.save_quantized("base-model-awq-4bit")
```

The output is, again, a separate quantized checkpoint meant for GPU serving, generally holding up as well as or better than GPTQ's at the same bit-width for less calibration compute. It is a newer format, though, with less universal support across inference engines than GPTQ.

# GGUF

GGUF is the quantization and packaging format used by llama.cpp, built around block-wise quantization, weights are grouped into small blocks and each block gets its own scaling factor, rather than one scale for an entire tensor.

```mermaid
flowchart LR
    W[Full-precision weights] --> B[Split into blocks]
    B --> S[Per-block scale factor]
    S --> Q[Quantized block]
```

Portability and block-wise scaling are the design center.

- Naming like Q4_K_M encodes the bit-width, four bits, and the specific quantization variant, K-quant, medium, each variant trading a bit more size for a bit more accuracy.
- Block-wise scaling keeps outlier weights within one block from distorting the whole tensor's precision, at the cost of storing a scale factor per block.
- GGUF bundles the quantized weights with model metadata and tokenizer information into a single portable file, which is why llama.cpp and Ollama both load it directly.

The same checkpoint converts to a single portable file here, instead of a GPU-serving checkpoint.

```bash
python convert_hf_to_gguf.py base-model/ --outfile model.gguf --outtype q4_k_m
```

That one `.gguf` file is what `inference-engines.md` covers llama.cpp and Ollama loading directly, built for portability and CPU-friendly inference rather than squeezing out the last bit of GPU throughput, which is why GPTQ and AWQ remain more common for pure GPU-server deployments.

# bitsandbytes

bitsandbytes is the quantization library behind QLoRA, providing on-the-fly quantization that loads a model straight into 4-bit or 8-bit precision inside a standard Hugging Face transformers pipeline, without a separate offline conversion step.

```mermaid
flowchart LR
    W[Full-precision checkpoint] --> L[Load with BitsAndBytesConfig]
    L --> Q[Quantized in memory, 4-bit or 8-bit]
```

Dynamic, load-time quantization is what its conventions are built around.

- Quantization happens at load time, directly inside `from_pretrained`, rather than requiring a separately produced quantized checkpoint file.
- NF4, normalized float 4-bit, is the default 4-bit type, chosen to match the roughly normal distribution pretrained weights tend to follow.
- Because quantization is dynamic and library-integrated rather than a fixed file format, it is the natural fit for QLoRA, where the base model needs to be quantized specifically to make room for training the LoRA adapter on top of it.

This is the one pipeline in this file with no separate offline step at all. The original 7B checkpoint is loaded directly, and quantization happens in the same call.

```python
from transformers import AutoModelForCausalLM, BitsAndBytesConfig

bnb_config = BitsAndBytesConfig(load_in_4bit=True, bnb_4bit_quant_type="nf4", bnb_4bit_compute_dtype="bfloat16")
model = AutoModelForCausalLM.from_pretrained("base-model", quantization_config=bnb_config)
```

No new file is ever produced, the quantized weights exist only in memory for that process. That is exactly why QLoRA builds on bitsandbytes rather than a pre-quantized format, the whole point is quantizing the base model on the fly to make room for a training run, not producing a checkpoint to hand off elsewhere.

# How to choose

GPTQ fits a GPU deployment where a calibration dataset is available and squeezing out maximum accuracy at 4-bit matters enough to justify an offline quantization step.

AWQ fits the same GPU-deployment case as GPTQ, when a faster quantization process or slightly better retained quality at the same bit-width outweighs GPTQ's slightly wider tooling support.

GGUF fits running a model with llama.cpp or Ollama, on a CPU, a laptop, or any environment without a dedicated GPU.

bitsandbytes fits fine-tuning, especially QLoRA, or any case where quantizing on the fly at load time is more convenient than maintaining a separately quantized checkpoint.

# What gets traded away

GPTQ trades away quantization speed for accuracy, the calibration and layer-by-layer reconstruction process takes real time compared to simpler methods.

AWQ trades away the widest tooling support, it is newer and not every inference engine or checkpoint hosting convention treats it as the default the way GPTQ often is.

GGUF trades away peak GPU throughput for portability, it is not the format of choice for a GPU server trying to maximize concurrent request throughput.

bitsandbytes trades away the calibration-tuned accuracy of GPTQ or AWQ for the convenience of quantizing on the fly with no offline step.
