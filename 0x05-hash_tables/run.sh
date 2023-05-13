#!/bin/bash

# -lm flag will make the inbuilt math.h header file to work
# without this flag, the math.h header file might not work
gcc hash_tables.c -o a -lm
./a

