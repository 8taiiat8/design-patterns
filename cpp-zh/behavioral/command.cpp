// 🤖 机器人工厂 RoboWorks — 第 14 章：工单队列
//
// 故事：控制台不会对着车间大喊大叫——每个任务都变成一张"工单"
// 压进队列。车间按自己的节奏执行工单；客户取消订单时，
// 直接撤回最后一张工单（撤销）。
//
// 模式：命令（Command）——把请求封装成对象，从而可以排队、记录日志、
// 支持撤销。把发出操作的对象（控制台）与执行操作的对象（车间）解耦。
//
// 编译：g++ -std=c++17 command.cpp -o command

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 接收者：真正干活的对象。
class FactoryFloor {
public:
    void start(const std::string& job) { std::cout << "车间开工：" << job << "\n"; }
    void recall(const std::string& job) { std::cout << "车间撤回：" << job << "\n"; }
};

// 带撤销功能的命令接口。
class JobCard {
public:
    virtual ~JobCard() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class WeldJob : public JobCard {
public:
    WeldJob(FactoryFloor& floor, std::string seam)
        : floor_(floor), seam_(std::move(seam)) {}
    void execute() override { floor_.start("焊接 " + seam_); }
    void undo() override { floor_.recall("焊接 " + seam_); }

private:
    FactoryFloor& floor_;
    std::string seam_;
};

class TransportJob : public JobCard {
public:
    TransportJob(FactoryFloor& floor, std::string cargo)
        : floor_(floor), cargo_(std::move(cargo)) {}
    void execute() override { floor_.start("运输 " + cargo_); }
    void undo() override { floor_.recall("运输 " + cargo_); }

private:
    FactoryFloor& floor_;
    std::string cargo_;
};

// 调用者：签发工单并保存历史，以便撤销。
class ControlPanel {
public:
    void issue(std::unique_ptr<JobCard> job) {
        job->execute();
        history_.push_back(std::move(job));
    }

    void cancelLast() {
        if (history_.empty()) return;
        history_.back()->undo();
        history_.pop_back();
    }

private:
    std::vector<std::unique_ptr<JobCard>> history_;
};

int main() {
    FactoryFloor floor;
    ControlPanel panel;

    panel.issue(std::make_unique<WeldJob>(floor, "底盘 7 号焊缝"));
    panel.issue(std::make_unique<TransportJob>(floor, "一箱伺服电机"));

    std::cout << "—— 客户取消订单 ——\n";
    panel.cancelLast();
    return 0;
}
