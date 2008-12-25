cd C:\WindRiver\vxworks-6.3\target

del h\WPILib\*.h
del h\WPILib\ChipObject\*.h
del h\WPILib\Visa\*.h
del h\WPILib\NetworkCommunication\*.h
copy c:\WindRiver\workspace\WPILib\*.h h\WPIlib
copy c:\WindRiver\workspace\WPILib\ChipObject\*.h h\WPIlib\ChipObject
copy c:\WindRiver\workspace\WPILib\visa\*.h h\WPIlib\visa
copy C:\WindRiver\workspace\WPILib\NetworkCommunication\*.h h\WPILib\NetworkCommunication

copy C:\WindRiver\workspace\WPILib\PPC603gnu_DEBUG\WPILib.a lib
