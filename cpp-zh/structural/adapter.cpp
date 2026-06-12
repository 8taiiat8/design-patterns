// 🤖 机器人工厂 RoboWorks — 第 6 章：老焊接臂
//
// 故事：新装配线要求所有机械臂都响应 actuate(task)。但老厂传下来的
// 传奇焊接臂只听得懂 pulseCrank()——而它的焊缝质量至今无人能敌。
// 你不会为它重排整条线，也改不了停产的老零件，
// 于是你做了一个适配器，把老协议接到新接口上。
//
// 模式：适配器（Adapter）——把现有类的接口转换成客户端期望的接口，
// 让本不兼容的类协同工作。
//
// 编译：g++ -std=c++17 adapter.cpp -o adapter

#include <iostream>
#include <memory>
#include <string>

// 装配线期望的接口。
class RoboticArm {
public:
    virtual ~RoboticArm() = default;
    virtual void actuate(const std::string& task) = 0;
};

// 接口不兼容的老零件（被适配者）。假设我们无法修改它。
class LegacyWeldingArm {
public:
    void pulseCrank(const std::string& job) {
        std::cout << "老焊接臂脉冲运转，完成：" << job << "\n";
    }
};

// 适配器实现期望接口，并把调用转发给被适配者。
class LegacyArmAdapter : public RoboticArm {
public:
    void actuate(const std::string& task) override {
        legacy_.pulseCrank(task);  // 翻译调用
    }

private:
    LegacyWeldingArm legacy_;
};

// 原生兼容的现代机械臂，用于对比。
class ServoArm : public RoboticArm {
public:
    void actuate(const std::string& task) override {
        std::cout << "伺服机械臂平滑执行：" << task << "\n";
    }
};

int main() {
    std::unique_ptr<RoboticArm> assemblyLine[] = {
        std::make_unique<ServoArm>(),
        std::make_unique<LegacyArmAdapter>(),  // 老零件躲在同一接口后面
    };

    for (auto& arm : assemblyLine) {
        arm->actuate("焊接底盘 7 号焊缝");
    }
    return 0;
}
