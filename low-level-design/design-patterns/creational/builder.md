# Builder

A builder is a helper that lets you create a complex object step by step without worrying about the order or messy construction details. It's used when an object has many optional parts or configuration choices.

This shows up when designing things like HTTP requests, database queires, or configuration objects. Instead of a constructor with ten parameters where half are null, you build the object incrementally.

```java
class HttpRequest {
    private String url;
    private String method;
    private Map<String, String> headers;
    private String body;

    private HttpRequest() {}

    public statis class Builder {
        private HttpRequest request = new HttpRequest();

        public Builder url(String url) {
            request.url = url;
            return this;
        }

        public Builder method(String method) {
            request.method = method;
            return this;
        }

        public Builder header(String key, String value) {
            if (request.headers == null) {
                request.headers = new HashMap<>();
            }

            request.headers.put(key, value);
            return this;
        }

        public Builder body(String body) {
            request.body = body;
            return this;
        }

        public HttpRequest build() {
            // Validate required fields
            if (request.url == null) {
                throw new IllegalStateException("URL is required");
            }
            return request;
        }
    }
}

// Usage
HttpRequest request = new HttpRequest.Builder()
    .url("https://api.example.com")
    .method("POST")
    .header("Content-Type", "application/json")
    .body("{\"key\" : \"value\"}")
    .build();
```

Builder makes construction readable and handles optional fields cleanly. It most commonly shows up in LLD interviews when you're designing API client or complext configurations, but is very rarely used in other contexts.

? If the interviewer didn't describe a complex object with lots of optional details, Builder probably isn't needed. Most interview problems involve simple domain objects with 2-4 required fields where a normal constructor works fine.