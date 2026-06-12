// 🤖 机器人工厂 RoboWorks — 第 10 章：那个绿色大按钮
//
// 故事：开始生产的幕后是一团乱：预留零件、给电网加电、运行装配单元、
// 通过质检——顺序一步都不能错。客户什么都看不见，
// 只需按下写着"生产"的绿色大按钮，门面就把一切安排妥当。
//
// 模式：外观（Facade）——为复杂子系统提供一个简化的统一入口。
// 适用于客户端只需要子系统的一小部分功能、且调用顺序容易出错的场景。
//
// 编译：g++ -std=c++17 facade.cpp -o facade

#include <iostream>
#include <string>

// 复杂的子系统部件。客户端可以直接调用它们，
// 但正确的顺序和接线很容易搞错。
class PartsDepot {
public:
    bool reservePartsFor(const std::string& model) {
        std::cout << "仓库：已为 " << model << " 预留零件\n";
        return true;
    }
};

class PowerGrid {
public:
    bool powerUp(int kilowatts) {
        std::cout << "电网：已分配 " << kilowatts << " 千瓦\n";
        return true;
    }
};

class AssemblyCell {
public:
    void assemble(const std::string& model) {
        std::cout << "装配单元：正在组装 " << model << "\n";
    }
};

class QualityControl {
public:
    void inspect(const std::string& model) {
        std::cout << "质检：" << model << " 检验合格\n";
    }
};

// 外观暴露一个高层操作，统一编排各部件。
class ProductionFacade {
public:
    bool produce(const std::string& model, int kilowatts) {
        if (!depot_.reservePartsFor(model)) return false;
        if (!grid_.powerUp(kilowatts)) return false;
        cell_.assemble(model);
        qc_.inspect(model);
        std::cout << "本次生产完成\n";
        return true;
    }

private:
    PartsDepot depot_;
    PowerGrid grid_;
    AssemblyCell cell_;
    QualityControl qc_;
};

int main() {
    ProductionFacade bigGreenButton;
    bigGreenButton.produce("焊接机器人 Mk2", 40);
    return 0;
}
