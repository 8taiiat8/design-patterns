// 🤖 机器人工厂 RoboWorks — 第 9 章：升级模块
//
// 故事：装甲板、太阳能充电器、AI 语音模块……客户把升级件以各种组合
// 拧到基础机器人上。你不可能为每种组合写一个"装甲太阳能会说话机器人"
// 类——正确做法是每个升级模块"包裹"下面的机器人，
// 加上自己的配置说明和价格。
//
// 模式：装饰器（Decorator）——通过用共享同一接口的对象层层包装，
// 在运行时为对象动态附加职责。
//
// 编译：g++ -std=c++17 decorator.cpp -o decorator

#include <iostream>
#include <memory>
#include <string>

// 组件接口
class Robot {
public:
    virtual ~Robot() = default;
    virtual std::string specs() const = 0;
    virtual double cost() const = 0;
};

// 具体组件：被装饰的机器人。
class BasicBot : public Robot {
public:
    std::string specs() const override { return "基础机器人"; }
    double cost() const override { return 2000.0; }
};

// 装饰器基类：包裹一个 Robot，默认原样转发。
class UpgradeDecorator : public Robot {
public:
    explicit UpgradeDecorator(std::unique_ptr<Robot> inner) : inner_(std::move(inner)) {}

    std::string specs() const override { return inner_->specs(); }
    double cost() const override { return inner_->cost(); }

private:
    std::unique_ptr<Robot> inner_;
};

class ArmorPlating : public UpgradeDecorator {
public:
    using UpgradeDecorator::UpgradeDecorator;
    std::string specs() const override { return UpgradeDecorator::specs() + " + 装甲板"; }
    double cost() const override { return UpgradeDecorator::cost() + 500.0; }
};

class SolarCharger : public UpgradeDecorator {
public:
    using UpgradeDecorator::UpgradeDecorator;
    std::string specs() const override { return UpgradeDecorator::specs() + " + 太阳能充电器"; }
    double cost() const override { return UpgradeDecorator::cost() + 200.0; }
};

class AiVoice : public UpgradeDecorator {
public:
    using UpgradeDecorator::UpgradeDecorator;
    std::string specs() const override { return UpgradeDecorator::specs() + " + AI 语音"; }
    double cost() const override { return UpgradeDecorator::cost() + 700.0; }
};

int main() {
    // 运行时任意叠加升级模块。
    std::unique_ptr<Robot> order = std::make_unique<AiVoice>(
        std::make_unique<SolarCharger>(std::make_unique<ArmorPlating>(std::make_unique<BasicBot>())));

    std::cout << order->specs() << "，售价 $" << order->cost() << "\n";

    std::unique_ptr<Robot> plain = std::make_unique<BasicBot>();
    std::cout << plain->specs() << "，售价 $" << plain->cost() << "\n";
    return 0;
}
