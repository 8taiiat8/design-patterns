// 🤖 RoboWorks — Chapter 10: The Big Green Button
//
// STORY: Starting production is chaos behind the scenes: reserve parts,
// power up the grid, run the assembly cell, pass quality control — in
// exactly that order. The client sees none of it. They press the big
// green button labeled "PRODUCE" and the facade orchestrates everything.
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
class PartsDepot {
public:
    bool reservePartsFor(const std::string& model) {
        std::cout << "depot: parts reserved for " << model << "\n";
        return true;
    }
};

class PowerGrid {
public:
    bool powerUp(int kilowatts) {
        std::cout << "grid: " << kilowatts << " kW allocated\n";
        return true;
    }
};

class AssemblyCell {
public:
    void assemble(const std::string& model) {
        std::cout << "cell: assembling " << model << "\n";
    }
};

class QualityControl {
public:
    void inspect(const std::string& model) {
        std::cout << "QC: " << model << " passed inspection\n";
    }
};

// The facade exposes one high-level operation that orchestrates the parts.
class ProductionFacade {
public:
    bool produce(const std::string& model, int kilowatts) {
        if (!depot_.reservePartsFor(model)) return false;
        if (!grid_.powerUp(kilowatts)) return false;
        cell_.assemble(model);
        qc_.inspect(model);
        std::cout << "production run complete\n";
        return true;
    }

private:
    PartsDepot depot_;
    PowerGrid grid_;
    AssemblyCell cell_;
    QualityControl qc_;
};

int main() {
    ProductionFacade bigGreenButton;
    bigGreenButton.produce("WelderBot Mk2", 40);
    return 0;
}
