# System Design Roadmap

This directory archives system design notes topic by topic, each one covering the underlying concept plus a grounding in the real systems that implement it. The topics build roughly bottom-up, from how a request reaches a server at all, to how that server stores, caches, and communicates data, to the infrastructure it all runs on.

## Suggested order

1. [networking](networking/dns.md) covering DNS, load balancing, reverse proxies, and CDNs. How a request finds and reaches a server in the first place, before anything else in this list matters.
2. [database](database/database.md) explaining the SQL versus NoSQL split, plus data warehousing, full-text search, and distributed ID generation. Where most application data actually lives.
3. [caching](caching/caching.md) walking through placement, eviction, invalidation, and the engines that implement it. The layer that sits in front of a database to avoid redoing expensive work.
4. [messaging](messaging/messaging.md) laying out queues, pub-sub, and the brokers that implement them. How services talk to each other without a direct, synchronous call.
5. [storage](storage/object-storage.md) describing blob and object storage, distinct from the structured, queryable data a database holds.
6. [api](api/api.md) breaking down request-response styles, real-time protocols, webhooks, rate limiting, auth, and the other concerns at the request boundary. The contract a system exposes to whoever consumes it.
7. [cloud](cloud/cloud.md) going over what a cloud platform actually provides, and how the major providers compare.

## How each topic is organized

Every topic directory follows the same shape, a theory file explaining the underlying concept, plus one or more files grounding that theory in the real tools and systems that implement it, Kafka and RabbitMQ for messaging, Redis and Memcached for caching, and so on. The goal throughout is to know not just what a concept is, but which real system to reach for and why, and what gets traded away for that choice.
