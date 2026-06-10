// Decorator — attach additional responsibilities to an object dynamically
// by wrapping it in objects that share its interface.
//
// Use when you want to add behavior to individual objects at run time
// without subclassing every combination (coffee + milk + sugar + ...).
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

// Concrete component: the object being decorated.
class Espresso : public Coffee {
public:
    std::string description() const override { return "espresso"; }
    double cost() const override { return 2.0; }
};

// Base decorator: wraps a Coffee and delegates by default.
class CoffeeDecorator : public Coffee {
public:
    explicit CoffeeDecorator(std::unique_ptr<Coffee> inner) : inner_(std::move(inner)) {}

    std::string description() const override { return inner_->description(); }
    double cost() const override { return inner_->cost(); }

private:
    std::unique_ptr<Coffee> inner_;
};

class Milk : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;
    std::string description() const override { return CoffeeDecorator::description() + " + milk"; }
    double cost() const override { return CoffeeDecorator::cost() + 0.5; }
};

class Sugar : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;
    std::string description() const override { return CoffeeDecorator::description() + " + sugar"; }
    double cost() const override { return CoffeeDecorator::cost() + 0.2; }
};

int main() {
    // Stack decorators in any combination at run time.
    std::unique_ptr<Coffee> order =
        std::make_unique<Sugar>(std::make_unique<Milk>(std::make_unique<Espresso>()));

    std::cout << order->description() << " costs $" << order->cost() << "\n";

    std::unique_ptr<Coffee> plain = std::make_unique<Espresso>();
    std::cout << plain->description() << " costs $" << plain->cost() << "\n";
    return 0;
}
