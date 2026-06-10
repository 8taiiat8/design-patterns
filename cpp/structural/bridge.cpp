// ☕ Café Patterna — Chapter 7: Any Drink, Any Machine
//
// STORY: You sell lattes and cappuccinos; you own a home machine and an
// industrial one. Without care you'd need HomeLatte, IndustrialLatte,
// HomeCappuccino, IndustrialCappuccino... a class for every combination.
// Instead, each DRINK holds a reference to a MACHINE: new drinks and new
// machines can now be added independently.
//
// PATTERN: Bridge — decouple an abstraction (Drink) from its
// implementation (BrewMachine) so the two hierarchies vary independently.
//
// Build: g++ -std=c++17 bridge.cpp -o bridge

#include <iostream>

// Implementation hierarchy
class BrewMachine {
public:
    virtual ~BrewMachine() = default;
    virtual void brewShots(int shots) const = 0;
};

class HomeMachine : public BrewMachine {
public:
    void brewShots(int shots) const override {
        std::cout << "home machine gently brews " << shots << " shot(s)\n";
    }
};

class IndustrialMachine : public BrewMachine {
public:
    void brewShots(int shots) const override {
        std::cout << "industrial machine blasts out " << shots << " shot(s)\n";
    }
};

// Abstraction hierarchy: holds the "bridge" to the implementation.
class Drink {
public:
    explicit Drink(const BrewMachine& machine) : machine_(machine) {}
    virtual ~Drink() = default;
    virtual void prepare() const = 0;

protected:
    const BrewMachine& machine_;
};

class Latte : public Drink {
public:
    Latte(const BrewMachine& machine, int shots)
        : Drink(machine), shots_(shots) {}

    void prepare() const override { machine_.brewShots(shots_); }

    void makeItStronger() { ++shots_; }

private:
    int shots_;
};

int main() {
    HomeMachine home;
    IndustrialMachine industrial;

    // Any drink can be paired with any machine at run time.
    Latte cozy(home, 1);
    Latte rush(industrial, 1);
    cozy.prepare();
    rush.prepare();

    cozy.makeItStronger();
    cozy.prepare();
    return 0;
}
