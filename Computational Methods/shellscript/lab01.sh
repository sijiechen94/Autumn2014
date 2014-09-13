#!/bin/bash

gcc -O3 src/lab01.c -o bin/foo
time ./bin/foo
od -F output/lab01
