// ☕ Café Patterna — Chapter 4: "Can I Get That With Oat Milk?"
//
// STORY: Customers never order a plain drink. It's "large, two shots, oat
// milk, vanilla, extra hot". A constructor with seven parameters would be
// a nightmare, so the counter assembles each drink step by step — and the
// menu board keeps recipes (a director) for the house favorites.
//
// PATTERN: Builder — separate the construction of a complex object from
// its representation, so the same process can create different
// configurations step by step.
//
// Build: g++ -std=c++17 builder.cpp -o builder

#include <iostream>
#include <string>

class Drink {
public:
    std::string base;
    std::string size;
    int shots = 0;
    std::string milk;

    void describe() const {
        std::cout << "Drink{base=" << base << ", size=" << size
                  << ", shots=" << shots << ", milk=" << milk << "}\n";
    }
};

// Fluent builder: each setter returns *this so calls can be chained.
class DrinkBuilder {
public:
    DrinkBuilder& base(std::string value) { drink_.base = std::move(value); return *this; }
    DrinkBuilder& size(std::string value) { drink_.size = std::move(value); return *this; }
    DrinkBuilder& shots(int value) { drink_.shots = value; return *this; }
    DrinkBuilder& milk(std::string value) { drink_.milk = std::move(value); return *this; }

    Drink build() { return drink_; }

private:
    Drink drink_;
};

// The menu board (director): encapsulates well-known recipes.
class MenuBoard {
public:
    static Drink houseLatte() {
        return DrinkBuilder{}
            .base("espresso")
            .size("medium")
            .shots(2)
            .milk("whole, steamed")
            .build();
    }

    static Drink tripleMocha() {
        return DrinkBuilder{}
            .base("mocha")
            .size("large")
            .shots(3)
            .milk("oat, extra foam")
            .build();
    }
};

int main() {
    // A picky customer builds a custom drink step by step.
    Drink custom = DrinkBuilder{}.base("espresso").size("large").shots(2).milk("oat").build();
    custom.describe();

    // Or order straight off the menu board's recipes.
    MenuBoard::houseLatte().describe();
    MenuBoard::tripleMocha().describe();
    return 0;
}
