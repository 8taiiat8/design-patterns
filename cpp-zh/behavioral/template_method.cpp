// 🤖 机器人工厂 RoboWorks — 第 22 章：开机流程
//
// 故事：每台机器人都按同样的顺序开机：上电、自检、加载驱动、宣告
// 就绪。流程本身永远不变——但每个机型"如何自检"（校准焊接激光、
// 启动旋翼）以及如何宣告就绪各不相同。
//
// 模式：模板方法（Template Method）——在基类中定义算法骨架，
// 让子类重写特定步骤，而不改变算法的整体结构。
//
// 编译：g++ -std=c++17 template_method.cpp -o template_method

#include <iostream>

// 基类拥有开机流程的骨架。
class BootSequence {
public:
    virtual ~BootSequence() = default;

    // 模板方法：步骤顺序固定，故意设计为非虚函数。
    void boot() {
        powerOn();
        selfTest();
        loadDrivers();
        announceReady();  // 带默认实现的可选钩子
    }

protected:
    // 子类必须提供的步骤。
    virtual void selfTest() = 0;

    // 钩子：有合理默认值，需要时才重写。
    virtual void announceReady() { std::cout << "  （标准就绪提示音）\n"; }

private:
    // 所有机器人完全相同的步骤保持私有且固定。
    void powerOn() { std::cout << "  上电\n"; }
    void loadDrivers() { std::cout << "  加载驱动\n"; }
};

class WelderBot : public BootSequence {
protected:
    void selfTest() override { std::cout << "  校准焊接激光\n"; }
    void announceReady() override { std::cout << "  宣告：焊接系统在线\n"; }
};

class ScoutDrone : public BootSequence {
protected:
    void selfTest() override { std::cout << "  启动旋翼\n"; }
};

int main() {
    std::cout << "焊接机器人开机：\n";
    WelderBot{}.boot();

    std::cout << "侦察无人机开机：\n";
    ScoutDrone{}.boot();
    return 0;
}
