"""机器人工厂 RoboWorks — 第 10 章：那个绿色大按钮

故事：开始生产的幕后是一团乱：预留零件、给电网加电、运行装配单元、
通过质检——顺序一步都不能错。客户什么都看不见，
只需按下写着"生产"的绿色大按钮，门面就把一切安排妥当。

模式：外观（Facade）——为复杂子系统提供一个简化的统一入口。

运行：python3 facade.py
"""


# 复杂的子系统部件。客户端可以直接调用它们，
# 但正确的顺序和接线很容易搞错。
class PartsDepot:
    def reserve_parts_for(self, model: str) -> bool:
        print(f"仓库：已为 {model} 预留零件")
        return True


class PowerGrid:
    def power_up(self, kilowatts: int) -> bool:
        print(f"电网：已分配 {kilowatts} 千瓦")
        return True


class AssemblyCell:
    def assemble(self, model: str) -> None:
        print(f"装配单元：正在组装 {model}")


class QualityControl:
    def inspect(self, model: str) -> None:
        print(f"质检：{model} 检验合格")


# 外观暴露一个高层操作，统一编排各部件。
class ProductionFacade:
    def __init__(self):
        self._depot = PartsDepot()
        self._grid = PowerGrid()
        self._cell = AssemblyCell()
        self._qc = QualityControl()

    def produce(self, model: str, kilowatts: int) -> bool:
        if not self._depot.reserve_parts_for(model):
            return False
        if not self._grid.power_up(kilowatts):
            return False
        self._cell.assemble(model)
        self._qc.inspect(model)
        print("本次生产完成")
        return True


def main():
    big_green_button = ProductionFacade()
    big_green_button.produce("焊接机器人 Mk2", 40)


if __name__ == "__main__":
    main()
