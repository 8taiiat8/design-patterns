// 🤖 RoboWorks — Chapter 3: The Product Series
//
// STORY: RoboWorks sells two product series. The Industrial series pairs
// a heavy chassis WITH hydraulic arms; the Domestic series pairs a light
// chassis WITH soft-grip arms. Parts from one series always match — a
// soft-grip arm on a heavy chassis would snap off on day one.
//
// PATTERN: Abstract Factory — provide an interface for creating families
// of related objects without specifying their concrete classes. Use when
// products from one family must be used together.
//
// Build: g++ -std=c++17 abstract_factory.cpp -o abstract_factory

#include <iostream>
#include <memory>

// Abstract products
class Chassis {
public:
    virtual ~Chassis() = default;
    virtual void assemble() const = 0;
};

class Arm {
public:
    virtual ~Arm() = default;
    virtual void attach() const = 0;
};

// Concrete products: the Industrial series
class HeavyChassis : public Chassis {
public:
    void assemble() const override { std::cout << "bolting together a heavy steel chassis\n"; }
};

class HydraulicArm : public Arm {
public:
    void attach() const override { std::cout << "attaching a hydraulic arm\n"; }
};

// Concrete products: the Domestic series
class LightChassis : public Chassis {
public:
    void assemble() const override { std::cout << "clipping together a light alloy chassis\n"; }
};

class SoftGripArm : public Arm {
public:
    void attach() const override { std::cout << "attaching a soft-grip arm\n"; }
};

// Abstract factory: one creation method per product type
class RobotSeriesFactory {
public:
    virtual ~RobotSeriesFactory() = default;
    virtual std::unique_ptr<Chassis> createChassis() const = 0;
    virtual std::unique_ptr<Arm> createArm() const = 0;
};

class IndustrialSeries : public RobotSeriesFactory {
public:
    std::unique_ptr<Chassis> createChassis() const override { return std::make_unique<HeavyChassis>(); }
    std::unique_ptr<Arm> createArm() const override { return std::make_unique<HydraulicArm>(); }
};

class DomesticSeries : public RobotSeriesFactory {
public:
    std::unique_ptr<Chassis> createChassis() const override { return std::make_unique<LightChassis>(); }
    std::unique_ptr<Arm> createArm() const override { return std::make_unique<SoftGripArm>(); }
};

// The production planner only depends on the abstract factory interface.
void produceRobot(const RobotSeriesFactory& series) {
    series.createChassis()->assemble();
    series.createArm()->attach();
}

int main() {
    std::cout << "-- Industrial series --\n";
    produceRobot(IndustrialSeries{});
    std::cout << "-- Domestic series --\n";
    produceRobot(DomesticSeries{});
    return 0;
}
