// Facade — provide a single simplified interface to a complex subsystem.
//
// Use when clients only need a small slice of a subsystem's functionality,
// or when you want to decouple client code from the subsystem's internals.
//
// Build: g++ -std=c++17 facade.cpp -o facade

#include <iostream>
#include <string>

// Complex subsystem parts. Clients could call these directly, but the
// correct order and wiring is easy to get wrong.
class Inventory {
public:
    bool reserve(const std::string& item) {
        std::cout << "inventory: reserved " << item << "\n";
        return true;
    }
};

class Payment {
public:
    bool charge(double amount) {
        std::cout << "payment: charged $" << amount << "\n";
        return true;
    }
};

class Shipping {
public:
    void schedule(const std::string& item, const std::string& address) {
        std::cout << "shipping: " << item << " -> " << address << "\n";
    }
};

// The facade exposes one high-level operation that orchestrates the parts.
class OrderFacade {
public:
    bool placeOrder(const std::string& item, double price, const std::string& address) {
        if (!inventory_.reserve(item)) return false;
        if (!payment_.charge(price)) return false;
        shipping_.schedule(item, address);
        std::cout << "order complete\n";
        return true;
    }

private:
    Inventory inventory_;
    Payment payment_;
    Shipping shipping_;
};

int main() {
    OrderFacade shop;
    shop.placeOrder("mechanical keyboard", 89.99, "42 Wallaby Way");
    return 0;
}
