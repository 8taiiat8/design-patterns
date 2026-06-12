// 🤖 RoboWorks — Chapter 17: The Dispatch Tower
//
// STORY: When robots radioed each other directly, the factory floor was
// chaos — every robot needed every other robot's frequency. So you built
// the dispatch tower: robots report INTO the tower, and it relays the
// message to everyone else. No robot needs to know who else is online.
//
// PATTERN: Mediator — define an object that encapsulates how a set of
// objects interact, so they don't reference each other directly; turns
// many-to-many links into one-to-many.
//
// Build: g++ -std=c++17 mediator.cpp -o mediator

#include <iostream>
#include <string>
#include <vector>

class FloorRobot;

// Mediator interface
class DispatchTower {
public:
    virtual ~DispatchTower() = default;
    virtual void relay(const std::string& from, const std::string& message) = 0;
    virtual void registerRobot(FloorRobot* robot) = 0;
};

// Colleague: only knows the tower, not the other robots.
class FloorRobot {
public:
    FloorRobot(std::string callsign, DispatchTower& tower)
        : callsign_(std::move(callsign)), tower_(tower) {
        tower_.registerRobot(this);
    }

    const std::string& callsign() const { return callsign_; }

    void report(const std::string& message) {
        std::cout << callsign_ << " reports: " << message << "\n";
        tower_.relay(callsign_, message);
    }

    void receive(const std::string& from, const std::string& message) {
        std::cout << "  " << callsign_ << " receives " << from << ": " << message << "\n";
    }

private:
    std::string callsign_;
    DispatchTower& tower_;
};

// Concrete mediator: relays reports to every other robot on the floor.
class CentralTower : public DispatchTower {
public:
    void registerRobot(FloorRobot* robot) override { robots_.push_back(robot); }

    void relay(const std::string& from, const std::string& message) override {
        for (FloorRobot* robot : robots_) {
            if (robot->callsign() != from) robot->receive(from, message);
        }
    }

private:
    std::vector<FloorRobot*> robots_;
};

int main() {
    CentralTower tower;
    FloorRobot welder("Welder-01", tower);
    FloorRobot crane("Crane-02", tower);
    FloorRobot drone("Drone-03", tower);

    welder.report("chassis seam #7 finished, ready for pickup");
    crane.report("picking up at line B, clear the aisle");
    return 0;
}
