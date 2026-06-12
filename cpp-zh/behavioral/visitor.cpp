// 🤖 机器人工厂 RoboWorks — 第 23 章：巡检员
//
// 故事：今天有两位巡检员到车间：安全审计员统计功率风险，估价师
// 给设备贴价值标签。设备本身（焊接机器人、无人机）不需要任何修改——
// 每台设备只是"接待"（accept）巡检员，巡检员对每种设备各干各的活。
// 下个月来一位新巡检员，也不用动任何设备类。
//
// 模式：访问者（Visitor）——把作用于对象结构中各元素的操作独立出来，
// 让你在不修改元素类的情况下新增操作。
// 核心机制是 accept()/visit() 的双重分派。
//
// 编译：g++ -std=c++17 visitor.cpp -o visitor

#include <iostream>
#include <memory>
#include <vector>

class WelderBot;
class ScoutDrone;

// 访问者接口：每种元素类型一个 visit 重载。
class FloorVisitor {
public:
    virtual ~FloorVisitor() = default;
    virtual void visit(const WelderBot& welder) = 0;
    virtual void visit(const ScoutDrone& drone) = 0;
};

// 元素接口
class Machine {
public:
    virtual ~Machine() = default;
    virtual void accept(FloorVisitor& visitor) const = 0;
};

class WelderBot : public Machine {
public:
    explicit WelderBot(int watts) : watts_(watts) {}
    int watts() const { return watts_; }
    void accept(FloorVisitor& visitor) const override { visitor.visit(*this); }

private:
    int watts_;
};

class ScoutDrone : public Machine {
public:
    explicit ScoutDrone(int rotors) : rotors_(rotors) {}
    int rotors() const { return rotors_; }
    void accept(FloorVisitor& visitor) const override { visitor.visit(*this); }

private:
    int rotors_;
};

// 新操作以新访问者的形式加入——设备类一行不改。
class SafetyAuditor : public FloorVisitor {
public:
    void visit(const WelderBot& welder) override { riskScore_ += welder.watts() / 100; }
    void visit(const ScoutDrone& drone) override { riskScore_ += drone.rotors(); }
    int riskScore() const { return riskScore_; }

private:
    int riskScore_ = 0;
};

class ValueAppraiser : public FloorVisitor {
public:
    void visit(const WelderBot& welder) override {
        std::cout << "标签：焊接机器人，" << welder.watts() << " 瓦 — $12,000\n";
    }
    void visit(const ScoutDrone& drone) override {
        std::cout << "标签：侦察无人机，" << drone.rotors() << " 旋翼 — $3,500\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Machine>> floor;
    floor.push_back(std::make_unique<WelderBot>(400));
    floor.push_back(std::make_unique<ScoutDrone>(4));

    SafetyAuditor auditor;
    ValueAppraiser appraiser;
    for (const auto& machine : floor) {
        machine->accept(auditor);
        machine->accept(appraiser);
    }
    std::cout << "总风险分：" << auditor.riskScore() << "\n";
    return 0;
}
