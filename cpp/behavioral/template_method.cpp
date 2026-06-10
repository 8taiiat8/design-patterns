// ☕ Café Patterna — Chapter 22: The House Ritual
//
// STORY: Every hot drink follows the same house ritual, in the same
// order: boil water, brew, pour into cup, add the finishing touch. The
// ritual itself never changes — but HOW you brew (drip the coffee, steep
// the tea) and the finishing touch differ per drink.
//
// PATTERN: Template Method — define the skeleton of an algorithm in a
// base class and let subclasses override specific steps without changing
// the algorithm's structure.
//
// Build: g++ -std=c++17 template_method.cpp -o template_method

#include <iostream>

// The base class owns the ritual's skeleton.
class HotDrinkRecipe {
public:
    virtual ~HotDrinkRecipe() = default;

    // The template method: fixed order, non-virtual on purpose.
    void prepare() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();  // optional hook with a default
    }

protected:
    // Steps subclasses must provide.
    virtual void brew() = 0;

    // Hook: has a sensible default, override only if needed.
    virtual void addCondiments() { std::cout << "  (served as is)\n"; }

private:
    // Steps that are identical for every drink stay private and fixed.
    void boilWater() { std::cout << "  boiling water\n"; }
    void pourInCup() { std::cout << "  pouring into cup\n"; }
};

class Coffee : public HotDrinkRecipe {
protected:
    void brew() override { std::cout << "  dripping coffee through filter\n"; }
    void addCondiments() override { std::cout << "  adding sugar and milk\n"; }
};

class Tea : public HotDrinkRecipe {
protected:
    void brew() override { std::cout << "  steeping the tea leaves\n"; }
};

int main() {
    std::cout << "Making coffee:\n";
    Coffee{}.prepare();

    std::cout << "Making tea:\n";
    Tea{}.prepare();
    return 0;
}
