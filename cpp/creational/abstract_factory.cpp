// ☕ Café Patterna — Chapter 3: The Franchise Kits
//
// STORY: Café Patterna goes international! Each franchise orders a "kit":
// the Italian kit ships a lever espresso machine WITH porcelain cups, the
// Japanese kit ships a siphon brewer WITH ceramic cups. Machines and cups
// from one kit always match — you never mix a siphon with porcelain.
//
// PATTERN: Abstract Factory — provide an interface for creating families
// of related objects without specifying their concrete classes. Use when
// products from one family must be used together.
//
// Build: g++ -std=c++17 abstract_factory.cpp -o abstract_factory

#include <iostream>
#include <memory>

// Abstract products
class CoffeeMachine {
public:
    virtual ~CoffeeMachine() = default;
    virtual void brew() const = 0;
};

class Cup {
public:
    virtual ~Cup() = default;
    virtual void fill() const = 0;
};

// Concrete products: the Italian family
class LeverMachine : public CoffeeMachine {
public:
    void brew() const override { std::cout << "lever machine pulls a shot\n"; }
};

class PorcelainCup : public Cup {
public:
    void fill() const override { std::cout << "filling a porcelain cup\n"; }
};

// Concrete products: the Japanese family
class SiphonBrewer : public CoffeeMachine {
public:
    void brew() const override { std::cout << "siphon brewer bubbles away\n"; }
};

class CeramicCup : public Cup {
public:
    void fill() const override { std::cout << "filling a ceramic cup\n"; }
};

// Abstract factory: one creation method per product type
class FranchiseKit {
public:
    virtual ~FranchiseKit() = default;
    virtual std::unique_ptr<CoffeeMachine> createMachine() const = 0;
    virtual std::unique_ptr<Cup> createCup() const = 0;
};

class ItalianKit : public FranchiseKit {
public:
    std::unique_ptr<CoffeeMachine> createMachine() const override { return std::make_unique<LeverMachine>(); }
    std::unique_ptr<Cup> createCup() const override { return std::make_unique<PorcelainCup>(); }
};

class JapaneseKit : public FranchiseKit {
public:
    std::unique_ptr<CoffeeMachine> createMachine() const override { return std::make_unique<SiphonBrewer>(); }
    std::unique_ptr<Cup> createCup() const override { return std::make_unique<CeramicCup>(); }
};

// The franchise owner only depends on the abstract kit interface.
void openFranchise(const FranchiseKit& kit) {
    kit.createMachine()->brew();
    kit.createCup()->fill();
}

int main() {
    std::cout << "-- Rome branch --\n";
    openFranchise(ItalianKit{});
    std::cout << "-- Kyoto branch --\n";
    openFranchise(JapaneseKit{});
    return 0;
}
