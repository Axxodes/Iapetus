@echo off
g++ main.cpp -Os -s -flto -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-exceptions -fno-rtti -o fapplication.exe

application.exe
pause