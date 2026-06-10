"""Observer — define a one-to-many dependency so that when one object (the
subject) changes state, all its dependents (observers) are notified.

Use for event systems, model-view updates, pub/sub within a process.

Run: python3 observer.py
"""

from abc import ABC, abstractmethod


class Observer(ABC):
    @abstractmethod
    def update(self, temperature: float) -> None: ...


class WeatherStation:
    """Subject: maintains observers and notifies them on change."""

    def __init__(self):
        self._observers: list[Observer] = []

    def attach(self, observer: Observer) -> None:
        self._observers.append(observer)

    def detach(self, observer: Observer) -> None:
        self._observers.remove(observer)

    def set_temperature(self, celsius: float) -> None:
        print(f"station: temperature is now {celsius}C")
        for observer in self._observers:
            observer.update(celsius)


class PhoneDisplay(Observer):
    def update(self, temperature: float) -> None:
        print(f"  phone display shows {temperature}C")


class HeaterController(Observer):
    def update(self, temperature: float) -> None:
        print(f"  heater turns {'ON' if temperature < 18.0 else 'OFF'}")


def main():
    station = WeatherStation()
    phone = PhoneDisplay()
    heater = HeaterController()

    station.attach(phone)
    station.attach(heater)

    station.set_temperature(15.5)
    station.set_temperature(22.0)

    station.detach(phone)
    station.set_temperature(12.0)  # only the heater reacts now


if __name__ == "__main__":
    main()
