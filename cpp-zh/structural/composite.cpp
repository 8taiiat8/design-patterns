// 🤖 机器人工厂 RoboWorks — 第 8 章：组件套组件
//
// 故事：机器人不是一个零件，而是组件里套组件：躯干总成包含机械臂
// 总成，机械臂总成包含伺服电机和夹爪。成本工程师想对任何节点——
// 一颗螺栓也好、整个躯干也好——问同一个问题："这个多少钱？"
//
// 模式：组合（Composite）——把对象组合成树形结构，
// 让客户端统一对待单个零件和整个总成。
//
// 编译：g++ -std=c++17 composite.cpp -o composite

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 组件：单个零件和整个总成的公共接口。
class PartComponent {
public:
    explicit PartComponent(std::string name) : name_(std::move(name)) {}
    virtual ~PartComponent() = default;

    virtual long costCents() const = 0;
    virtual void print(int indent) const = 0;

protected:
    std::string name_;
};

// 叶子
class Part : public PartComponent {
public:
    Part(std::string name, long costCents)
        : PartComponent(std::move(name)), costCents_(costCents) {}

    long costCents() const override { return costCents_; }

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "- " << name_
                  << "（$" << costCents_ / 100.0 << "）\n";
    }

private:
    long costCents_;
};

// 组合：持有子节点，把操作转发给它们。
class Assembly : public PartComponent {
public:
    explicit Assembly(std::string name) : PartComponent(std::move(name)) {}

    void add(std::unique_ptr<PartComponent> child) {
        children_.push_back(std::move(child));
    }

    long costCents() const override {
        long total = 0;
        for (const auto& child : children_) total += child->costCents();
        return total;
    }

    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << "+ " << name_ << "\n";
        for (const auto& child : children_) child->print(indent + 2);
    }

private:
    std::vector<std::unique_ptr<PartComponent>> children_;
};

int main() {
    auto torso = std::make_unique<Assembly>("躯干总成");
    torso->add(std::make_unique<Part>("钢制框架", 12000));

    auto arm = std::make_unique<Assembly>("机械臂总成");
    arm->add(std::make_unique<Part>("伺服电机", 4500));
    arm->add(std::make_unique<Part>("夹爪", 3000));
    torso->add(std::move(arm));

    torso->print(0);
    std::cout << "总成本：$" << torso->costCents() / 100.0 << "\n";
    return 0;
}
