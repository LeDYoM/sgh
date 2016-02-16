@echo off

if "%1"=="" goto show_usage

cd ..
cd ..
IF EXIST %1 GOTO dir_created

mkdir %1

:dir_created

cd %1

cmake .. 
goto end_success

:show_usage
echo Usage: regen.bat directory
goto end

:end_success
echo Completed sucessfully


:end