"""Factory Method — define an interface for creating an object, but let
subclasses decide which concrete class to instantiate.

Use when a class can't anticipate the type of objects it must create, or
when you want to localize the knowledge of which class gets created.

Run: python3 factory_method.py
"""

from abc import ABC, abstractmethod


# Product interface
class Transport(ABC):
    @abstractmethod
    def deliver(self) -> str: ...


class Truck(Transport):
    def deliver(self) -> str:
        return "deliver by land in a truck"


class Ship(Transport):
    def deliver(self) -> str:
        return "deliver by sea in a ship"


# Creator: business logic depends only on the Transport interface;
# the factory method defers the concrete choice to subclasses.
class Logistics(ABC):
    def plan_delivery(self) -> None:
        transport = self.create_transport()  # the factory method
        print(f"Planning: {transport.deliver()}")

    @abstractmethod
    def create_transport(self) -> Transport: ...


class RoadLogistics(Logistics):
    def create_transport(self) -> Transport:
        return Truck()


class SeaLogistics(Logistics):
    def create_transport(self) -> Transport:
        return Ship()


def main():
    RoadLogistics().plan_delivery()
    SeaLogistics().plan_delivery()


if __name__ == "__main__":
    main()
