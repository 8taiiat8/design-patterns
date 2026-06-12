// 🤖 机器人工厂 RoboWorks — 第 21 章：电源模式
//
// 故事：同一台机器人在不同时刻耗电不同：白班高峰满功率，节能模式
// 半功率，夜间模式九折。机器人不关心当前是哪条规则——它只问当前的
// 电源策略该用多少电；夜班开始时，你把策略一换就行。
//
// 模式：策略（Strategy）——定义一族可互换的算法，在运行时通过统一
// 接口切换。在现代 C++ 中，简单场景也可以用 std::function 实现轻量
// 策略——两种风格都在下面演示。
//
// 编译：g++ -std=c++17 strategy.cpp -o strategy

#include <functional>
#include <iostream>
#include <memory>

// 经典 OO 风格：策略接口 + 具体策略。
class PowerStrategy {
public:
    virtual ~PowerStrategy() = default;
    virtual double draw(double baseWatts) const = 0;
};

class PerformanceMode : public PowerStrategy {
public:
    double draw(double baseWatts) const override { return baseWatts; }
};

class EcoMode : public PowerStrategy {
public:
    double draw(double baseWatts) const override { return baseWatts * 0.5; }
};

class NightMode : public PowerStrategy {
public:
    double draw(double baseWatts) const override { return baseWatts * 0.9; }
};

// 上下文：机器人配置了某个策略，但不知道具体是哪一个。
class Robot {
public:
    explicit Robot(std::unique_ptr<PowerStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<PowerStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void runTask(double baseWatts) const {
        std::cout << "任务基准 " << baseWatts << " 瓦 -> 实际消耗 "
                  << strategy_->draw(baseWatts) << " 瓦\n";
    }

private:
    std::unique_ptr<PowerStrategy> strategy_;
};

int main() {
    Robot robot(std::make_unique<PerformanceMode>());
    robot.runTask(400.0);

    robot.setStrategy(std::make_unique<EcoMode>());  // 电费账单到了
    robot.runTask(400.0);

    robot.setStrategy(std::make_unique<NightMode>());
    robot.runTask(400.0);

    // 现代替代方案：std::function 也能当策略用。
    std::function<double(double)> standby = [](double baseWatts) { return baseWatts * 0.1; };
    std::cout << "待机模式：消耗 " << standby(400.0) << " 瓦\n";
    return 0;
}
