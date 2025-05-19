@echo off
echo =================================================
echo           Qt Application Build Tool
echo =================================================

REM Set Qt environment paths
REM 使用原始的32位编译器
set QT_DIR=D:\qt\5.12.2\mingw73_32
set MINGW_DIR=D:\qt\Tools\mingw730_32\bin

echo Setting up environment...
set PATH=%QT_DIR%\bin;%MINGW_DIR%;%PATH%

echo.
echo Step 1: Running qmake...
qmake -o Makefile bleserver.pro -spec win32-g++ "CONFIG+=qtquickcompiler"

if not exist Makefile (
    echo ERROR: Failed to generate Makefile!
    goto ERROR
)

echo.
echo Step 2: Compiling application...
mingw32-make clean
mingw32-make -f Makefile.Release

echo.
echo Step 3: Deploying Qt dependencies...
if exist bin\bleserver.exe (
    windeployqt bin\bleserver.exe
) else (
    echo Searching for executable in bin directory...
    for %%f in (bin\*.exe) do (
        echo Found executable: %%f
        windeployqt %%f
        goto DEPLOY_DONE
    )
    echo WARNING: No executable found in bin directory!
)
:DEPLOY_DONE

echo.
echo =================================================
echo           Build and deployment completed!
echo =================================================
echo.
echo You can now run the application:
echo   bin\ARCS_Tool.exe
echo.

goto END

:ERROR
echo.
echo Build process failed!
echo.

:END
pause
