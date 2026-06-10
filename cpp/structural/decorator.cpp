// ☕ Café Patterna — Chapter 9: Toppings, Toppings, Toppings
//
// STORY: Milk. Sugar. Whipped cream. Customers stack them in every
// combination imaginable. You are NOT creating a MilkSugarWhipEspresso
// class for each combo — instead every topping WRAPS the drink underneath
// and adds its own description and price.
//
// PATTERN: Decorator — attach additional responsibilities to an object
// dynamically by wrapping it in objects that share its interface.
//
// Build: g++ -std=c++17 decorator.cpp -o decorator

#include <iostream>
#include <memory>
#include <string>

// Component interface
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual std::string description() const = 0;
    virtual double cost() const = 0;
};

// Concrete component: the drink being decorated.
class Espresso : public Coffee {
public:
    std::string description() const override { return "espresso"; }
    double cost() const override { return 2.0; }
};

// Base decorator: wraps a Coffee and delegates by default.
class ToppingDecorator : public Coffee {
public:
    explicit ToppingDecorator(std::unique_ptr<Coffee> inner) : inner_(std::move(inner)) {}

    std::string description() const override { return inner_->description(); }
    double cost() const override { return inner_->cost(); }

private:
    std::unique_ptr<Coffee> inner_;
};

class Milk : public ToppingDecorator {
public:
    using ToppingDecorator::ToppingDecorator;
    std::string description() const override { return ToppingDecorator::description() + " + milk"; }
    double cost() const override { return ToppingDecorator::cost() + 0.5; }
};

class Sugar : public ToppingDecorator {
public:
    using ToppingDecorator::ToppingDecorator;
    std::string description() const override { return ToppingDecorator::description() + " + sugar"; }
    double cost() const override { return ToppingDecorator::cost() + 0.2; }
};

class WhippedCream : public ToppingDecorator {
public:
    using ToppingDecorator::ToppingDecorator;
    std::string description() const override { return ToppingDecorator::description() + " + whipped cream"; }
    double cost() const override { return ToppingDecorator::cost() + 0.7; }
};

int main() {
    // Stack toppings in any combination at run time.
    std::unique_ptr<Coffee> order = std::make_unique<WhippedCream>(
        std::make_unique<Sugar>(std::make_unique<Milk>(std::make_unique<Espresso>())));

    std::cout << order->description() << " costs $" << order->cost() << "\n";

    std::unique_ptr<Coffee> plain = std::make_unique<Espresso>();
    std::cout << plain->description() << " costs $" << plain->cost() << "\n";
    return 0;
}
