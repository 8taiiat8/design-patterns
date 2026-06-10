// Observer — define a one-to-many dependency so that when one object (the
// subject) changes state, all its dependents (observers) are notified.
//
// Use for event systems, model-view updates, pub/sub within a process.
//
// Build: g++ -std=c++17 observer.cpp -o observer

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(double temperature) = 0;
};

// Subject: maintains a list of observers and notifies them on change.
class WeatherStation {
public:
    void attach(Observer* observer) { observers_.push_back(observer); }

    void detach(Observer* observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer),
                         observers_.end());
    }

    void setTemperature(double celsius) {
        std::cout << "station: temperature is now " << celsius << "C\n";
        for (Observer* observer : observers_) observer->update(celsius);
    }

private:
    std::vector<Observer*> observers_;
};

class PhoneDisplay : public Observer {
public:
    void update(double temperature) override {
        std::cout << "  phone display shows " << temperature << "C\n";
    }
};

class HeaterController : public Observer {
public:
    void update(double temperature) override {
        std::cout << "  heater turns " << (temperature < 18.0 ? "ON" : "OFF") << "\n";
    }
};

int main() {
    WeatherStation station;
    PhoneDisplay phone;
    HeaterController heater;

    station.attach(&phone);
    station.attach(&heater);

    station.setTemperature(15.5);
    station.setTemperature(22.0);

    station.detach(&phone);
    station.setTemperature(12.0);  // only the heater reacts now
    return 0;
}
