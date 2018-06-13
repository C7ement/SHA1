cmake_minimum_required(VERSION 3.10)
project(sha1project C)

set(CMAKE_C_STANDARD 99)

add_executable(sha1 main.c sha1.c sha1.h sha1opt.c sha1opt.h)