// ☕ Café Patterna — Chapter 21: Happy Hour
//
// STORY: The same latte costs different money depending on the moment:
// full price in the morning rush, half price during happy hour, 10% off
// for members. The till doesn't care WHICH rule is active — it just asks
// the current pricing rule for the final price, and you can swap the
// rule when the clock strikes five.
//
// PATTERN: Strategy — define a family of interchangeable algorithms and
// make them swappable at run time behind a common interface. In modern
// C++, std::function offers a lightweight alternative for simple cases —
// both styles are shown.
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

class HappyHourPricing : public PricingStrategy {
public:
    double finalPrice(double base) const override { return base * 0.5; }
};

class MemberPricing : public PricingStrategy {
public:
    double finalPrice(double base) const override { return base * 0.9; }
};

// Context: the till is configured with a strategy, unaware of which one.
class Till {
public:
    explicit Till(std::unique_ptr<PricingStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<PricingStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void charge(double base) const {
        std::cout << "latte base $" << base << " -> pay $" << strategy_->finalPrice(base) << "\n";
    }

private:
    std::unique_ptr<PricingStrategy> strategy_;
};

int main() {
    Till till(std::make_unique<RegularPricing>());
    till.charge(4.0);

    till.setStrategy(std::make_unique<HappyHourPricing>());  // it's 5pm somewhere
    till.charge(4.0);

    till.setStrategy(std::make_unique<MemberPricing>());
    till.charge(4.0);

    // Modern alternative: a std::function works as a strategy too.
    std::function<double(double)> staffDiscount = [](double base) { return base * 0.3; };
    std::cout << "staff price: pay $" << staffDiscount(4.0) << "\n";
    return 0;
}
