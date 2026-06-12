"""RoboWorks — Chapter 11: A Thousand Drones, Three Blueprints

STORY: The drone hall holds thousands of units, but the factory only
produces a handful of models. Storing the full blueprint inside every
drone would melt the warehouse database. So each unit stores only its
serial number and docking bay, plus a REFERENCE to the one shared model
definition.

PATTERN: Flyweight — share common (intrinsic) state between many objects;
varying (extrinsic) state is passed in from outside. In CPython, small
ints and interned strings are flyweights maintained by the runtime.

Run: python3 flyweight.py
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class RobotModel:
    """Flyweight: heavy intrinsic state shared by many drones
    (the model's name and full blueprint)."""

    name: str
    blueprint: str

    def print_unit(self, serial: int, bay: int) -> None:
        # Extrinsic state (serial, bay) is supplied by the caller.
        print(f"unit #{serial} (bay {bay}): {self.name} — {self.blueprint}")


class RobotModelFactory:
    """Caches and reuses RobotModel instances."""

    def __init__(self):
        self._cache: dict[str, RobotModel] = {}

    def get(self, name: str, blueprint: str) -> RobotModel:
        if name not in self._cache:
            self._cache[name] = RobotModel(name, blueprint)
            print(f"(created new flyweight: {name})")
        return self._cache[name]

    def unique_models(self) -> int:
        return len(self._cache)


@dataclass
class DroneUnit:
    """Context object: tiny — extrinsic state plus a shared flyweight."""

    serial: int
    bay: int
    model: RobotModel


def main():
    factory = RobotModelFactory()
    hall = [
        DroneUnit(101, 1, factory.get("ScoutDrone", "4 rotors, wide-angle cam")),
        DroneUnit(102, 3, factory.get("ScoutDrone", "4 rotors, wide-angle cam")),
        DroneUnit(103, 2, factory.get("CargoDrone", "8 rotors, 5kg payload")),
        DroneUnit(104, 5, factory.get("ScoutDrone", "4 rotors, wide-angle cam")),
        DroneUnit(105, 4, factory.get("CargoDrone", "8 rotors, 5kg payload")),
        DroneUnit(106, 1, factory.get("ScoutDrone", "4 rotors, wide-angle cam")),
    ]

    for unit in hall:
        unit.model.print_unit(unit.serial, unit.bay)

    print(f"drones: {len(hall)}, model flyweights: {factory.unique_models()}")
    print("ScoutDrone flyweight shared?", hall[0].model is hall[1].model)


if __name__ == "__main__":
    main()
