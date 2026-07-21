# What is AI Engineering?

AI engineering is the practice of building software around large language models, wiring a model up to memory, tools, retrieval, and other models so it can do more than answer a single prompt in isolation. The model itself is usually someone else's product, an API call away, the actual engineering work is in the scaffolding around it.

That scaffolding has to answer several separate questions, how multiple steps or agents get coordinated, how a model answers using information it was never trained on, how a model gets steered without touching its weights at all, how a model's own weights get adapted to a new task instead, how those weights get represented in fewer bits, and how the result actually gets served once training is done.

Each file in this directory takes on one of those questions, since the answers do not overlap enough to be treated as one topic:

- [orchestration-frameworks.md](orchestration-frameworks.md) answers how multi-step LLM workflows and multi-agent systems get coordinated.
- [rag.md](rag.md) answers how a model answers using information it was never trained on.
- [in-context-learning.md](in-context-learning.md) answers how a model gets steered toward a task through the prompt alone, without touching its weights.
- [finetuning.md](finetuning.md) answers how a model's own weights get adapted to a new task.
- [quantization.md](quantization.md) answers how those weights get represented in fewer bits without losing too much quality.
- [inference-engines.md](inference-engines.md) answers how the result actually gets served once training or fine-tuning is done.
