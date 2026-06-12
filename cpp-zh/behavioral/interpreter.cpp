// 🤖 机器人工厂 RoboWorks — 第 15 章：机器人脚本
//
// 故事：工程师用一种极简的脚本语言排班："焊接 + 移动 - 省电"。
// 调度器看得懂：每个词对应一条文法规则，对整个句子求值
// 就能算出这一班的能耗预算（瓦特）。
//
// 模式：解释器（Interpreter）——为小型语言的每条文法规则定义一个类，
// 用 interpret() 方法对语言中的句子求值。适合简单 DSL；
// 复杂语言请使用真正的解析器。
//
// 本例对脚本树 (焊接 + 移动) - 省电 求值。
//
// 编译：g++ -std=c++17 interpreter.cpp -o interpreter

#include <iostream>
#include <memory>
#include <string>

// 抽象表达式：一切都求值为瓦特数。
class ScriptExpression {
public:
    virtual ~ScriptExpression() = default;
    virtual int watts() const = 0;
};

// 终结符表达式：单个机器人动作。
class Action : public ScriptExpression {
public:
    Action(std::string name, int watts) : name_(std::move(name)), watts_(watts) {}
    int watts() const override { return watts_; }

private:
    std::string name_;
    int watts_;
};

// 非终结符表达式：组合子表达式。
class Sequence : public ScriptExpression {
public:
    Sequence(std::unique_ptr<ScriptExpression> left, std::unique_ptr<ScriptExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    int watts() const override { return left_->watts() + right_->watts(); }

private:
    std::unique_ptr<ScriptExpression> left_, right_;
};

class PowerSave : public ScriptExpression {
public:
    PowerSave(std::unique_ptr<ScriptExpression> script, int savedWatts)
        : script_(std::move(script)), savedWatts_(savedWatts) {}

    int watts() const override { return script_->watts() - savedWatts_; }

private:
    std::unique_ptr<ScriptExpression> script_;
    int savedWatts_;
};

int main() {
    // 语法树：(焊接 + 移动) - 省电(100)
    auto script = std::make_unique<PowerSave>(
        std::make_unique<Sequence>(std::make_unique<Action>("焊接", 200),
                                   std::make_unique<Action>("移动", 50)),
        100);

    std::cout << "「焊接 + 移动 - 省电」 = " << script->watts() << " 瓦\n";
    return 0;
}
