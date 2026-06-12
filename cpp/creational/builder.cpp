// 🤖 RoboWorks — Chapter 4: The Custom Order
//
// STORY: A client never orders a plain robot. It's "tracked chassis, four
// sensors, two arms, night-vision firmware". A constructor with seven
// parameters would be a nightmare, so the configurator assembles each
// robot step by step — and the catalog keeps blueprints (a director) for
// the standard models.
//
// PATTERN: Builder — separate the construction of a complex object from
// its representation, so the same process can create different
// configurations step by step.
//
// Build: g++ -std=c++17 builder.cpp -o builder

#include <iostream>
#include <string>

class Robot {
public:
    std::string chassis;
    int sensors = 0;
    int arms = 0;
    std::string firmware;

    void describe() const {
        std::cout << "Robot{chassis=" << chassis << ", sensors=" << sensors
                  << ", arms=" << arms << ", firmware=" << firmware << "}\n";
    }
};

// Fluent builder: each setter returns *this so calls can be chained.
class RobotBuilder {
public:
    RobotBuilder& chassis(std::string value) { robot_.chassis = std::move(value); return *this; }
    RobotBuilder& sensors(int value) { robot_.sensors = value; return *this; }
    RobotBuilder& arms(int value) { robot_.arms = value; return *this; }
    RobotBuilder& firmware(std::string value) { robot_.firmware = std::move(value); return *this; }

    Robot build() { return robot_; }

private:
    Robot robot_;
};

// The catalog (director): encapsulates well-known build blueprints.
class Catalog {
public:
    static Robot workerBot() {
        return RobotBuilder{}
            .chassis("tracked")
            .sensors(4)
            .arms(2)
            .firmware("heavy-duty v3")
            .build();
    }

    static Robot scoutBot() {
        return RobotBuilder{}
            .chassis("wheeled")
            .sensors(8)
            .arms(0)
            .firmware("night-vision v2")
            .build();
    }
};

int main() {
    // A picky client configures a custom robot step by step.
    Robot custom = RobotBuilder{}.chassis("hexapod").sensors(6).arms(4).firmware("experimental").build();
    custom.describe();

    // Or order straight from the catalog's blueprints.
    Catalog::workerBot().describe();
    Catalog::scoutBot().describe();
    return 0;
}
