"""机器人工厂 RoboWorks — 第 17 章：调度塔

故事：以前机器人之间直接用无线电互联，车间一片混乱——每台机器人
都得记住其他所有机器人的频率。于是你建了调度塔：机器人只向塔台
汇报，塔台把消息转发给其他所有机器人。谁也不用知道还有谁在线。

模式：中介者（Mediator）——用一个对象封装一组对象的交互方式，
使它们不再互相直接引用；把多对多关系变成一对多。

运行：python3 mediator.py
"""

from abc import ABC, abstractmethod


class DispatchTower(ABC):
    @abstractmethod
    def relay(self, sender: "FloorRobot", message: str) -> None: ...

    @abstractmethod
    def register(self, robot: "FloorRobot") -> None: ...


class FloorRobot:
    """同事类：只认识塔台，不认识其他机器人。"""

    def __init__(self, callsign: str, tower: DispatchTower):
        self.callsign = callsign
        self.tower = tower
        tower.register(self)

    def report(self, message: str) -> None:
        print(f"{self.callsign} 汇报：{message}")
        self.tower.relay(self, message)

    def receive(self, sender: str, message: str) -> None:
        print(f"  {self.callsign} 收到 {sender}：{message}")


class CentralTower(DispatchTower):
    """具体中介者：把汇报转发给其他所有机器人。"""

    def __init__(self):
        self.robots: list[FloorRobot] = []

    def register(self, robot: FloorRobot) -> None:
        self.robots.append(robot)

    def relay(self, sender: FloorRobot, message: str) -> None:
        for robot in self.robots:
            if robot is not sender:
                robot.receive(sender.callsign, message)


def main():
    tower = CentralTower()
    welder = FloorRobot("焊接-01", tower)
    crane = FloorRobot("吊装-02", tower)
    FloorRobot("无人机-03", tower)

    welder.report("底盘 7 号焊缝完工，可以取件")
    crane.report("正在 B 线取件，请让出通道")


if __name__ == "__main__":
    main()
