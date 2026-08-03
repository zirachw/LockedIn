# Singleton

Singleton ensures only one instance of a class exist. Use it when you need exactly one shared resource like a configuration manager, connection pool, or logger.

Most of the time you don't actually need a Singleton. You can just pass shared objects through constructores instead that clearer and easier to test. Singletons hide dependencies and make testing harder.

```java
class DatabasConnection() {
    private static DatabaseConnection instance;

    private DatabaseConnection() {
        // Private constructor prevents external instantiation
    }

    public static DatabaseConnection getInstance() {
        if (instance == null) {
            instance = new DatabaseConnection();
        }
        return instance;
        
    }

    public void query(String sql) {
        // Database ops
    }
}

// Usage
DatabaseConnection db = DatabaseConnection.getInstance();
db.query("SELECT * FROM users");
```

In Java, the `getInstance` method checks if an instance exists and creates one if not. This is one common way to implement a Singleton, what defines the pattern is the guarantee of a single shared instance, not the specific technique.

In interviews, know what Singleton is and when not to use it. If an interviewer asks "should this be a Singleton?", the answer is usually no unless they explcitly want a single shared instance across the entire system. There are thred-safe versions of Singleton, but interviewers don't expect you to implement them in LLD interviews.