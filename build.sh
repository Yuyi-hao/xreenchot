#!/bin/sh
CC=gcc
CFLAGS="-Wall -Wextra"

gcc main.c $(pkg-config --cflags --libs x11)  -o main
