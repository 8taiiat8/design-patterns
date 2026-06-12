// 🤖 RoboWorks — Chapter 20: The Robot's Modes
//
// STORY: A floor robot has modes. When idle, it accepts a task; when
// busy, assigning another task just triggers an angry beep, but pressing
// "complete" finishes the job and returns it to idle. Instead of one
// giant if/else on a status flag, each mode is its own class.
//
// PATTERN: State — let an object change its behavior when its internal
// state changes, by delegating behavior to a state object and swapping it
// on transitions.
//
// Build: g++ -std=c++17 state.cpp -o state

#include <iostream>
#include <memory>

class FloorRobot;

// State interface: one method per event the robot can receive.
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

// Concrete states
class BusyState : public RobotState {
public:
    void assignTask(FloorRobot&) override {
        std::cout << "robot beeps: already busy with a task\n";
    }
    void completeTask(FloorRobot& robot) override;
};

class IdleState : public RobotState {
public:
    void assignTask(FloorRobot& robot) override {
        std::cout << "task accepted, motors spinning up\n";
        robot.setState(std::make_unique<BusyState>());
    }
    void completeTask(FloorRobot&) override {
        std::cout << "nothing to complete, robot is idle\n";
    }
};

void BusyState::completeTask(FloorRobot& robot) {
    std::cout << "task finished, back to idle\n";
    robot.setState(std::make_unique<IdleState>());
}

FloorRobot::FloorRobot() : state_(std::make_unique<IdleState>()) {}
void FloorRobot::assignTask() { state_->assignTask(*this); }
void FloorRobot::completeTask() { state_->completeTask(*this); }

int main() {
    FloorRobot robot;
    robot.completeTask();  // idle: refuses
    robot.assignTask();    // idle -> busy
    robot.assignTask();    // busy: beeps
    robot.completeTask();  // busy -> idle, job done
    robot.completeTask();  // idle again: refuses
    return 0;
}
