@echo off

pushd ..
Vendor\Binaries\Premake\Windows\premake5.exe --file=BuildPremake.lua vs2022
popd
pause