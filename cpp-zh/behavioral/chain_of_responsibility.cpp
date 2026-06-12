// 🤖 机器人工厂 RoboWorks — 第 13 章：故障上报
//
// 故事：B 线一台机器人卡死了。线上技术员可以当场批准 100 美元以内的
// 维修；再贵就要找楼层工程师；装配单元烧熔了？只有总工程师能批。
// 故障只上报一次——它沿着链条向上爬，直到有人能批准为止。
//
// 模式：责任链（Chain of Responsibility）——把请求沿处理者链传递；
// 每个处理者要么处理它，要么转发给下一个。
//
// 编译：g++ -std=c++17 chain_of_responsibility.cpp -o chain_of_responsibility

#include <iostream>
#include <string>

// 处理者：知道自己的后继者，以及自己能批准的维修预算。
class FaultHandler {
public:
    FaultHandler(std::string title, double budget)
        : title_(std::move(title)), budget_(budget) {}

    void setNext(FaultHandler* next) { next_ = next; }

    void handle(const std::string& fault, double cost) {
        if (cost <= budget_) {
            std::cout << title_ << " 批准 $" << cost << " 维修：「" << fault << "」\n";
        } else if (next_) {
            std::cout << title_ << " 无权批准 $" << cost << "，向上汇报……\n";
            next_->handle(fault, cost);
        } else {
            std::cout << "没人能为「" << fault << "」批准 $" << cost << "\n";
        }
    }

private:
    std::string title_;
    double budget_;
    FaultHandler* next_ = nullptr;
};

int main() {
    FaultHandler technician("线上技术员", 100);
    FaultHandler floorEngineer("楼层工程师", 1000);
    FaultHandler chiefEngineer("总工程师", 10000);

    // 搭建链条：技术员 -> 楼层工程师 -> 总工程师。
    technician.setNext(&floorEngineer);
    floorEngineer.setNext(&chiefEngineer);

    // 故障总是先报给线上的人。
    technician.handle("夹爪错位", 45);
    technician.handle("传送带撕裂", 800);
    technician.handle("装配单元烧熔", 7500);
    technician.handle("整个西厂区着火了", 2000000);
    return 0;
}
