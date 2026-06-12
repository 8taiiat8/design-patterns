// 🤖 机器人工厂 RoboWorks — 第 11 章：千架无人机，三张图纸
//
// 故事：无人机机库停着上千架飞机，但工厂只生产几个机型。如果每架
// 无人机内部都存一份完整图纸，仓库数据库就爆了。所以每架飞机只存
// 自己的序列号和停机位，外加一个指向共享机型定义的"指针"。
//
// 模式：享元（Flyweight）——在大量对象之间共享公共（内在）状态；
// 变化的（外在）状态由外部传入。
//
// 编译：g++ -std=c++17 flyweight.cpp -o flyweight

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// 享元：众多无人机共享的重量级内在状态（机型名称和完整图纸）。
class RobotModel {
public:
    RobotModel(std::string name, std::string blueprint)
        : name_(std::move(name)), blueprint_(std::move(blueprint)) {}

    // 外在状态（序列号、停机位）由调用方提供。
    void printUnit(int serial, int bay) const {
        std::cout << "编号 #" << serial << "（" << bay << " 号停机位）："
                  << name_ << " — " << blueprint_ << "\n";
    }

private:
    std::string name_;
    std::string blueprint_;
};

// 享元工厂：缓存并复用 RobotModel 实例。
class RobotModelFactory {
public:
    const RobotModel& get(const std::string& name, const std::string& blueprint) {
        auto it = cache_.find(name);
        if (it == cache_.end()) {
            it = cache_.emplace(name, std::make_unique<RobotModel>(name, blueprint)).first;
            std::cout << "（新建享元：" << name << "）\n";
        }
        return *it->second;
    }

    size_t uniqueModels() const { return cache_.size(); }

private:
    std::map<std::string, std::unique_ptr<RobotModel>> cache_;
};

// 上下文对象：很小——只有外在状态加一个共享享元。
struct DroneUnit {
    int serial;
    int bay;
    const RobotModel* model;
};

int main() {
    RobotModelFactory factory;
    std::vector<DroneUnit> hall;

    // 六架无人机，内存中却只有两个机型对象。
    hall.push_back({101, 1, &factory.get("侦察无人机", "4 旋翼，广角摄像头")});
    hall.push_back({102, 3, &factory.get("侦察无人机", "4 旋翼，广角摄像头")});
    hall.push_back({103, 2, &factory.get("货运无人机", "8 旋翼，5 公斤载重")});
    hall.push_back({104, 5, &factory.get("侦察无人机", "4 旋翼，广角摄像头")});
    hall.push_back({105, 4, &factory.get("货运无人机", "8 旋翼，5 公斤载重")});
    hall.push_back({106, 1, &factory.get("侦察无人机", "4 旋翼，广角摄像头")});

    for (const auto& unit : hall) unit.model->printUnit(unit.serial, unit.bay);
    std::cout << "无人机数量：" << hall.size()
              << "，机型享元数量：" << factory.uniqueModels() << "\n";
    return 0;
}
