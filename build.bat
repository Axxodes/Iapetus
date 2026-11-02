@echo off
g++ -Os -s -flto -Wall -Werror -Wextra -pedantic -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -Wl,--gc-sections -Ilibs -Ilibs/Hyperion src/main.cpp recourse.rc -o iapetus.exe -Ivulkan/Include -Lvulkan/Lib -lvulkan-1 -lgdi32 -mwindows

iapetus.exe