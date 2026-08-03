# Factory Method

A factory is a helper that makes the right kind of object for you so you don't have to decide which one to create. They're used to hide creation logic and keep your code flexible when the exact type you need can change.

> Factories are polarizing. While very popular and idomatic in languages like Java, some engineers see them as examples of everengineering. If you choose to implement one, take a look at your interviewer and check them for a grimace.

Factory show up regularly in interviews, usually when requirements say "support different notification types" or "handle multiple payment methods." Instead of writing `new EmailNotification()` throughout your code, you call `notificationFactory.create(type)`. Now when you add SMS notifications, you update the factory. The rest of your code never changes.

```java
interface Notification {
    void send(String message);
}

class EmailNotification implements Notification {
    public void send(String message) {
        // Email sending logic
    }
}

class SMSNotification implements Notification {
    public void send(String message) {
        // SMS sending logic
    }
}

class NotificationFactory {
    public static Notification create(String type) {
        if (type.equals("email")) {
            return new EmailNotification();
        } else if (type.equals("sms")) {
            return new SMSNotification();
        }
        throw new IllegalArgumentException("Unknown type");
    }
}

// Usage
Notification notif = NotificationFactory.create("email");
notif.send("Hello");
```

The factory centralizes creation logic. When you add push notifications, you modify one place. Factory controls which object gets instantiated. It makes the decision once and returns the right type.

> This is technically called Simple Factory, not the Gang of Four Factory Method pattern. The GoF version uses abstract factory classes with subclasses that override a factory method. It's more complex and rarely shows up in real code or interviews. What we're showing here is what people actually build and what interviewers expect when they say "use a factory"

