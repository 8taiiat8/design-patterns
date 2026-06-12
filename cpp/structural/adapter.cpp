// 🤖 RoboWorks — Chapter 6: The Legacy Welding Arm
//
// STORY: The new assembly line expects every arm to respond to
// actuate(task). But the legendary legacy welding arm from the old plant
// only understands pulseCrank() — and it still welds better than anything
// on the market. You won't rewire the line and you can't modify a
// discontinued part, so you build an adapter that fits the old protocol
// into the new interface.
//
// PATTERN: Adapter — convert the interface of an existing class into the
// interface clients expect, letting incompatible classes work together.
//
// Build: g++ -std=c++17 adapter.cpp -o adapter

#include <iostream>
#include <memory>
#include <string>

// The interface the assembly line expects.
class RoboticArm {
public:
    virtual ~RoboticArm() = default;
    virtual void actuate(const std::string& task) = 0;
};

// The legacy part with an incompatible interface (the adaptee).
// Imagine we cannot modify it.
class LegacyWeldingArm {
public:
    void pulseCrank(const std::string& job) {
        std::cout << "legacy arm pulses through: " << job << "\n";
    }
};

// The adapter implements the expected interface and delegates to the adaptee.
class LegacyArmAdapter : public RoboticArm {
public:
    void actuate(const std::string& task) override {
        legacy_.pulseCrank(task);  // translate the call
    }

private:
    LegacyWeldingArm legacy_;
};

// A modern arm that fits natively, for comparison.
class ServoArm : public RoboticArm {
public:
    void actuate(const std::string& task) override {
        std::cout << "servo arm smoothly executes: " << task << "\n";
    }
};

int main() {
    std::unique_ptr<RoboticArm> assemblyLine[] = {
        std::make_unique<ServoArm>(),
        std::make_unique<LegacyArmAdapter>(),  // legacy part behind the same interface
    };

    for (auto& arm : assemblyLine) {
        arm->actuate("weld chassis seam #7");
    }
    return 0;
}
