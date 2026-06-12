// 🤖 RoboWorks — Chapter 2: The Assembly Lines
//
// STORY: Demand grows, so you open assembly lines. Every line follows the
// same roll-out routine (assemble, test, ship). What differs is WHICH
// robot each line builds: the welder line produces WelderBots, the
// cleaner line produces CleanerBots.
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
class Robot {
public:
    virtual ~Robot() = default;
    virtual std::string describe() const = 0;
};

class WelderBot : public Robot {
public:
    std::string describe() const override { return "a WelderBot with twin plasma torches"; }
};

class CleanerBot : public Robot {
public:
    std::string describe() const override { return "a CleanerBot with spinning brushes"; }
};

// Creator: the roll-out routine relies only on the Robot interface;
// the factory method defers the choice of concrete robot to subclasses.
class AssemblyLine {
public:
    virtual ~AssemblyLine() = default;

    void rollOut() const {
        auto robot = buildRobot();  // the factory method
        std::cout << "Line ships " << robot->describe() << "\n";
    }

protected:
    virtual std::unique_ptr<Robot> buildRobot() const = 0;
};

class WelderLine : public AssemblyLine {
protected:
    std::unique_ptr<Robot> buildRobot() const override {
        return std::make_unique<WelderBot>();
    }
};

class CleanerLine : public AssemblyLine {
protected:
    std::unique_ptr<Robot> buildRobot() const override {
        return std::make_unique<CleanerBot>();
    }
};

int main() {
    WelderLine lineA;
    CleanerLine lineB;
    lineA.rollOut();
    lineB.rollOut();
    return 0;
}
