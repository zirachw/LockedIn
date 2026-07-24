# What is AI Engineering?

AI engineering is the practice of building software around large language models, wiring a model up to memory, tools, retrieval, and other models so it can do more than answer a single prompt in isolation. The model itself is usually someone else's product, an API call away, the actual engineering work is in the scaffolding around it.

That scaffolding has to answer several separate questions, how a model gets steered without touching its weights at all, how a model answers using information it was never trained on, how a model's own weights get adapted to a new task instead, how those weights get represented in fewer bits, how the result actually gets served once training is done, and how multiple such calls get coordinated into one task.

Each file in this directory takes on one of those questions, since the answers do not overlap enough to be treated as one topic. Suggested order:

1. [in-context-learning.md](in-context-learning.md) explaining how a model gets steered toward a task through the prompt alone, without touching its weights.
2. [rag.md](rag.md) walking through how a model answers using information it was never trained on.
3. [fine-tuning.md](fine-tuning.md) describing how a model's own weights get adapted to a new task instead.
4. [quantization.md](quantization.md) breaking down how those weights get represented in fewer bits without losing too much quality.
5. [inference-engines.md](inference-engines.md) going over how the result actually gets served once training or fine-tuning is done.
6. [harness.md](harness.md) unpacking how calls into any of the above get coordinated into one task, and how that coordination becomes a single agent's own running loop, tying the rest of this list together in practice.
