@echo off
g++ src/main.cpp -Os -s -flto -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-exceptions -fno-rtti -o Iapetus.exe

Iapetus.exe
pause