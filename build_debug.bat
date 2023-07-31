@echo off

mkdir bin
pushd bin
mkdir debug
popd
clang ./src/main.cpp -O3 -g -o ./bin/debug/main.exe
pause