# What is an API?

An API, short for application programming interface, is the contract a system exposes to whoever needs to use it, another service, a mobile app, a third-party developer, without exposing how that system works internally. Whatever sits behind the contract can change freely, as long as the contract itself holds.

That contract has to answer several separate questions, how a single request-and-response exchange is shaped, and how a consumer finds out about something as it happens rather than asking repeatedly.

Each of those questions gets its own file in this directory, since the answers do not overlap enough to be treated as one topic:

- [request-response.md](request-response.md) answers how a single request-and-response exchange is shaped.
- [real-time.md](real-time.md) and [webhooks.md](webhooks.md) answer how a consumer finds out about something as it happens, rather than asking repeatedly.
