@echo off

if exist del default.dll /f default.dll
if exist del tem.cpp /f tem.cpp

resource_builder.exe cl default --keep default.jpg
