// 🤖 机器人工厂 RoboWorks — 第 20 章：机器人的工作模式
//
// 故事：车间机器人有不同的"模式"。空闲时它接受任务；忙碌时再派任务
// 只会触发一声不耐烦的蜂鸣，但按下"完成"就交付任务并回到空闲。
// 与其写一个围绕状态标志的巨型 if/else，不如让每个模式都成为一个类。
//
// 模式：状态（State）——把行为委托给状态对象，并在状态转换时更换它，
// 让对象在内部状态改变时改变自己的行为。
//
// 编译：g++ -std=c++17 state.cpp -o state

#include <iostream>
#include <memory>

class FloorRobot;

// 状态接口：机器人能接收的每种事件对应一个方法。
class RobotState {
public:
    virtual ~RobotState() = default;
    virtual void assignTask(FloorRobot& robot) = 0;
    virtual void completeTask(FloorRobot& robot) = 0;
};

class FloorRobot {
public:
    FloorRobot();

    void assignTask();
    void completeTask();
    void setState(std::unique_ptr<RobotState> state) { state_ = std::move(state); }

private:
    std::unique_ptr<RobotState> state_;
};

// 具体状态
class BusyState : public RobotState {
public:
    void assignTask(FloorRobot&) override {
        std::cout << "机器人蜂鸣：已经在忙了\n";
    }
    void completeTask(FloorRobot& robot) override;
};

class IdleState : public RobotState {
public:
    void assignTask(FloorRobot& robot) override {
        std::cout << "任务已接受，电机启动\n";
        robot.setState(std::make_unique<BusyState>());
    }
    void completeTask(FloorRobot&) override {
        std::cout << "没有任务可完成，机器人空闲中\n";
    }
};

void BusyState::completeTask(FloorRobot& robot) {
    std::cout << "任务完成，回到空闲\n";
    robot.setState(std::make_unique<IdleState>());
}

FloorRobot::FloorRobot() : state_(std::make_unique<IdleState>()) {}
void FloorRobot::assignTask() { state_->assignTask(*this); }
void FloorRobot::completeTask() { state_->completeTask(*this); }

int main() {
    FloorRobot robot;
    robot.completeTask();  // 空闲：拒绝
    robot.assignTask();    // 空闲 -> 忙碌
    robot.assignTask();    // 忙碌：蜂鸣
    robot.completeTask();  // 忙碌 -> 空闲，交付任务
    robot.completeTask();  // 又是空闲：拒绝
    return 0;
}
