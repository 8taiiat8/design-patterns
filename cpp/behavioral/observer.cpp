// ☕ Café Patterna — Chapter 19: "Order 42 Is Ready!"
//
// STORY: Customers used to crowd the counter asking "is mine done yet?"
// Now they subscribe: when the barista finishes an order, the pickup
// screen lights up AND the customer's phone buzzes — automatically,
// without the barista knowing or caring who's listening.
//
// PATTERN: Observer — define a one-to-many dependency so that when the
// subject changes state, all registered observers are notified. The
// backbone of event systems and UI updates.
//
// Build: g++ -std=c++17 observer.cpp -o observer

#include <algorithm>
#include <iostream>
#include <vector>

// Observer interface
class OrderObserver {
public:
    virtual ~OrderObserver() = default;
    virtual void orderReady(int orderNo) = 0;
};

// Subject: maintains a list of observers and notifies them on change.
class PickupCounter {
public:
    void attach(OrderObserver* observer) { observers_.push_back(observer); }

    void detach(OrderObserver* observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                         observers_.end());
    }

    void announceReady(int orderNo) {
        std::cout << "barista: order #" << orderNo << " is done\n";
        for (OrderObserver* observer : observers_) observer->orderReady(orderNo);
    }

private:
    std::vector<OrderObserver*> observers_;
};

class PickupScreen : public OrderObserver {
public:
    void orderReady(int orderNo) override {
        std::cout << "  screen flashes: NOW SERVING #" << orderNo << "\n";
    }
};

class CustomerPhone : public OrderObserver {
public:
    void orderReady(int orderNo) override {
        std::cout << "  phone buzzes: your order #" << orderNo << " is ready!\n";
    }
};

int main() {
    PickupCounter counter;
    PickupScreen screen;
    CustomerPhone phone;

    counter.attach(&screen);
    counter.attach(&phone);

    counter.announceReady(41);
    counter.announceReady(42);

    counter.detach(&phone);  // customer picked up and left
    counter.announceReady(43);  // only the screen reacts now
    return 0;
}
