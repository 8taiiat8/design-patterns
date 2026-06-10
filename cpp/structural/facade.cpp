// ☕ Café Patterna — Chapter 10: One Counter to Rule Them All
//
// STORY: Behind the counter it's chaos: check the bean inventory, brew
// the drink, charge the card, stamp the loyalty card — in exactly that
// order. The customer sees none of it. They say "one latte please" and
// the counter orchestrates everything.
//
// PATTERN: Facade — provide a single simplified interface to a complex
// subsystem. Use when clients need only a small slice of a subsystem's
// functionality, in the right order.
//
// Build: g++ -std=c++17 facade.cpp -o facade

#include <iostream>
#include <string>

// Complex subsystem parts. Clients could call these directly, but the
// correct order and wiring is easy to get wrong.
class BeanInventory {
public:
    bool reserveBeansFor(const std::string& drink) {
        std::cout << "inventory: beans reserved for " << drink << "\n";
        return true;
    }
};

class BrewStation {
public:
    void brew(const std::string& drink) {
        std::cout << "brew station: making " << drink << "\n";
    }
};

class Payment {
public:
    bool charge(double amount) {
        std::cout << "payment: charged $" << amount << "\n";
        return true;
    }
};

class LoyaltyProgram {
public:
    void stamp(const std::string& customer) {
        std::cout << "loyalty: stamped " << customer << "'s card\n";
    }
};

// The facade exposes one high-level operation that orchestrates the parts.
class OrderCounter {
public:
    bool placeOrder(const std::string& drink, double price, const std::string& customer) {
        if (!inventory_.reserveBeansFor(drink)) return false;
        if (!payment_.charge(price)) return false;
        brewStation_.brew(drink);
        loyalty_.stamp(customer);
        std::cout << "order complete, enjoy!\n";
        return true;
    }

private:
    BeanInventory inventory_;
    BrewStation brewStation_;
    Payment payment_;
    LoyaltyProgram loyalty_;
};

int main() {
    OrderCounter counter;
    counter.placeOrder("oat latte", 4.5, "Nora");
    return 0;
}
