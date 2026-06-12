// 🤖 机器人工厂 RoboWorks — 第 12 章：笨重的诊断套件
//
// 故事：完整诊断套件启动要很久——几个 GB 的传感器模型和校准表。
// 大多数班次根本用不上它。所以工作台上放着一个替身：它看起来和
// 真套件一模一样，但只有工程师"第一次"真正运行扫描时才会启动真家伙。
//
// 模式：代理（Proxy）——为另一个对象提供替身以控制对它的访问。
// 变体：虚代理（惰性加载，本例）、保护代理、远程代理、缓存/日志代理。
//
// 编译：g++ -std=c++17 proxy.cpp -o proxy

#include <iostream>
#include <memory>
#include <string>

class Diagnostics {
public:
    virtual ~Diagnostics() = default;
    virtual void scan(const std::string& robot) = 0;
};

// 真实主题：构造代价高（启动完整套件）。
class FullDiagnosticsSuite : public Diagnostics {
public:
    FullDiagnosticsSuite() {
        std::cout << "正在启动完整诊断套件（很慢！）\n";
    }

    void scan(const std::string& robot) override {
        std::cout << "对 " << robot << " 进行深度扫描\n";
    }
};

// 代理：同样的接口，只在第一次使用时才启动真套件。
class DiagnosticsProxy : public Diagnostics {
public:
    void scan(const std::string& robot) override {
        if (!real_) {
            real_ = std::make_unique<FullDiagnosticsSuite>();  // 惰性加载
        }
        real_->scan(robot);
    }

private:
    std::unique_ptr<FullDiagnosticsSuite> real_;
};

int main() {
    DiagnosticsProxy workbench;
    std::cout << "代理就绪，套件尚未启动\n";

    workbench.scan("焊接机器人 #7");   // 触发昂贵的启动
    workbench.scan("侦察无人机 #42");  // 复用已启动的套件
    return 0;
}
