// 🤖 RoboWorks — Chapter 15: The Robot Script
//
// STORY: Engineers program shifts in a tiny script language:
// "weld + move - powersave". The scheduler understands it: each word is
// a grammar rule, and evaluating the sentence computes the shift's energy
// budget in watts.
//
// PATTERN: Interpreter — for a small language, define a class per grammar
// rule and an interpret() method that evaluates sentences. Use for simple
// DSLs (job scripts, filters); for anything complex use a real parser.
//
// This example evaluates the script tree: (weld + move) - powersave.
//
// Build: g++ -std=c++17 interpreter.cpp -o interpreter

#include <iostream>
#include <memory>
#include <string>

// Abstract expression: everything evaluates to watts.
class ScriptExpression {
public:
    virtual ~ScriptExpression() = default;
    virtual int watts() const = 0;
};

// Terminal expression: a single robot action.
class Action : public ScriptExpression {
public:
    Action(std::string name, int watts) : name_(std::move(name)), watts_(watts) {}
    int watts() const override { return watts_; }

private:
    std::string name_;
    int watts_;
};

// Non-terminal expressions combine sub-expressions.
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
    // Syntax tree for: (weld + move) - powersave(100)
    auto script = std::make_unique<PowerSave>(
        std::make_unique<Sequence>(std::make_unique<Action>("weld", 200),
                                   std::make_unique<Action>("move", 50)),
        100);

    std::cout << "\"weld + move - powersave\" = " << script->watts() << " watts\n";
    return 0;
}
