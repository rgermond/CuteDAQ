#!/bin/bash
g++ $1".cpp" -o $1 -std=c++11 -lsqlite3 -lboost_system -lpthread
