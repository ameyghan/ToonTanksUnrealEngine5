@echo off

call %~dp0\vars.bat

set EDITOR_CMD="%UE4EDITOR_EXE%" "%UPROJECT_PATH%" %-log
echo %EDITOR_CMD%
start "" %EDITOR_CMD%