# Strategy

Strategy replaces conditional logic with polymorphism. Use it when you have different ways of doing the same thing and you want to swap them at runtime.

> When we say "runtime," we mean the moment the program is actually running. You can choose behaviors based on conditions, inputs, configuration as the code executes. When we say "compile time," we mean decisions baked into the code itself. The behavior is fixed in the class definition and doesn't change while the program runs.

Interviews love Strategy. It's the single most common pattern in LLD interviews because it directly test whether you understand polymorphism and composition over inheritance. When you see a pila of `if/else` or `switch` statements based on type, that's a strategy pattern waiting to happen.

```java
interface PaymentStrategy {
    boolean pay(double amount);
}

class CreditCardPayment implements PaymentStrategy {
    private String cardNumber;

    public CreditCardPayment(String cardNumber) {
        this.cardNumber = cardNumber;
    }

    public boolean pay(double amount) {
        // credit card logic
        System.out.println("Paid " + amount + " with credit card");
        return true;
    }
}

class PayPalPayment implements PaymentStrategy {
    private String email;

    public PayPalPayment(String email) {
        this.email = email;
    }

    public boolean pay(double amount) {
        // paypal logic
        System.out.println("Paid " + amount + " with PayPal");
        return true;
    }
}

class ShoppingCart {
    private PaymentStrategy paymentStrategy;

    public void setPaymentStrategy(PaymentStrategy strategy) {
        this.paymentStrategy = strategy;
    }

    public void checkout(double amount) {
        paymentStrategy.pay(amount);
    }
}

// Usage
ShoppingCart cart = new ShoppingCart();

cart.setPaymentStrategy(new CreditCardPayment("1234-5678"));
cart.checkout(100.00);

cart.setPaymentStrategy(new PayPalPayment("user@example.com"));
cart.checkout(50.00);
```