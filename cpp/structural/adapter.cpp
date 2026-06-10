// ☕ Café Patterna — Chapter 6: Grandpa's Grinder
//
// STORY: The new kitchen line expects every grinder to respond to
// grind(beans). But grandpa's beloved cast-iron grinder only understands
// turnCrank() — and it makes the best grounds in town. You won't rewire
// the kitchen and you can't modify a family heirloom, so you build an
// adapter that fits the old crank into the new interface.
//
// PATTERN: Adapter — convert the interface of an existing class into the
// interface clients expect, letting incompatible classes work together.
//
// Build: g++ -std=c++17 adapter.cpp -o adapter

#include <iostream>
#include <memory>
#include <string>

// The interface the kitchen line expects.
class Grinder {
public:
    virtual ~Grinder() = default;
    virtual void grind(const std::string& beans) = 0;
};

// The family heirloom with an incompatible interface (the adaptee).
// Imagine we cannot modify it.
class VintageGrinder {
public:
    void turnCrank(const std::string& contents) {
        std::cout << "vintage grinder slowly cranks through: " << contents << "\n";
    }
};

// The adapter implements the expected interface and delegates to the adaptee.
class VintageGrinderAdapter : public Grinder {
public:
    void grind(const std::string& beans) override {
        heirloom_.turnCrank(beans);  // translate the call
    }

private:
    VintageGrinder heirloom_;
};

// A modern grinder that fits natively, for comparison.
class ElectricGrinder : public Grinder {
public:
    void grind(const std::string& beans) override {
        std::cout << "electric grinder whizzes through: " << beans << "\n";
    }
};

int main() {
    std::unique_ptr<Grinder> kitchenLine[] = {
        std::make_unique<ElectricGrinder>(),
        std::make_unique<VintageGrinderAdapter>(),  // heirloom behind the same interface
    };

    for (auto& grinder : kitchenLine) {
        grinder->grind("Ethiopian beans");
    }
    return 0;
}
