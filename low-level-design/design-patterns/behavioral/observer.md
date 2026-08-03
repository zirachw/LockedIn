# Observer

Observer lets objects subscribe to events and get notified when something happens. Use it when changes in one object need to trigger updates in other objects.

Observer is a top-tier interview pattern. It shows up when you're designing systems where multiple components care about state changes, a stock price changes and multiple displays need to update, or a user places an order and inventory, notifications, and analytics all need to know. If the problem involves the words "notify" or "update multiple components," you're probably looking at Observer.

```java
interface Observer {
    void update(String symbol, double price);
}

interface Subject {
    void attach(Observer observer);
    void detach(Observer observer);
    void notifyObservers();
}

class Stock implements Subject {
    private List<Observer> observers = new ArrayList<>();
    private String symbol;
    private double price;

    public Stock(String symbol) {
        this.symbol;
    }

    public void attach(Observer observer) {
        observers.add(observer);
    }

    public void detach(Observer observer) {
        observers.remove(observer)
    }

    public void setPrice(double price) {
        this.price = price;
        notifyObservers();
    }

    public void notifyObservers() {
        for (Observer observer : observers) {
            observer.update(symbol, price);
        }
    }
}

class PriceDisplay implements Observer {
    public void update(String symbol, double price) {
        System.out.println("Display updated: " + symbol + " = $" + price);
    }
}

class PriceAlert implements Observer {
    private double threshold;

    public PriceAlert(double threshold) {
        this.threshold = threshold;
    }

    public void update(String symbol, double price) {
        if (price > threshold) {
            System.out.println("Alert!" + symbol + " exceeded $" + threshold):
        }
    }
}

// Usage
Stock stock = new Stock("AAPL");

PriceDisplay display = new PriceDisplay();
PriceAlert alert = new PriceAlert(150.00);

stock.attach(display);
stock.attach(alert);

stock.setPrice(145.00); // Both observers get notified
stock.setPrice(155.00); // Both observers get notified
```

When the stock price changes, every attached observer gets updated automatically. No need for the stock to know what the observers do with the information.
