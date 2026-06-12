// 🤖 机器人工厂 RoboWorks — 第 4 章：定制订单
//
// 故事：客户从不订购"标准机器人"，而是"履带底盘、四个传感器、两条
// 机械臂、夜视固件"。七个参数的构造函数是噩梦，所以配置台一步一步
// 组装机器人——产品目录（指挥者）里还存着标准机型的配方。
//
// 模式：建造者（Builder）——把复杂对象的构建过程与表示分离，
// 同一个构建过程可以一步步生成不同配置。
//
// 编译：g++ -std=c++17 builder.cpp -o builder

#include <iostream>
#include <string>

class Robot {
public:
    std::string chassis;
    int sensors = 0;
    int arms = 0;
    std::string firmware;

    void describe() const {
        std::cout << "机器人{底盘=" << chassis << ", 传感器=" << sensors
                  << ", 机械臂=" << arms << ", 固件=" << firmware << "}\n";
    }
};

// 流式建造者：每个设置方法返回 *this，可以链式调用。
class RobotBuilder {
public:
    RobotBuilder& chassis(std::string value) { robot_.chassis = std::move(value); return *this; }
    RobotBuilder& sensors(int value) { robot_.sensors = value; return *this; }
    RobotBuilder& arms(int value) { robot_.arms = value; return *this; }
    RobotBuilder& firmware(std::string value) { robot_.firmware = std::move(value); return *this; }

    Robot build() { return robot_; }

private:
    Robot robot_;
};

// 产品目录（指挥者）：封装常见机型的构建配方。
class Catalog {
public:
    static Robot workerBot() {
        return RobotBuilder{}
            .chassis("履带式")
            .sensors(4)
            .arms(2)
            .firmware("重载版 v3")
            .build();
    }

    static Robot scoutBot() {
        return RobotBuilder{}
            .chassis("轮式")
            .sensors(8)
            .arms(0)
            .firmware("夜视版 v2")
            .build();
    }
};

int main() {
    // 挑剔的客户一步一步定制机器人。
    Robot custom = RobotBuilder{}.chassis("六足式").sensors(6).arms(4).firmware("实验版").build();
    custom.describe();

    // 也可以直接按目录配方下单。
    Catalog::workerBot().describe();
    Catalog::scoutBot().describe();
    return 0;
}
