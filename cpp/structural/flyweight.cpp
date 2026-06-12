// 🤖 RoboWorks — Chapter 11: A Thousand Drones, Three Blueprints
//
// STORY: The drone hall holds thousands of units, but the factory only
// produces a handful of models. Storing the full blueprint inside every
// drone would melt the warehouse database. So each unit stores only its
// serial number and docking bay, plus a POINTER to the one shared model
// definition.
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

// Flyweight: the heavy intrinsic state shared by many drones
// (the model's name and full blueprint).
class RobotModel {
public:
    RobotModel(std::string name, std::string blueprint)
        : name_(std::move(name)), blueprint_(std::move(blueprint)) {}

    // Extrinsic state (serial, bay) is supplied by the caller.
    void printUnit(int serial, int bay) const {
        std::cout << "unit #" << serial << " (bay " << bay << "): "
                  << name_ << " — " << blueprint_ << "\n";
    }

private:
    std::string name_;
    std::string blueprint_;
};

// Flyweight factory: caches and reuses RobotModel instances.
class RobotModelFactory {
public:
    const RobotModel& get(const std::string& name, const std::string& blueprint) {
        auto it = cache_.find(name);
        if (it == cache_.end()) {
            it = cache_.emplace(name, std::make_unique<RobotModel>(name, blueprint)).first;
            std::cout << "(created new flyweight: " << name << ")\n";
        }
        return *it->second;
    }

    size_t uniqueModels() const { return cache_.size(); }

private:
    std::map<std::string, std::unique_ptr<RobotModel>> cache_;
};

// Context object: tiny — extrinsic state plus a shared flyweight.
struct DroneUnit {
    int serial;
    int bay;
    const RobotModel* model;
};

int main() {
    RobotModelFactory factory;
    std::vector<DroneUnit> hall;

    // Six drones, but only two unique RobotModel objects exist in memory.
    hall.push_back({101, 1, &factory.get("ScoutDrone", "4 rotors, wide-angle cam")});
    hall.push_back({102, 3, &factory.get("ScoutDrone", "4 rotors, wide-angle cam")});
    hall.push_back({103, 2, &factory.get("CargoDrone", "8 rotors, 5kg payload")});
    hall.push_back({104, 5, &factory.get("ScoutDrone", "4 rotors, wide-angle cam")});
    hall.push_back({105, 4, &factory.get("CargoDrone", "8 rotors, 5kg payload")});
    hall.push_back({106, 1, &factory.get("ScoutDrone", "4 rotors, wide-angle cam")});

    for (const auto& unit : hall) unit.model->printUnit(unit.serial, unit.bay);
    std::cout << "drones: " << hall.size()
              << ", model flyweights: " << factory.uniqueModels() << "\n";
    return 0;
}
