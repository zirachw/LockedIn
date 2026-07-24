# What is an API?

An API, short for application programming interface, is the contract a system exposes to whoever needs to use it, another service, a mobile app, a third-party developer, without exposing how that system works internally. Whatever sits behind the contract can change freely, as long as the contract itself holds.

That contract has to answer far more than just the shape of a request and response. It has to say how a consumer finds out about something as it happens, how much traffic it's willing to accept from one caller, whether a timestamp or a retry can actually be trusted, and who's allowed to do what once identity itself is settled.

Each of those questions gets its own file in this directory, since the answers do not overlap enough to be treated as one topic. Suggested order:

1. [request-response.md](request-response.md) covering how a single request-and-response exchange is shaped, SOAP through tRPC. The foundation everything else in this list builds on.
2. [real-time.md](real-time.md) and [webhooks.md](webhooks.md) explaining how a consumer finds out about something as it happens, rather than asking repeatedly.
3. [rate-limiting.md](rate-limiting.md) walking through how much traffic one caller is allowed to send before the API pushes back.
4. [server-time.md](server-time.md) laying out why a client's own clock or timestamp can never be trusted on its own.
5. [idempotency.md](idempotency.md) describing how a retried request avoids repeating a side effect like a duplicate charge.
6. [pagination-and-versioning.md](pagination-and-versioning.md) breaking down how a large result set gets split into pages, and how a contract changes over time without breaking existing clients.
7. [debounce-and-throttle.md](debounce-and-throttle.md) outlining the same question as rate limiting from the client's own side, controlling how often it fires a request in the first place.
8. [auth.md](auth.md) going over how a request's identity gets confirmed, and what that identity is then allowed to do.
9. [middleware.md](middleware.md) unpacking how cross-cutting concerns like auth and logging get composed around every request without duplicating that logic in every handler, tying the rest of this list together in practice.
