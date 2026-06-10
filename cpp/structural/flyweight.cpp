// ☕ Café Patterna — Chapter 11: A Thousand Tickets, Three Drinks
//
// STORY: On a busy Saturday the kitchen prints thousands of order
// tickets. But the café only sells a handful of drink types — printing
// the full recipe on every ticket would waste mountains of paper (and in
// code, memory). So each ticket carries only its order number and table,
// plus a POINTER to the one shared drink definition.
//
// PATTERN: Flyweight — share common (intrinsic) state between many
// objects; varying (extrinsic) state is passed in from outside.
//
// Build: g++ -std=c++17 flyweight.cpp -o flyweight

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Flyweight: the heavy intrinsic state shared by many tickets
// (the drink's name and full recipe).
class DrinkType {
public:
    DrinkType(std::string name, std::string recipe)
        : name_(std::move(name)), recipe_(std::move(recipe)) {}

    // Extrinsic state (order number, table) is supplied by the caller.
    void printTicket(int orderNo, int table) const {
        std::cout << "ticket #" << orderNo << " (table " << table << "): "
                  << name_ << " — " << recipe_ << "\n";
    }

private:
    std::string name_;
    std::string recipe_;
};

// Flyweight factory: caches and reuses DrinkType instances.
class DrinkTypeFactory {
public:
    const DrinkType& get(const std::string& name, const std::string& recipe) {
        auto it = cache_.find(name);
        if (it == cache_.end()) {
            it = cache_.emplace(name, std::make_unique<DrinkType>(name, recipe)).first;
            std::cout << "(created new flyweight: " << name << ")\n";
        }
        return *it->second;
    }

    size_t uniqueTypes() const { return cache_.size(); }

private:
    std::map<std::string, std::unique_ptr<DrinkType>> cache_;
};

// Context object: tiny — extrinsic state plus a shared flyweight.
struct OrderTicket {
    int orderNo;
    int table;
    const DrinkType* type;
};

int main() {
    DrinkTypeFactory factory;
    std::vector<OrderTicket> rail;

    // Six orders, but only two unique DrinkType objects exist in memory.
    rail.push_back({101, 1, &factory.get("latte", "2 shots + steamed milk")});
    rail.push_back({102, 3, &factory.get("latte", "2 shots + steamed milk")});
    rail.push_back({103, 2, &factory.get("matcha", "whisked matcha + milk")});
    rail.push_back({104, 5, &factory.get("latte", "2 shots + steamed milk")});
    rail.push_back({105, 4, &factory.get("matcha", "whisked matcha + milk")});
    rail.push_back({106, 1, &factory.get("latte", "2 shots + steamed milk")});

    for (const auto& ticket : rail) ticket.type->printTicket(ticket.orderNo, ticket.table);
    std::cout << "tickets: " << rail.size()
              << ", drink flyweights: " << factory.uniqueTypes() << "\n";
    return 0;
}
