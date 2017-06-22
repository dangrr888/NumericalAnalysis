#! /bin/bash -

g++ -o bin/matrix/main src/matrix/lib/test/main.cpp -I src/matrix/include/main --std=c++14

exit $?