import wpilib

lstick = wpilib.Joystick(1)
rstick = wpilib.Joystick(2)

lmotor = wpilib.CANJaguar(3)
rmotor = wpilib.CANJaguar(5)
drive = wpilib.RobotDrive(lmotor, rmotor)

def CheckRestart():
    if lstick.GetRawButton(10):
        raise RuntimeError("Restart")

class MyRobot(wpilib.SimpleRobot):
    def Disabled(self):
        while self.IsDisabled():
            CheckRestart()
            wpilib.Wait(0.01)

    def Autonomous(self):
        self.GetWatchdog().SetEnabled(False)
        while self.IsAutonomous() and self.IsEnabled():
            CheckRestart()
            wpilib.Wait(0.01)

    def OperatorControl(self):
        dog = self.GetWatchdog()
        dog.SetEnabled(True)
        dog.SetExpiration(0.5)

        while self.IsOperatorControl() and self.IsEnabled():
            dog.Feed()
            CheckRestart()

            drive.TankDrive(lstick, rstick)

            wpilib.Wait(0.04)

def run():
    robot = MyRobot()
    robot.StartCompetition()
