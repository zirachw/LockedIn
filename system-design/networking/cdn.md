# What is a CDN?

Physical distance between a server and a user costs real latency, the time it takes a request and response to travel back and forth.

# Starting small

Consider an online store with a single origin server in Jakarta, serving product pages and images. A customer browsing from Jakarta requests a product photo, the request travels a short distance to the server, and the image comes back in milliseconds.

```mermaid
flowchart LR
    U[User in Jakarta] -- short trip --> O[Origin server, Jakarta]
    O -- short trip --> U
```

At a local audience this works fine. Every request is short and fast, and nobody notices the server's physical location at all.

# Where it breaks

The same store starts getting customers in Europe and the US. Their requests now have to travel across oceans and continents to reach that one server in Jakarta, adding hundreds of milliseconds of latency before the response even starts coming back, on top of whatever time the server itself takes to respond.

```mermaid
flowchart LR
    U[User in Europe] -- long trip --> O[Origin server, Jakarta]
    O -- long trip --> U
```

Running origin servers in every region a customer might connect from is not practical for most teams, that infrastructure is expensive to run and complex to keep in sync.

A CDN, content delivery network, solves this by caching content on servers distributed close to users geographically, so a request gets served from a nearby edge location instead of traveling all the way back to the origin server.

# How a request gets served

```mermaid
flowchart LR
    U[User] --> E[Nearest edge node]
    E -- cache hit --> U
    E -- cache miss --> O[Origin server]
    O --> E
    E --> U
```

On a cache hit, the edge node closest to the user answers directly, no round trip to the origin at all.

On a cache miss, the edge node fetches from the origin once, serves that response, and caches it for the next nearby request.

# Edge Nodes and Cache Control

Edge nodes, sometimes called points of presence, are the geographically distributed servers that actually cache and serve content. More of them closer to users means lower latency on average.

Cache-Control headers, set by the origin server, tell the CDN how long a given response can be cached before it needs to be re-fetched, the same TTL tradeoff that applies to DNS and application-level caching.

# What Fits and What Doesn't

Static assets, images, videos, CSS, JavaScript bundles, are the classic CDN use case, since they rarely change and are safe to cache aggressively.

Dynamic, personalized content is a poor fit for the same reason, unless the CDN supports edge compute to run logic per request rather than serving one cached response to everyone.

Cache invalidation, purging a specific asset from every edge node before its TTL naturally expires, is needed when content changes and cannot wait for the cache to expire on its own, a deployment of a new CSS file, for instance.

# Providers

Cloudflare, Amazon CloudFront, and Fastly are the major CDN providers. Each also offers DDoS protection and edge compute as an extension of the same distributed network.

## Cloudflare

Cloudflare pairs its CDN with the rest of its security and DNS product line, DDoS protection, a WAF, and Workers for running code at the edge, in one account, which is why it is often the default even for a team not otherwise deep in one cloud provider.

## Amazon CloudFront

Amazon CloudFront leans into AWS integration, pulling directly from an S3 bucket as an origin and running Lambda@Edge for per-request logic, the natural choice for a system already built on AWS.

## Fastly

Fastly is known for near-instant cache purges, invalidating an asset across its network in seconds rather than minutes, which matters most for news or media sites that need a change to go live immediately rather than waiting on a TTL to expire.

# How to choose

The general fit is the same across all three, cacheable, mostly-static content benefits, content that must always be fresh does not. Within that, the choice comes down to what else the system already depends on.

## Cloudflare

Cloudflare fits a team that wants CDN, DNS, and security bundled into one account, without needing to already be on a specific cloud provider.

## Amazon CloudFront

Amazon CloudFront fits a system already built on AWS, where pulling from S3 and running Lambda@Edge fit naturally into the existing stack.

## Fastly

Fastly fits content that changes often enough that purge speed genuinely matters, a news site or anything publishing frequent updates that cannot wait on a TTL to expire naturally.

# What gets traded away

A CDN meaningfully cuts latency and origin load for cacheable content, but it adds a layer of caching that can serve stale content if invalidation is not handled correctly when the origin changes. Content that must always be fresh, real-time pricing, live inventory counts, gets little benefit from it and needs to bypass the cache entirely, which reintroduces the exact latency the CDN exists to remove.

## Cloudflare

Cloudflare trades away some of CloudFront's depth of native AWS integration for being a more provider-neutral default.

## Amazon CloudFront

Amazon CloudFront trades away that neutrality, its tightest integrations only pay off when the origin is already S3 or another AWS service.

## Fastly

Fastly trades away Cloudflare's broader bundled product line and CloudFront's AWS integration for being narrowly focused on CDN performance and fast purges specifically.
