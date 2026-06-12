// 🤖 机器人工厂 RoboWorks — 第 18 章：固件回滚
//
// 故事：每次冒险改固件（"实验性激光模块"？）之前，你都会先给机器人
// 的配置拍个快照。一旦升级把功能搞坏，就回滚到上一个快照。
// 快照存在备份保险库里——保险库从不查看快照内容，只负责原样归还。
//
// 模式：备忘录（Memento）——把对象的内部状态捕获到快照中以便日后恢复，
// 且不暴露对象的内部细节。发起人 = 固件配置，备忘录 = 快照，
// 负责人 = 保险库。
//
// 编译：g++ -std=c++17 memento.cpp -o memento

#include <iostream>
#include <string>
#include <vector>

// 发起人：要被快照的对象。
class FirmwareConfig {
public:
    // 备忘录：除发起人之外对所有人不透明。
    class Snapshot {
        friend class FirmwareConfig;
        explicit Snapshot(std::string modules) : modules_(std::move(modules)) {}
        std::string modules_;
    };

    void install(const std::string& module) { modules_ += module; }

    Snapshot save() const { return Snapshot(modules_); }
    void restore(const Snapshot& snapshot) { modules_ = snapshot.modules_; }

    void show() const { std::cout << "固件：「" << modules_ << "」\n"; }

private:
    std::string modules_;
};

// 负责人：保存快照，但不知道里面是什么。
class BackupVault {
public:
    void keep(FirmwareConfig::Snapshot snapshot) { stack_.push_back(std::move(snapshot)); }

    bool rollback(FirmwareConfig& config) {
        if (stack_.empty()) return false;
        config.restore(stack_.back());
        stack_.pop_back();
        return true;
    }

private:
    std::vector<FirmwareConfig::Snapshot> stack_;
};

int main() {
    FirmwareConfig config;
    BackupVault vault;

    config.install("核心 v1.0");
    vault.keep(config.save());

    config.install(" + 导航模块");
    vault.keep(config.save());

    config.install(" + 实验性激光模块");  // 大胆。太大胆了。
    config.show();

    vault.rollback(config);  // 激光模块把夹爪搞坏了
    config.show();

    vault.rollback(config);  // 一路回滚到核心版本
    config.show();
    return 0;
}
