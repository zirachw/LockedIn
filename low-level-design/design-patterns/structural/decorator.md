# Decorator

A decorator adds behaviour to an object without changing its class. Use it when you need to layer on extra functionality at runtime.

Decorator is powerful but comes up less often than Strategy or Observer. You might need this whe the requirements say things like "add logging to specific operations" or "encrypt certain message." Instead of creating subclasses for every combination (`LoggedEmailNotification`, `EncryptedEmailNotification`, `LoggedEncryptedEmailNotification`), you wrap the base object with decorators. If you see words like "optional features", "stack behaviours", or "combine multiple enhancements," think Decorator.

```java
interface DataSource {
    void writeData(String data);
    String readData();
}

class FileDataSource implements DataSource {
    private String filename;

    public FileDataSource(String filename) {
        this.filename = filename;
    }

    public void writeData(String data) {
        // Write to file
    }

    public String readData() {
        // Read from file
        return "data from file";
    }
}

class EncryptionDecorator implements DataSource {
    private DataSource wrapped;

    public EncryptionDecorator(DataSource source) {
        this.wrapped = source;
    }

    public void writeData(String data) {
        String encrypted = encrypt(data);
        wrapped.writeData(encrypted);       // Delegate to wrapped object
    }

    public String readData() {
        String data = wrapped.readData();
        return decrypt(data);
    }

    private String encrypt(String data) {
        return "encrypted:" + data;
    }

    private String decrypt(String data) {
        return data.replace("encrypted:", "");
    }
}

class ComperessionDecorator implements DataSource {
    private DataSource wrapped;

    public EncryptionDecorator(DataSource source) {
        this.wrapped = source;
    }

    public void writeData(String data) {
        String compressed = compress(data);
        wrapped.writeData(compressed);       // Delegate to wrapped object
    }

    public String readData() {
        String data = wrapped.readData();
        return decompress(data);
    }

    private String encrypt(String data) {
        return "compressed:" + data;
    }

    private String decompress(String data) {
        return data.replace("compressed:", "");
    }
}

// Usage
DataSource source = new FileDataSource("data.txt");
source = new EncryptionDecorator(source);
source = new CompressionDecorator(source);
source.writeData("sensitive info");
// Data gets compressed, then encrypted, then written to file
```

> Use a Decorator when you need to add behavior at runtime based on conditions, like wrapping a service with logging only in debug mode or adding caching only for certain requests. It lets you layer optional, combinable features without modifying the underlying class.

> In most other cases, use normal subclases, where the new behavior is fixed at design time and represents a stable variation of the original type. If the behavior depends on runtime conditions, choose Decorator. If it's a predefined type, choose Subclass.

Each decorator adds one piece of functionality. You can stack them in any order and add or remove them without touching the base class or other decorators, though in real systems order often affects behavior.