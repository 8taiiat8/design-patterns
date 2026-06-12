// 🤖 RoboWorks — Chapter 18: The Firmware Rollback
//
// STORY: Before every risky firmware tweak ("experimental laser module"?)
// you snapshot the robot's config. When an update bricks the behavior,
// you roll back to the last snapshot. The snapshots sit in the backup
// vault — the vault never reads them, it just hands them back.
//
// PATTERN: Memento — capture an object's internal state in a snapshot so
// it can be restored later, without exposing the object's internals.
// Originator = firmware config, memento = snapshot, caretaker = vault.
//
// Build: g++ -std=c++17 memento.cpp -o memento

#include <iostream>
#include <string>
#include <vector>

// Originator: the object whose state we want to snapshot.
class FirmwareConfig {
public:
    // Memento: opaque to everyone except the originator.
    class Snapshot {
        friend class FirmwareConfig;
        explicit Snapshot(std::string modules) : modules_(std::move(modules)) {}
        std::string modules_;
    };

    void install(const std::string& module) { modules_ += module; }

    Snapshot save() const { return Snapshot(modules_); }
    void restore(const Snapshot& snapshot) { modules_ = snapshot.modules_; }

    void show() const { std::cout << "firmware: \"" << modules_ << "\"\n"; }

private:
    std::string modules_;
};

// Caretaker: stores snapshots without knowing what's inside them.
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

    config.install("core v1.0");
    vault.keep(config.save());

    config.install(" + nav module");
    vault.keep(config.save());

    config.install(" + experimental laser module");  // bold. too bold.
    config.show();

    vault.rollback(config);  // the laser module bricked the gripper
    config.show();

    vault.rollback(config);  // all the way back to core
    config.show();
    return 0;
}
