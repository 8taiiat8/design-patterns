// ☕ Café Patterna — Chapter 1: The One Cash Register
//
// STORY: On opening day you buy exactly ONE cash register. Every barista
// rings up sales on the same machine — if there were two, the day's totals
// would never add up. The register is created the first time someone needs
// it, and everyone shares it from then on.
//
// PATTERN: Singleton — ensure a class has only one instance and provide a
// global access point to it. Use when exactly one object must coordinate
// something shop-wide (configuration, logging, the till).
//
// Key points in C++:
// - A function-local static (the "Meyers singleton") is initialized lazily
//   and is thread-safe since C++11.
// - Delete the copy/move operations so the instance cannot be duplicated.
//
// Build: g++ -std=c++17 singleton.cpp -o singleton

#include <iostream>
#include <string>

class CashRegister {
public:
    // The single global access point.
    static CashRegister& instance() {
        static CashRegister till;  // created on first use, thread-safe
        return till;
    }

    CashRegister(const CashRegister&) = delete;
    CashRegister& operator=(const CashRegister&) = delete;

    void ringUp(const std::string& item, double price) {
        ++sales_;
        total_ += price;
        std::cout << "[sale #" << sales_ << "] " << item << " $" << price
                  << " (day total: $" << total_ << ")\n";
    }

private:
    CashRegister() = default;  // private: nobody can buy a second register
    int sales_ = 0;
    double total_ = 0.0;
};

int main() {
    CashRegister::instance().ringUp("espresso", 2.0);
    CashRegister::instance().ringUp("croissant", 3.5);

    // Both baristas are using the same till.
    CashRegister& morningShift = CashRegister::instance();
    CashRegister& eveningShift = CashRegister::instance();
    std::cout << "same register? " << std::boolalpha
              << (&morningShift == &eveningShift) << "\n";
    return 0;
}
