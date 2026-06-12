// 🤖 机器人工厂 RoboWorks — 第 17 章：调度塔
//
// 故事：以前机器人之间直接用无线电互联，车间一片混乱——每台机器人
// 都得记住其他所有机器人的频率。于是你建了调度塔：机器人只向塔台
// 汇报，塔台把消息转发给其他所有机器人。谁也不用知道还有谁在线。
//
// 模式：中介者（Mediator）——用一个对象封装一组对象的交互方式，
// 使它们不再互相直接引用；把多对多关系变成一对多。
//
// 编译：g++ -std=c++17 mediator.cpp -o mediator

#include <iostream>
#include <string>
#include <vector>

class FloorRobot;

// 中介者接口
class DispatchTower {
public:
    virtual ~DispatchTower() = default;
    virtual void relay(const std::string& from, const std::string& message) = 0;
    virtual void registerRobot(FloorRobot* robot) = 0;
};

// 同事类：只认识塔台，不认识其他机器人。
class FloorRobot {
public:
    FloorRobot(std::string callsign, DispatchTower& tower)
        : callsign_(std::move(callsign)), tower_(tower) {
        tower_.registerRobot(this);
    }

    const std::string& callsign() const { return callsign_; }

    void report(const std::string& message) {
        std::cout << callsign_ << " 汇报：" << message << "\n";
        tower_.relay(callsign_, message);
    }

    void receive(const std::string& from, const std::string& message) {
        std::cout << "  " << callsign_ << " 收到 " << from << "：" << message << "\n";
    }

private:
    std::string callsign_;
    DispatchTower& tower_;
};

// 具体中介者：把汇报转发给车间里的其他机器人。
class CentralTower : public DispatchTower {
public:
    void registerRobot(FloorRobot* robot) override { robots_.push_back(robot); }

    void relay(const std::string& from, const std::string& message) override {
        for (FloorRobot* robot : robots_) {
            if (robot->callsign() != from) robot->receive(from, message);
        }
    }

private:
    std::vector<FloorRobot*> robots_;
};

int main() {
    CentralTower tower;
    FloorRobot welder("焊接-01", tower);
    FloorRobot crane("吊装-02", tower);
    FloorRobot drone("无人机-03", tower);

    welder.report("底盘 7 号焊缝完工，可以取件");
    crane.report("正在 B 线取件，请让出通道");
    return 0;
}
