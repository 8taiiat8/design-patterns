// 🤖 机器人工厂 RoboWorks — 第 2 章：装配线
//
// 故事：订单越来越多，你开设了多条装配线。每条线的下线流程都一样
// （组装、测试、出厂），不同的是每条线生产"哪种"机器人：
// 焊接线生产焊接机器人，清洁线生产清洁机器人。
//
// 模式：工厂方法（Factory Method）——定义创建对象的接口，
// 但由子类决定实例化哪个具体类。适用于基类无法预知要创建哪种对象的场景。
//
// 编译：g++ -std=c++17 factory_method.cpp -o factory_method

#include <iostream>
#include <memory>
#include <string>

// 产品接口
class Robot {
public:
    virtual ~Robot() = default;
    virtual std::string describe() const = 0;
};

class WelderBot : public Robot {
public:
    std::string describe() const override { return "一台双等离子焊枪的焊接机器人"; }
};

class CleanerBot : public Robot {
public:
    std::string describe() const override { return "一台带旋转刷头的清洁机器人"; }
};

// 创建者：下线流程只依赖 Robot 接口；
// 工厂方法把"造哪种机器人"的决定推迟给子类。
class AssemblyLine {
public:
    virtual ~AssemblyLine() = default;

    void rollOut() const {
        auto robot = buildRobot();  // 工厂方法
        std::cout << "装配线下线：" << robot->describe() << "\n";
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
