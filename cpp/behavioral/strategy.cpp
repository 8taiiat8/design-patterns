// 🤖 RoboWorks — Chapter 21: The Power Modes
//
// STORY: The same robot burns different energy depending on the moment:
// full power in the day rush, half power in eco mode, 10% off in night
// mode. The robot doesn't care WHICH rule is active — it just asks the
// current power strategy what to draw, and you can swap the strategy when
// the night shift starts.
//
// PATTERN: Strategy — define a family of interchangeable algorithms and
// make them swappable at run time behind a common interface. In modern
// C++, std::function offers a lightweight alternative for simple cases —
// both styles are shown.
//
// Build: g++ -std=c++17 strategy.cpp -o strategy

#include <functional>
#include <iostream>
#include <memory>

// Classic OO style: strategy interface + concrete strategies.
class PowerStrategy {
public:
    virtual ~PowerStrategy() = default;
    virtual double draw(double baseWatts) const = 0;
};

class PerformanceMode : public PowerStrategy {
public:
    double draw(double baseWatts) const override { return baseWatts; }
};

class EcoMode : public PowerStrategy {
public:
    double draw(double baseWatts) const override { return baseWatts * 0.5; }
};

class NightMode : public PowerStrategy {
public:
    double draw(double baseWatts) const override { return baseWatts * 0.9; }
};

// Context: the robot is configured with a strategy, unaware of which one.
class Robot {
public:
    explicit Robot(std::unique_ptr<PowerStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<PowerStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void runTask(double baseWatts) const {
        std::cout << "task base " << baseWatts << "W -> draws "
                  << strategy_->draw(baseWatts) << "W\n";
    }

private:
    std::unique_ptr<PowerStrategy> strategy_;
};

int main() {
    Robot robot(std::make_unique<PerformanceMode>());
    robot.runTask(400.0);

    robot.setStrategy(std::make_unique<EcoMode>());  // the grid bill arrived
    robot.runTask(400.0);

    robot.setStrategy(std::make_unique<NightMode>());
    robot.runTask(400.0);

    // Modern alternative: a std::function works as a strategy too.
    std::function<double(double)> standby = [](double baseWatts) { return baseWatts * 0.1; };
    std::cout << "standby: draws " << standby(400.0) << "W\n";
    return 0;
}
