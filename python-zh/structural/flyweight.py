"""机器人工厂 RoboWorks — 第 11 章：千架无人机，三张图纸

故事：无人机机库停着上千架飞机，但工厂只生产几个机型。如果每架
无人机内部都存一份完整图纸，仓库数据库就爆了。所以每架飞机只存
自己的序列号和停机位，外加一个指向共享机型定义的"引用"。

模式：享元（Flyweight）——在大量对象之间共享公共（内在）状态；
变化的（外在）状态由外部传入。在 CPython 中，小整数和驻留字符串
就是运行时维护的享元。

运行：python3 flyweight.py
"""

from dataclasses import dataclass


@dataclass(frozen=True)
class RobotModel:
    """享元：众多无人机共享的重量级内在状态（机型名称和完整图纸）。"""

    name: str
    blueprint: str

    def print_unit(self, serial: int, bay: int) -> None:
        # 外在状态（序列号、停机位）由调用方提供。
        print(f"编号 #{serial}（{bay} 号停机位）：{self.name} — {self.blueprint}")


class RobotModelFactory:
    """缓存并复用 RobotModel 实例。"""

    def __init__(self):
        self._cache: dict[str, RobotModel] = {}

    def get(self, name: str, blueprint: str) -> RobotModel:
        if name not in self._cache:
            self._cache[name] = RobotModel(name, blueprint)
            print(f"（新建享元：{name}）")
        return self._cache[name]

    def unique_models(self) -> int:
        return len(self._cache)


@dataclass
class DroneUnit:
    """上下文对象：很小——只有外在状态加一个共享享元。"""

    serial: int
    bay: int
    model: RobotModel


def main():
    factory = RobotModelFactory()
    hall = [
        DroneUnit(101, 1, factory.get("侦察无人机", "4 旋翼，广角摄像头")),
        DroneUnit(102, 3, factory.get("侦察无人机", "4 旋翼，广角摄像头")),
        DroneUnit(103, 2, factory.get("货运无人机", "8 旋翼，5 公斤载重")),
        DroneUnit(104, 5, factory.get("侦察无人机", "4 旋翼，广角摄像头")),
        DroneUnit(105, 4, factory.get("货运无人机", "8 旋翼，5 公斤载重")),
        DroneUnit(106, 1, factory.get("侦察无人机", "4 旋翼，广角摄像头")),
    ]

    for unit in hall:
        unit.model.print_unit(unit.serial, unit.bay)

    print(f"无人机数量：{len(hall)}，机型享元数量：{factory.unique_models()}")
    print("侦察无人机享元是共享的吗？", hall[0].model is hall[1].model)


if __name__ == "__main__":
    main()
