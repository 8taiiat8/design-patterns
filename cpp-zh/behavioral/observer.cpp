// 🤖 机器人工厂 RoboWorks — 第 19 章："42 号下线了！"
//
// 故事：经理们过去每小时给车间打电话问"42 批好了没？"
// 现在他们订阅了通知：每当一台机器人下线，大屏看板自动刷新，
// 工程师的传呼机同时震动——装配线根本不知道、也不关心谁在听。
//
// 模式：观察者（Observer）——定义一对多依赖，主题状态一变，
// 所有注册的观察者都收到通知。事件系统和 UI 更新的基石。
//
// 编译：g++ -std=c++17 observer.cpp -o observer

#include <algorithm>
#include <iostream>
#include <vector>

// 观察者接口
class LineObserver {
public:
    virtual ~LineObserver() = default;
    virtual void unitFinished(int serial) = 0;
};

// 主题：维护观察者列表，状态变化时逐个通知。
class AssemblyLine {
public:
    void attach(LineObserver* observer) { observers_.push_back(observer); }

    void detach(LineObserver* observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                         observers_.end());
    }

    void rollOff(int serial) {
        std::cout << "装配线：#" << serial << " 号机下线\n";
        for (LineObserver* observer : observers_) observer->unitFinished(serial);
    }

private:
    std::vector<LineObserver*> observers_;
};

class Dashboard : public LineObserver {
public:
    void unitFinished(int serial) override {
        std::cout << "  看板刷新：#" << serial << " 号机完工\n";
    }
};

class EngineerPager : public LineObserver {
public:
    void unitFinished(int serial) override {
        std::cout << "  传呼机震动：#" << serial << " 号机等待质检！\n";
    }
};

int main() {
    AssemblyLine line;
    Dashboard dashboard;
    EngineerPager pager;

    line.attach(&dashboard);
    line.attach(&pager);

    line.rollOff(41);
    line.rollOff(42);

    line.detach(&pager);  // 工程师下班了
    line.rollOff(43);     // 现在只有看板有反应
    return 0;
}
