// 🤖 RoboWorks — Chapter 7: Any Robot, Any Controller
//
// STORY: You build welders and drones; they can be driven by a remote
// operator or by the autonomous AI. Without care you'd need RemoteWelder,
// AutonomousWelder, RemoteDrone, AutonomousDrone... a class for every
// combination. Instead, each ROBOT holds a reference to a CONTROLLER:
// new robots and new controllers can now be added independently.
//
// PATTERN: Bridge — decouple an abstraction (Robot) from its
// implementation (Controller) so the two hierarchies vary independently.
//
// Build: g++ -std=c++17 bridge.cpp -o bridge

#include <iostream>

// Implementation hierarchy
class Controller {
public:
    virtual ~Controller() = default;
    virtual void drive(int power) const = 0;
};

class RemoteOperator : public Controller {
public:
    void drive(int power) const override {
        std::cout << "remote operator steers carefully at power " << power << "\n";
    }
};

class AutonomousAI : public Controller {
public:
    void drive(int power) const override {
        std::cout << "autonomous AI optimizes the route at power " << power << "\n";
    }
};

// Abstraction hierarchy: holds the "bridge" to the implementation.
class Robot {
public:
    explicit Robot(const Controller& controller) : controller_(controller) {}
    virtual ~Robot() = default;
    virtual void operate() const = 0;

protected:
    const Controller& controller_;
};

class WelderBot : public Robot {
public:
    WelderBot(const Controller& controller, int power)
        : Robot(controller), power_(power) {}

    void operate() const override { controller_.drive(power_); }

    void boostPower() { ++power_; }

private:
    int power_;
};

int main() {
    RemoteOperator human;
    AutonomousAI ai;

    // Any robot can be paired with any controller at run time.
    WelderBot nightShift(ai, 3);
    WelderBot delicateJob(human, 3);
    nightShift.operate();
    delicateJob.operate();

    nightShift.boostPower();
    nightShift.operate();
    return 0;
}
