#!/bin/sh
CC=gcc
CFLAGS="-Wall -Wextra"

gcc x11windowexample.c $(pkg-config --cflags --libs x11)  -o example
