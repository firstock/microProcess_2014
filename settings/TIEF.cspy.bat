@REM This bat file has been generated by the IAR Embeddded Workbench
@REM C-SPY interactive debugger,as an aid to preparing a command
@REM line for running the cspybat command line utility with the
@REM appropriate settings.
@REM
@REM After making some adjustments to this file, you can launch cspybat
@REM by typing the name of this file followed by the name of the debug
@REM file (usually an ubrof file). Note that this file is generated
@REM every time a new debug session is initialized, so you may want to
@REM move or rename the file before making changes.
@REM
@REM Note: some command line arguments cannot be properly generated
@REM by this process. Specifically, the plugin which is responsible
@REM for the Terminal I/O window (and other C runtime functionality)
@REM comes in a special version for cspybat, and the name of that
@REM plugin dll is not known when generating this file. It resides in
@REM the $TOOLKIT_DIR$\bin folder and is usually called XXXbat.dll or
@REM XXXlibsupportbat.dll, where XXX is the name of the corresponding
@REM tool chain. Replace the '<libsupport_plugin>' parameter
@REM below with the appropriate file name. Other plugins loaded by
@REM C-SPY are usually not needed by, or will not work in, cspybat
@REM but they are listed at the end of this file for reference.


"C:\Program Files\IAR Systems\Embedded Workbench 5.4\common\bin\cspybat" "C:\Program Files\IAR Systems\Embedded Workbench 5.4\avr\bin\avrproc.dll" "C:\Program Files\IAR Systems\Embedded Workbench 5.4\avr\bin\avrJtagIce-mkII.dll"  %1 --plugin "C:\Program Files\IAR Systems\Embedded Workbench 5.4\avr\bin\<libsupport_plugin>" --backend -B "--cpu=m128" "--enhanced_core" "-p" "C:\Program Files\IAR Systems\Embedded Workbench 5.4\avr\Config\iom128.ddf" "--eeprom_size" "4096" "-d" "jtagIceMkII" "--jtagice_clock=3600000" "--jtagice_leave_timers_running" "--drv_communication=USB" 


@REM Loaded plugins:
@REM    C:\Program Files\IAR Systems\Embedded Workbench 5.4\avr\bin\avrlibsupport.dll
@REM    C:\Program Files\IAR Systems\Embedded Workbench 5.4\common\plugins\CodeCoverage\CodeCoverage.dll
@REM    C:\Program Files\IAR Systems\Embedded Workbench 5.4\common\plugins\Profiling\Profiling.dll
@REM    C:\Program Files\IAR Systems\Embedded Workbench 5.4\common\plugins\stack\stack.dll
@REM    C:\Program Files\IAR Systems\Embedded Workbench 5.4\common\plugins\SymList\SymList.dll
