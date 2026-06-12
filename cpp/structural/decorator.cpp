// 🤖 RoboWorks — Chapter 9: The Upgrade Modules
//
// STORY: Armor plating. Solar charger. AI voice module. Clients bolt
// upgrades onto the base bot in every combination imaginable. You are NOT
// creating an ArmoredSolarTalkingBot class for each combo — instead every
// upgrade WRAPS the robot underneath and adds its own spec and price.
//
// PATTERN: Decorator — attach additional responsibilities to an object
// dynamically by wrapping it in objects that share its interface.
//
// Build: g++ -std=c++17 decorator.cpp -o decorator

#include <iostream>
#include <memory>
#include <string>

// Component interface
class Robot {
public:
    virtual ~Robot() = default;
    virtual std::string specs() const = 0;
    virtual double cost() const = 0;
};

// Concrete component: the robot being decorated.
class BasicBot : public Robot {
public:
    std::string specs() const override { return "basic bot"; }
    double cost() const override { return 2000.0; }
};

// Base decorator: wraps a Robot and delegates by default.
class UpgradeDecorator : public Robot {
public:
    explicit UpgradeDecorator(std::unique_ptr<Robot> inner) : inner_(std::move(inner)) {}

    std::string specs() const override { return inner_->specs(); }
    double cost() const override { return inner_->cost(); }

private:
    std::unique_ptr<Robot> inner_;
};

class ArmorPlating : public UpgradeDecorator {
public:
    using UpgradeDecorator::UpgradeDecorator;
    std::string specs() const override { return UpgradeDecorator::specs() + " + armor plating"; }
    double cost() const override { return UpgradeDecorator::cost() + 500.0; }
};

class SolarCharger : public UpgradeDecorator {
public:
    using UpgradeDecorator::UpgradeDecorator;
    std::string specs() const override { return UpgradeDecorator::specs() + " + solar charger"; }
    double cost() const override { return UpgradeDecorator::cost() + 200.0; }
};

class AiVoice : public UpgradeDecorator {
public:
    using UpgradeDecorator::UpgradeDecorator;
    std::string specs() const override { return UpgradeDecorator::specs() + " + AI voice"; }
    double cost() const override { return UpgradeDecorator::cost() + 700.0; }
};

int main() {
    // Stack upgrades in any combination at run time.
    std::unique_ptr<Robot> order = std::make_unique<AiVoice>(
        std::make_unique<SolarCharger>(std::make_unique<ArmorPlating>(std::make_unique<BasicBot>())));

    std::cout << order->specs() << " costs $" << order->cost() << "\n";

    std::unique_ptr<Robot> plain = std::make_unique<BasicBot>();
    std::cout << plain->specs() << " costs $" << plain->cost() << "\n";
    return 0;
}
