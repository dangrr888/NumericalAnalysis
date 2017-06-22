#! /bin/bash -

g++ -o bin/integration/main src/integration/lib/test/main.cpp -I src/integration/include/main --std=c++14

exit $?