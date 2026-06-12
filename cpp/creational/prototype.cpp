// 🤖 RoboWorks — Chapter 5: Clone the Blueprint
//
// STORY: Designing a robot from a blank sheet takes months of R&D. So
// when a client wants "the same WelderBot, but with a longer reach", you
// CLONE the proven blueprint and tweak one spec. The original blueprint
// stays untouched in the archive.
//
// PATTERN: Prototype — create new objects by copying an existing object
// (the prototype) instead of building them from scratch. Use when
// creation is expensive or when code shouldn't depend on concrete classes.
//
// Build: g++ -std=c++17 prototype.cpp -o prototype

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Blueprint {
public:
    virtual ~Blueprint() = default;
    virtual std::unique_ptr<Blueprint> clone() const = 0;
    virtual void review() const = 0;
};

class RobotBlueprint : public Blueprint {
public:
    RobotBlueprint(std::string model, std::string spec)
        : model_(std::move(model)), spec_(std::move(spec)) {}

    std::unique_ptr<Blueprint> clone() const override {
        return std::make_unique<RobotBlueprint>(*this);  // copy ctor does the work
    }

    void tweak(std::string spec) { spec_ = std::move(spec); }

    void review() const override {
        std::cout << "RobotBlueprint(" << model_ << ": " << spec_ << ")\n";
    }

private:
    std::string model_;
    std::string spec_;
};

class DroneBlueprint : public Blueprint {
public:
    DroneBlueprint(std::string model, int rotors)
        : model_(std::move(model)), rotors_(rotors) {}

    std::unique_ptr<Blueprint> clone() const override {
        return std::make_unique<DroneBlueprint>(*this);
    }

    void review() const override {
        std::cout << "DroneBlueprint(" << model_ << ", " << rotors_ << " rotors)\n";
    }

private:
    std::string model_;
    int rotors_;
};

int main() {
    RobotBlueprint proven("WelderBot Mk2", "arm reach 1.2m");

    // Clone blueprints without naming the concrete type.
    std::vector<std::unique_ptr<Blueprint>> archive;
    archive.push_back(proven.clone());
    archive.push_back(std::make_unique<DroneBlueprint>("ScoutDrone", 4));
    archive.push_back(archive.back()->clone());  // clone via the base interface

    // Tweaking the copy does not change the proven original.
    auto custom = proven.clone();
    static_cast<RobotBlueprint*>(custom.get())->tweak("arm reach 2.0m, reinforced joints");

    std::cout << "original:     ";
    proven.review();
    std::cout << "client order: ";
    custom->review();

    std::cout << "archive:\n";
    for (const auto& bp : archive) bp->review();
    return 0;
}
