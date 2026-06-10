"""Builder — separate the construction of a complex object from its
representation, so the same process can create different configurations
step by step.

Use when an object has many optional parts and a constructor with a long
parameter list would be unreadable. Note: Python's keyword arguments and
dataclasses cover many simple cases; the builder shines when construction
involves ordering, validation, or reusable recipes.

Run: python3 builder.py
"""

from dataclasses import dataclass, field


@dataclass
class Computer:
    cpu: str = ""
    ram: str = ""
    usb_ports: int = 0
    display: str = ""
    extras: list = field(default_factory=list)


class ComputerBuilder:
    """Fluent builder: each step returns self so calls can be chained."""

    def __init__(self):
        self._computer = Computer()

    def cpu(self, value: str) -> "ComputerBuilder":
        self._computer.cpu = value
        return self

    def ram(self, value: str) -> "ComputerBuilder":
        self._computer.ram = value
        return self

    def usb_ports(self, count: int) -> "ComputerBuilder":
        self._computer.usb_ports = count
        return self

    def display(self, value: str) -> "ComputerBuilder":
        self._computer.display = value
        return self

    def extra(self, value: str) -> "ComputerBuilder":
        self._computer.extras.append(value)
        return self

    def build(self) -> Computer:
        if not self._computer.cpu:
            raise ValueError("a computer needs a CPU")
        return self._computer


class Director:
    """Optional director: encapsulates well-known build recipes."""

    @staticmethod
    def gaming_pc() -> Computer:
        return (
            ComputerBuilder()
            .cpu("Ryzen 9")
            .ram("64GB DDR5")
            .usb_ports(6)
            .display("4K 144Hz")
            .extra("RGB everything")
            .build()
        )

    @staticmethod
    def office_pc() -> Computer:
        return ComputerBuilder().cpu("Core i5").ram("16GB").usb_ports(4).display("1080p").build()


def main():
    custom = ComputerBuilder().cpu("Apple M3").ram("32GB").usb_ports(2).display("Retina").build()
    print("custom:", custom)
    print("gaming:", Director.gaming_pc())
    print("office:", Director.office_pc())


if __name__ == "__main__":
    main()
