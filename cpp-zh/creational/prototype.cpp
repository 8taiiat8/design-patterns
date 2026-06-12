// 🤖 机器人工厂 RoboWorks — 第 5 章：克隆图纸
//
// 故事：从零设计一台机器人要做几个月的研发。所以当客户想要
// "同款焊接机器人，但臂展更长"时，你直接克隆成熟图纸，只改一项参数。
// 档案室里的原版图纸原封不动。
//
// 模式：原型（Prototype）——通过复制现有对象（原型）来创建新对象，
// 而不是从头构建。适用于创建成本高、或代码不应依赖具体类的场景。
//
// 编译：g++ -std=c++17 prototype.cpp -o prototype

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Blueprint {
public:
    virtual ~Blueprint() = default;
    virtual std::unique_ptr<Blueprint> clone() const = 0;
    virtual void review() const = 0;
};

class RobotBlueprint : public Blueprint {
public:
    RobotBlueprint(std::string model, std::string spec)
        : model_(std::move(model)), spec_(std::move(spec)) {}

    std::unique_ptr<Blueprint> clone() const override {
        return std::make_unique<RobotBlueprint>(*this);  // 拷贝构造完成复制
    }

    void tweak(std::string spec) { spec_ = std::move(spec); }

    void review() const override {
        std::cout << "机器人图纸（" << model_ << "：" << spec_ << "）\n";
    }

private:
    std::string model_;
    std::string spec_;
};

class DroneBlueprint : public Blueprint {
public:
    DroneBlueprint(std::string model, int rotors)
        : model_(std::move(model)), rotors_(rotors) {}

    std::unique_ptr<Blueprint> clone() const override {
        return std::make_unique<DroneBlueprint>(*this);
    }

    void review() const override {
        std::cout << "无人机图纸（" << model_ << "，" << rotors_ << " 旋翼）\n";
    }

private:
    std::string model_;
    int rotors_;
};

int main() {
    RobotBlueprint proven("焊接机器人 Mk2", "臂展 1.2 米");

    // 不需要知道具体类型即可克隆图纸。
    std::vector<std::unique_ptr<Blueprint>> archive;
    archive.push_back(proven.clone());
    archive.push_back(std::make_unique<DroneBlueprint>("侦察无人机", 4));
    archive.push_back(archive.back()->clone());  // 通过基类接口克隆

    // 修改副本不会影响成熟的原版。
    auto custom = proven.clone();
    static_cast<RobotBlueprint*>(custom.get())->tweak("臂展 2.0 米，关节加固");

    std::cout << "原版图纸：  ";
    proven.review();
    std::cout << "客户订单：  ";
    custom->review();

    std::cout << "档案室：\n";
    for (const auto& bp : archive) bp->review();
    return 0;
}
