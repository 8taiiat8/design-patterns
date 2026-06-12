// 🤖 RoboWorks — Chapter 22: The Boot Sequence
//
// STORY: Every robot boots the same way, in the same order: power on,
// self-test, load drivers, announce readiness. The sequence itself never
// changes — but HOW each robot self-tests (calibrate the welding laser,
// spin up the rotors) and how it announces differ per model.
//
// PATTERN: Template Method — define the skeleton of an algorithm in a
// base class and let subclasses override specific steps without changing
// the algorithm's structure.
//
// Build: g++ -std=c++17 template_method.cpp -o template_method

#include <iostream>

// The base class owns the boot sequence's skeleton.
class BootSequence {
public:
    virtual ~BootSequence() = default;

    // The template method: fixed order, non-virtual on purpose.
    void boot() {
        powerOn();
        selfTest();
        loadDrivers();
        announceReady();  // optional hook with a default
    }

protected:
    // Steps subclasses must provide.
    virtual void selfTest() = 0;

    // Hook: has a sensible default, override only if needed.
    virtual void announceReady() { std::cout << "  (standard ready beep)\n"; }

private:
    // Steps that are identical for every robot stay private and fixed.
    void powerOn() { std::cout << "  power on\n"; }
    void loadDrivers() { std::cout << "  loading drivers\n"; }
};

class WelderBot : public BootSequence {
protected:
    void selfTest() override { std::cout << "  calibrating welding laser\n"; }
    void announceReady() override { std::cout << "  announces: welding systems online\n"; }
};

class ScoutDrone : public BootSequence {
protected:
    void selfTest() override { std::cout << "  spinning up rotors\n"; }
};

int main() {
    std::cout << "Booting WelderBot:\n";
    WelderBot{}.boot();

    std::cout << "Booting ScoutDrone:\n";
    ScoutDrone{}.boot();
    return 0;
}
