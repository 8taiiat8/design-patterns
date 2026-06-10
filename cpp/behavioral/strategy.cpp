// Strategy — define a family of interchangeable algorithms and make them
// swappable at run time behind a common interface.
//
// Use when a class needs one of several behaviors (compression formats,
// pricing rules, routing algorithms) and you want to avoid conditionals.
// In modern C++, std::function offers a lightweight alternative for simple
// cases — both styles are shown below.
//
// Build: g++ -std=c++17 strategy.cpp -o strategy

#include <functional>
#include <iostream>
#include <memory>

// Classic OO style: strategy interface + concrete strategies.
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double finalPrice(double base) const = 0;
};

class RegularPricing : public PricingStrategy {
public:
    double finalPrice(double base) const override { return base; }
};

class BlackFridayPricing : public PricingStrategy {
public:
    double finalPrice(double base) const override { return base * 0.5; }
};

class MemberPricing : public PricingStrategy {
public:
    double finalPrice(double base) const override { return base * 0.9; }
};

// Context: configured with a strategy, unaware of which one.
class Checkout {
public:
    explicit Checkout(std::unique_ptr<PricingStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<PricingStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void pay(double base) const {
        std::cout << "base $" << base << " -> pay $" << strategy_->finalPrice(base) << "\n";
    }

private:
    std::unique_ptr<PricingStrategy> strategy_;
};

int main() {
    Checkout checkout(std::make_unique<RegularPricing>());
    checkout.pay(100.0);

    checkout.setStrategy(std::make_unique<BlackFridayPricing>());
    checkout.pay(100.0);

    checkout.setStrategy(std::make_unique<MemberPricing>());
    checkout.pay(100.0);

    // Modern alternative: a std::function works as a strategy too.
    std::function<double(double)> clearance = [](double base) { return base * 0.3; };
    std::cout << "clearance: pay $" << clearance(100.0) << "\n";
    return 0;
}
