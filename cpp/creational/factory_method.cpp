// ☕ Café Patterna — Chapter 2: Hiring Baristas
//
// STORY: Business grows, so you hire baristas. You don't tell each barista
// HOW to serve a customer — the routine is the same (greet, craft the
// drink, hand it over). What differs is WHICH drink each specialist
// crafts: the espresso barista pulls shots, the tea master whisks matcha.
//
// PATTERN: Factory Method — define an interface for creating an object,
// but let subclasses decide which concrete class to instantiate. Use when
// a class can't anticipate the type of objects it must create.
//
// Build: g++ -std=c++17 factory_method.cpp -o factory_method

#include <iostream>
#include <memory>
#include <string>

// Product interface
class Drink {
public:
    virtual ~Drink() = default;
    virtual std::string describe() const = 0;
};

class Espresso : public Drink {
public:
    std::string describe() const override { return "a double espresso, rich crema"; }
};

class MatchaLatte : public Drink {
public:
    std::string describe() const override { return "a matcha latte, whisked to order"; }
};

// Creator: the serving routine relies only on the Drink interface;
// the factory method defers the choice of concrete drink to subclasses.
class Barista {
public:
    virtual ~Barista() = default;

    void serveCustomer() const {
        auto drink = craftSignatureDrink();  // the factory method
        std::cout << "Barista serves " << drink->describe() << "\n";
    }

protected:
    virtual std::unique_ptr<Drink> craftSignatureDrink() const = 0;
};

class EspressoBarista : public Barista {
protected:
    std::unique_ptr<Drink> craftSignatureDrink() const override {
        return std::make_unique<Espresso>();
    }
};

class TeaMaster : public Barista {
protected:
    std::unique_ptr<Drink> craftSignatureDrink() const override {
        return std::make_unique<MatchaLatte>();
    }
};

int main() {
    EspressoBarista marco;
    TeaMaster yuki;
    marco.serveCustomer();
    yuki.serveCustomer();
    return 0;
}
