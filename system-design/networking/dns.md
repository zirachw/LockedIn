# What is DNS?

Computers route traffic by IP address, not by name. Before a browser can open a connection to `example.com`, something has to translate that name into an address.

DNS, the Domain Name System, is that translation layer, a distributed, hierarchical directory that every request consults before the actual request ever goes out.

# How a lookup resolves

A DNS lookup rarely hits one server. It walks down a hierarchy, each level pointing to the next, until an authoritative answer comes back.

```mermaid
flowchart LR
    C[Client] --> R[Recursive resolver]
    R --> Root[Root server]
    Root --> TLD[TLD server, .com]
    TLD --> Auth[Authoritative server]
    Auth --> R
    R --> C
```

The recursive resolver, often run by an ISP or a public service like Google's 8.8.8.8 or Cloudflare's 1.1.1.1, does the actual walking on the client's behalf. It caches the result, so the next lookup for the same domain skips straight to a cached answer instead of repeating the whole walk.

# Record types

A lookup returns a different kind of answer depending on what record type it asks for. An A record maps a name to an IPv4 address, and AAAA does the same for IPv6.

A CNAME aliases one name to another, letting `www.example.com` point at `example.com` without duplicating its IP mapping. An MX record points to a domain's mail servers.

A TXT record holds arbitrary text, commonly used to prove domain ownership or configure email authentication schemes like SPF and DKIM.

# TTL and propagation

Every record carries a TTL, time to live, which tells a resolver how long it may cache the answer before checking again.

A low TTL means a change reaches every resolver faster, since cached answers expire and get re-fetched sooner, at the cost of resolvers hitting the authoritative server far more often.

A high TTL cuts that load dramatically, but a mistake or a needed change, failing over to a new IP during an incident, for instance, takes correspondingly longer to reach every client. Stale cached answers keep being served until they expire on their own, which is what "DNS propagation" delay actually refers to.

# Authoritative Providers

Route 53, Cloudflare DNS, and Google Cloud DNS all host a domain's records, the source of truth the resolution hierarchy eventually reaches, but they differ in what routing logic they layer on top of that basic hosting job.

| Provider | Defining trait | Fits | Trades away |
|---|---|---|---|
| Route 53 | Deep AWS integration, latency-based and geolocation routing, plus health-check-driven failover that pulls a record out of rotation automatically | A system already living inside AWS, where failover and routing plug directly into the rest of the stack | Platform neutrality, its most valuable features assume the rest of the system is already on AWS |
| Cloudflare DNS | Fastest to propagate changes, backed by Cloudflare's own global anycast network, DDoS protection and a free tier bundled in | A team that wants the fastest propagation and DDoS protection, regardless of which cloud provider the servers run on | Route 53's deeper cloud-native routing logic, in exchange for speed and provider independence |
| Google Cloud DNS | Simpler feature set with tight integration with GCP's own load balancers | A system already built on GCP, where that integration matters more than Route 53's deeper routing options | Route 53's routing sophistication, a reasonable trade only if the rest of the stack is already on Google Cloud |

# How to choose

The real difference between these three is rarely raw lookup speed, all three are fast enough for almost any workload. It comes down to which platform's health checks, failover, and routing rules a team is already invested in.

# What gets traded away

Choosing an authoritative provider mostly trades routing sophistication against how tightly it needs to fit into an existing cloud stack.
