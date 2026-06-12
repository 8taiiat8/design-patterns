// 🤖 机器人工厂 RoboWorks — 第 3 章：产品系列
//
// 故事：工厂出售两个产品系列。工业系列 = 重型底盘 + 液压机械臂；
// 家用系列 = 轻型底盘 + 软抓机械臂。同一系列的零件永远配套——
// 软抓臂装到重型底盘上，第一天就会折断。
//
// 模式：抽象工厂（Abstract Factory）——提供创建"一族相关对象"的接口，
// 而无需指定具体类。适用于同族产品必须配套使用的场景。
//
// 编译：g++ -std=c++17 abstract_factory.cpp -o abstract_factory

#include <iostream>
#include <memory>

// 抽象产品
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

// 具体产品：工业系列
class HeavyChassis : public Chassis {
public:
    void assemble() const override { std::cout << "拼装重型钢制底盘\n"; }
};

class HydraulicArm : public Arm {
public:
    void attach() const override { std::cout << "安装液压机械臂\n"; }
};

// 具体产品：家用系列
class LightChassis : public Chassis {
public:
    void assemble() const override { std::cout << "卡装轻型合金底盘\n"; }
};

class SoftGripArm : public Arm {
public:
    void attach() const override { std::cout << "安装软抓机械臂\n"; }
};

// 抽象工厂：每种产品对应一个创建方法
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

// 生产计划员只依赖抽象工厂接口。
void produceRobot(const RobotSeriesFactory& series) {
    series.createChassis()->assemble();
    series.createArm()->attach();
}

int main() {
    std::cout << "—— 工业系列 ——\n";
    produceRobot(IndustrialSeries{});
    std::cout << "—— 家用系列 ——\n";
    produceRobot(DomesticSeries{});
    return 0;
}
