@echo off
echo =================================================
echo        Qt Application Fast Build Tool
echo =================================================

REM Set Qt environment paths
set QT_DIR=D:\qt\5.12.2\mingw73_64
set MINGW_DIR=D:\qt\Tools\mingw730_64\bin

echo Setting up environment...
set PATH=%QT_DIR%\bin;%MINGW_DIR%;%PATH%

echo.
echo Step 1: Running qmake if Makefile doesn't exist...
if not exist Makefile (
    qmake -o Makefile bleserver.pro -spec win32-g++ "CONFIG+=qtquickcompiler"
)

if not exist Makefile (
    echo ERROR: Failed to generate Makefile!
    goto ERROR
)

echo.
echo Step 2: Compiling application (incremental build)...
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
echo      Fast Build and deployment completed!
echo =================================================
echo.
echo You can now run the application:
echo   bin\bleserver.exe
echo.

goto END

:ERROR
echo.
echo Build process failed!
echo.

:END
pause
