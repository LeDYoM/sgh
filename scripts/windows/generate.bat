@echo off

if "%1"=="" goto show_usage

cd ..
cd ..
IF NOT EXIST %1 GOTO dir_deleted

del %1 /Q /S
rmdir %1

:dir_deleted

mkdir %1
cd %1

cmake .. 
goto end_success

:show_usage
echo Usage: generate.bat directory
goto end

:end_success
echo Completed sucessfully


:end