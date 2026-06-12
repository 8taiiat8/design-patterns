"""机器人工厂 RoboWorks — 第 8 章：组件套组件

故事：机器人不是一个零件，而是组件里套组件：躯干总成包含机械臂
总成，机械臂总成包含伺服电机和夹爪。成本工程师想对任何节点——
一颗螺栓也好、整个躯干也好——问同一个问题："这个多少钱？"

模式：组合（Composite）——把对象组合成树形结构，
让客户端统一对待单个零件和整个总成。

运行：python3 composite.py
"""

from abc import ABC, abstractmethod


# 组件：单个零件和整个总成的公共接口。
class PartComponent(ABC):
    def __init__(self, name: str):
        self.name = name

    @abstractmethod
    def cost_cents(self) -> int: ...

    @abstractmethod
    def print(self, indent: int = 0) -> None: ...


# 叶子
class Part(PartComponent):
    def __init__(self, name: str, cost_cents: int):
        super().__init__(name)
        self._cost_cents = cost_cents

    def cost_cents(self) -> int:
        return self._cost_cents

    def print(self, indent: int = 0) -> None:
        print(f"{' ' * indent}- {self.name}（${self._cost_cents / 100}）")


# 组合：持有子节点，把操作转发给它们。
class Assembly(PartComponent):
    def __init__(self, name: str):
        super().__init__(name)
        self.children: list[PartComponent] = []

    def add(self, component: PartComponent) -> "Assembly":
        self.children.append(component)
        return self

    def cost_cents(self) -> int:
        return sum(child.cost_cents() for child in self.children)

    def print(self, indent: int = 0) -> None:
        print(f"{' ' * indent}+ {self.name}")
        for child in self.children:
            child.print(indent + 2)


def main():
    arm = Assembly("机械臂总成").add(Part("伺服电机", 4500)).add(Part("夹爪", 3000))
    torso = Assembly("躯干总成").add(Part("钢制框架", 12000)).add(arm)

    torso.print()
    print(f"总成本：${torso.cost_cents() / 100}")


if __name__ == "__main__":
    main()
