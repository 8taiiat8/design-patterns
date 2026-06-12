// 🤖 机器人工厂 RoboWorks — 第 7 章：任意机器人配任意控制器
//
// 故事：你生产焊接机器人和无人机；它们可以由远程操作员驾驶，也可以
// 由自主 AI 驾驶。不加设计的话就需要"远程焊接机器人、自主焊接机器人、
// 远程无人机、自主无人机"……每种组合一个类。正确做法：每台机器人
// 持有一个控制器的引用——新机器人和新控制器从此可以独立增加。
//
// 模式：桥接（Bridge）——把抽象（Robot）与实现（Controller）解耦，
// 让两个继承体系独立变化。
//
// 编译：g++ -std=c++17 bridge.cpp -o bridge

#include <iostream>

// 实现体系
class Controller {
public:
    virtual ~Controller() = default;
    virtual void drive(int power) const = 0;
};

class RemoteOperator : public Controller {
public:
    void drive(int power) const override {
        std::cout << "远程操作员小心驾驶，功率 " << power << "\n";
    }
};

class AutonomousAI : public Controller {
public:
    void drive(int power) const override {
        std::cout << "自主 AI 优化路线，功率 " << power << "\n";
    }
};

// 抽象体系：持有指向实现的"桥"。
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

    // 任何机器人都能在运行时搭配任何控制器。
    WelderBot nightShift(ai, 3);
    WelderBot delicateJob(human, 3);
    nightShift.operate();
    delicateJob.operate();

    nightShift.boostPower();
    nightShift.operate();
    return 0;
}
