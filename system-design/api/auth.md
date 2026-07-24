# What are Authentication and Authorization?

Authentication confirms who is making a request. Authorization confirms what that identity is allowed to do once it's confirmed. They're different problems, but almost every real system has to answer both, one right after the other, which is why they're covered together here.

# Authentication

# Starting small

Consider a single internal service calling another, authenticated with one hardcoded API key checked on every request.

```mermaid
flowchart LR
    S1[Service A] -- "API key: xyz" --> S2[Service B]
```

For one service calling another, this is enough, there's exactly one caller and one key to check.

# Where it breaks

Real users need to log in individually, have sessions that expire, and log out on demand, none of which a single shared key can express, since a shared key doesn't distinguish one user from another at all.

```mermaid
flowchart LR
    U1[User 1] -- "same shared key" --> A[API]
    U2[User 2] -- "same shared key" --> A
```

Identifying individual users, and letting each of their sessions be created and revoked independently, is what the approaches below solve differently.

# Session-Based Authentication

Session-based authentication creates a session record on the server after a successful login, and gives the client a session ID in a cookie, checked against that server-side record on every subsequent request.

```mermaid
flowchart LR
    C[Client] -- "session ID cookie" --> A[API]
    A --> Store[(Session store)]
```

Creating and reading that session record is two ordinary calls.

```python
session_id = create_session(user_id)  # stored server-side, e.g. in Redis
response.set_cookie("session_id", session_id)
```

Revoking a session is immediate and simple, deleting the server-side record instantly invalidates it. That same server-side lookup is the cost, every request needs a round trip to the session store, and that store has to be shared across every server in a horizontally scaled deployment rather than living in one machine's memory.

# Token-Based Authentication (JWT)

Token-based authentication issues a signed token after login, a JWT, JSON Web Token, carrying claims like user ID, roles, and an expiry directly inside it, verified by checking its signature rather than looking anything up.

```mermaid
flowchart LR
    C[Client] -- "JWT in Authorization header" --> A[API]
    A -- "verify signature only" --> A
```

Issuing and verifying the token are two independent calls, needing nothing shared but the signing key.

```python
token = jwt.encode({"user_id": 42, "exp": time.time() + 3600}, secret_key)
payload = jwt.decode(token, secret_key)  # raises if signature invalid or expired
```

Not needing a server-side lookup at all is the appeal, any server holding the signing key can verify a token independently, which scales cleanly across many servers. The cost shows up at revocation, a JWT is valid until it expires no matter what happens server-side afterward, so revoking one before its natural expiry means maintaining a blocklist, which reintroduces the same server-side check the token was meant to avoid.

# OAuth

OAuth solves a different problem than the other two, letting a third-party application act on a user's behalf without that application ever seeing the user's actual password, "Log in with Google" being the common example.

```mermaid
flowchart LR
    App[Third-party app] --> Auth[Authorization server,<br/>e.g. Google]
    Auth -- "user approves" --> App
    App -- "scoped access token" --> API[Resource API]
```

The user authenticates directly with the authorization server, Google, in the example, which then issues the third-party app a scoped access token, good only for the specific permissions the user approved, rather than full account access.

```
GET /authorize?client_id=app123&scope=read_profile&redirect_uri=...
```

That delegation is exactly what session and token auth don't solve on their own, a user granting one specific app limited access without ever handing that app a password it could reuse elsewhere. The cost is complexity, OAuth's authorization flows involve more moving parts, redirect steps, and scopes to configure correctly than either session or token auth alone.

# Authorization

# Starting small

Consider a small app with a single boolean check, `is_admin`, gating a handful of privileged actions.

```mermaid
flowchart LR
    U[User, is_admin: true] --> Check{is_admin?}
    Check -- yes --> Action[Privileged action]
```

With only two tiers of user, admin and everyone else, this is all the granularity the app actually needs.

# Where it breaks

Permissions get more specific than a single flag can express, a user who can edit their own posts but not someone else's, a moderator who can hide content but not delete an account, and a single boolean has no way to represent that many distinct, overlapping rules.

# Role-Based Access Control

RBAC groups permissions into named roles, admin, editor, viewer, and assigns each user one or more roles, so a permission check asks whether any of the user's roles grants the needed permission.

```mermaid
flowchart LR
    U[User] --> R[Role: editor]
    R --> P1[Permission: edit posts]
    R --> P2[Permission: view posts]
```

Checking a permission is a lookup across whichever roles the user holds.

```python
def can(user, permission):
    return any(permission in ROLE_PERMISSIONS[role] for role in user.roles)
```

Reasoning about who can do what is straightforward here, a role's permission list is fixed and easy to audit. What it can't express cleanly is a rule that depends on the specific resource being acted on, editing your own post versus anyone's post needs a role check plus extra logic bolted on, since the role itself has no concept of ownership.

# Attribute-Based Access Control

ABAC evaluates a permission dynamically, based on attributes of the user, the resource, and the context of the request, rather than a fixed role's fixed permission list.

```mermaid
flowchart LR
    U["User,<br/>department: sales"] --> Rule{Evaluate rule}
    D["Document,<br/>department: sales"] --> Rule
    Rule -- "departments match" --> Allow[Access granted]
```

The rule itself is just a function evaluating whatever attributes matter.

```python
def can_edit(user, document):
    return user.department == document.department and is_business_hours()
```

That flexibility lets a single rule express exactly the ownership or context-dependent logic RBAC needed extra code to bolt on, department matches, time of day, resource state, all evaluated together. The cost is auditability, a rule combining several dynamic attributes is harder to reason about at a glance than a fixed list of role-to-permission mappings, and tracing why a specific request was allowed or denied means evaluating the same conditions the system did, not just reading a table.

# How to choose

Session-based auth fits a traditional web application where immediate, reliable revocation matters and the deployment can share one session store across its servers.

Token-based auth fits a stateless API or a system with many independently scaling servers, where avoiding a server-side lookup on every request matters more than instant revocation.

OAuth fits letting a third-party application or service act on a user's behalf with limited, user-approved permissions, not a system's own first-party login.

RBAC fits permissions that map cleanly onto a small, fixed set of roles, most applications' actual needs.

ABAC fits permissions that genuinely depend on resource ownership or request context, where RBAC's fixed roles would need extra logic bolted on for every such case anyway.

# What gets traded away

Session-based auth trades away easy horizontal scaling for simple, immediate revocation.

Token-based auth trades away easy revocation for a server-side lookup it never needs to make.

OAuth trades away simplicity for the ability to delegate limited access safely to a third party.

RBAC trades away fine-grained, context-aware rules for permissions that are easy to define and audit.

ABAC trades away that same auditability for rules flexible enough to express ownership and context RBAC cannot on its own.
