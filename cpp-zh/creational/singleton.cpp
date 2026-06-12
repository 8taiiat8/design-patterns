// 🤖 机器人工厂 RoboWorks — 第 1 章：唯一的中央控制器
//
// 故事：你的工厂只有一台中央控制器（MCU）。所有装配线都向同一台 MCU
// 汇报——如果有两台，它们会发出互相矛盾的指令，工厂就乱套了。
// MCU 在第一次被使用时启动，之后所有人共享同一台。
//
// 模式：单例（Singleton）——确保一个类只有一个实例，并提供全局访问点。
// 适用于全厂只需要一个对象来协调的场景（配置、日志、控制核心）。
//
// C++ 要点：
// - 函数内局部 static 变量（"Meyers 单例"）是惰性初始化的，
//   且自 C++11 起线程安全。
// - 删除拷贝/移动操作，防止实例被复制。
//
// 编译：g++ -std=c++17 singleton.cpp -o singleton

#include <iostream>
#include <string>

class MasterControlUnit {
public:
    // 唯一的全局访问点。
    static MasterControlUnit& instance() {
        static MasterControlUnit mcu;  // 首次使用时创建，线程安全
        return mcu;
    }

    MasterControlUnit(const MasterControlUnit&) = delete;
    MasterControlUnit& operator=(const MasterControlUnit&) = delete;

    void logTask(const std::string& task) {
        ++tasks_;
        std::cout << "[MCU 任务 #" << tasks_ << "] " << task << "\n";
    }

private:
    MasterControlUnit() = default;  // 私有构造：谁也造不出第二台 MCU
    int tasks_ = 0;
};

int main() {
    MasterControlUnit::instance().logTask("启动 A 号装配线");
    MasterControlUnit::instance().logTask("校准焊接激光");

    // 两条装配线汇报给的是同一个控制核心。
    MasterControlUnit& lineA = MasterControlUnit::instance();
    MasterControlUnit& lineB = MasterControlUnit::instance();
    std::cout << "同一台 MCU？" << std::boolalpha << (&lineA == &lineB) << "\n";
    return 0;
}
