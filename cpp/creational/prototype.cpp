// ☕ Café Patterna — Chapter 5: The Drink of the Day
//
// STORY: Inventing a recipe from scratch takes weeks of tasting. So every
// morning you take yesterday's bestseller card from the recipe box, CLONE
// it, and tweak one thing — "same latte, but with cinnamon". The original
// card stays untouched in the box.
//
// PATTERN: Prototype — create new objects by copying an existing object
// (the prototype) instead of building them from scratch. Use when
// creation is expensive or when code shouldn't depend on concrete classes.
//
// Build: g++ -std=c++17 prototype.cpp -o prototype

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class RecipeCard {
public:
    virtual ~RecipeCard() = default;
    virtual std::unique_ptr<RecipeCard> clone() const = 0;
    virtual void read() const = 0;
};

class DrinkRecipe : public RecipeCard {
public:
    DrinkRecipe(std::string name, std::string secret)
        : name_(std::move(name)), secret_(std::move(secret)) {}

    std::unique_ptr<RecipeCard> clone() const override {
        return std::make_unique<DrinkRecipe>(*this);  // copy ctor does the work
    }

    void tweak(std::string secret) { secret_ = std::move(secret); }

    void read() const override {
        std::cout << "DrinkRecipe(" << name_ << ": " << secret_ << ")\n";
    }

private:
    std::string name_;
    std::string secret_;
};

class PastryRecipe : public RecipeCard {
public:
    PastryRecipe(std::string name, int ovenMinutes)
        : name_(std::move(name)), ovenMinutes_(ovenMinutes) {}

    std::unique_ptr<RecipeCard> clone() const override {
        return std::make_unique<PastryRecipe>(*this);
    }

    void read() const override {
        std::cout << "PastryRecipe(" << name_ << ", " << ovenMinutes_ << " min in the oven)\n";
    }

private:
    std::string name_;
    int ovenMinutes_;
};

int main() {
    DrinkRecipe bestseller("house latte", "steam milk to 60C");

    // Clone today's special without naming the concrete type.
    std::vector<std::unique_ptr<RecipeCard>> recipeBox;
    recipeBox.push_back(bestseller.clone());
    recipeBox.push_back(std::make_unique<PastryRecipe>("croissant", 18));
    recipeBox.push_back(recipeBox.back()->clone());  // clone via the base interface

    // Tweaking the copy does not change the original card.
    auto special = bestseller.clone();
    static_cast<DrinkRecipe*>(special.get())->tweak("steam milk to 60C + cinnamon dust");

    std::cout << "original:        ";
    bestseller.read();
    std::cout << "drink of the day: ";
    special->read();

    std::cout << "recipe box:\n";
    for (const auto& card : recipeBox) card->read();
    return 0;
}
