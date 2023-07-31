@echo off

mkdir bin
pushd bin
mkdir release
popd
clang ./src/main.cpp -O3 -g -o ./bin/release/main.exe
pause