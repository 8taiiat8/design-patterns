// 🤖 RoboWorks — Chapter 23: The Inspectors
//
// STORY: Two inspectors walk the floor today: the safety auditor tallies
// power risk, the appraiser prints value tags. The machines themselves
// (welders, drones) don't change — each machine simply ACCEPTS the
// inspector and the inspector does its own job per machine type. Next
// month a new inspector can visit without touching a single machine class.
//
// PATTERN: Visitor — represent an operation on the elements of an object
// structure, letting you add new operations without modifying the element
// classes. The key mechanism is double dispatch via accept()/visit().
//
// Build: g++ -std=c++17 visitor.cpp -o visitor

#include <iostream>
#include <memory>
#include <vector>

class WelderBot;
class ScoutDrone;

// Visitor interface: one visit overload per element type.
class FloorVisitor {
public:
    virtual ~FloorVisitor() = default;
    virtual void visit(const WelderBot& welder) = 0;
    virtual void visit(const ScoutDrone& drone) = 0;
};

// Element interface
class Machine {
public:
    virtual ~Machine() = default;
    virtual void accept(FloorVisitor& visitor) const = 0;
};

class WelderBot : public Machine {
public:
    explicit WelderBot(int watts) : watts_(watts) {}
    int watts() const { return watts_; }
    void accept(FloorVisitor& visitor) const override { visitor.visit(*this); }

private:
    int watts_;
};

class ScoutDrone : public Machine {
public:
    explicit ScoutDrone(int rotors) : rotors_(rotors) {}
    int rotors() const { return rotors_; }
    void accept(FloorVisitor& visitor) const override { visitor.visit(*this); }

private:
    int rotors_;
};

// New operations are added as new visitors — no Machine class changes.
class SafetyAuditor : public FloorVisitor {
public:
    void visit(const WelderBot& welder) override { riskScore_ += welder.watts() / 100; }
    void visit(const ScoutDrone& drone) override { riskScore_ += drone.rotors(); }
    int riskScore() const { return riskScore_; }

private:
    int riskScore_ = 0;
};

class ValueAppraiser : public FloorVisitor {
public:
    void visit(const WelderBot& welder) override {
        std::cout << "tag: WelderBot, " << welder.watts() << "W — $12,000\n";
    }
    void visit(const ScoutDrone& drone) override {
        std::cout << "tag: ScoutDrone, " << drone.rotors() << " rotors — $3,500\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Machine>> floor;
    floor.push_back(std::make_unique<WelderBot>(400));
    floor.push_back(std::make_unique<ScoutDrone>(4));

    SafetyAuditor auditor;
    ValueAppraiser appraiser;
    for (const auto& machine : floor) {
        machine->accept(auditor);
        machine->accept(appraiser);
    }
    std::cout << "total risk score: " << auditor.riskScore() << "\n";
    return 0;
}
