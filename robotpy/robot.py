import wpilib


def CheckRestart():
    if lstick.GetRawButton(10):
        raise RuntimeError("Restart")

lstick = wpilib.Joystick(1)
rstick = wpilib.Joystick(2)
dt = wpilib.RobotDrive(1, 2)
dt.SetInvertedMotor(wpilib.RobotDrive.kFrontLeftMotor, True)
dt.SetInvertedMotor(wpilib.RobotDrive.kFrontRightMotor, True)

flipper = wpilib.Servo(9)

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
        dog.SetExpiration(0.25)

        while self.IsOperatorControl() and self.IsEnabled():
            dog.Feed()
            CheckRestart()

            
            # dt control
            dt.TankDrive(-lstick.GetY(), -rstick.GetY())
            if lstick.GetTop():
                flipper.Set(1)
            else:
                flipper.Set(0)
            
            
            wpilib.Wait(0.04)

def run():
    robot = MyRobot()
    robot.StartCompetition()
