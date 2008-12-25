rmdir c:\Temp\WorkbenchUpdate /s /q

mkdir c:\Temp\WorkbenchUpdate
cd \Temp\WorkbenchUpdate

mkdir vxworks-6.3\target\h\WPILib\ChipObject
mkdir vxworks-6.3\target\h\WPILib\Visa
mkdir vxworks-6.3\target\h\WPILib\NetworkCommunication
copy c:\WindRiver\workspace\WPILib\*.h vxworks-6.3\target\h\WPIlib
copy c:\WindRiver\workspace\WPILib\ChipObject\*.h vxworks-6.3\target\h\WPIlib\ChipObject
copy c:\WindRiver\workspace\WPILib\visa\*.h vxworks-6.3\target\h\WPIlib\visa

mkdir vxworks-6.3\target\lib
copy C:\WindRiver\workspace\WPILib\PPC603gnu_DEBUG\WPILib.a vxworks-6.3\target\lib

mkdir vxworks-6.3\target\src\demo
xcopy c:\WindRiver\vxworks-6.3\target\src\demo\DefaultRobot vxworks-6.3\target\src\demo\DefaultRobot\ /e
xcopy c:\WindRiver\vxworks-6.3\target\src\demo\IterativeDemo vxworks-6.3\target\src\demo\IterativeDemo\ /e
xcopy c:\WindRiver\vxworks-6.3\target\src\demo\SimpleTemplate vxworks-6.3\target\src\demo\SimpleTemplate\ /e
xcopy c:\WindRiver\vxworks-6.3\target\src\demo\VisionDemo vxworks-6.3\target\src\demo\VisionDemo\ /e

mkdir docs\extensions
mkdir workbench-3.0\wrwb\wrworkbench\eclipse\plugins
copy C:\WindRiver\workbench-3.0\wrwb\wrworkbench\eclipse\plugins\edu.wpi.* workbench-3.0\wrwb\wrworkbench\eclipse\plugins

copy c:\WindRiver\docs\extensions\FRC\*.* docs\extensions\FRC
copy C:\WindRiver\workspace\Documentation\*.pdf docs\extensions\FRC\

mkdir WPILib
copy c:\WindRiver\WPILib\*.* WPILib
