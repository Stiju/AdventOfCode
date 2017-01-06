cmake_minimum_required(VERSION 3.3)

project (aoc2016)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aoc2016 
	main.cpp
	common.cpp
	md5.cpp
	solutions/day01a.cpp
	solutions/day01b.cpp
	solutions/day02a.cpp
	solutions/day02b.cpp
	solutions/day03a.cpp
	solutions/day03b.cpp
	solutions/day04a.cpp
	solutions/day04b.cpp
	solutions/day05a.cpp
	solutions/day05b.cpp
	solutions/day06a.cpp
	solutions/day06b.cpp
	solutions/day07a.cpp
	solutions/day07b.cpp
	solutions/day08a.cpp
	solutions/day09a.cpp
	solutions/day09b.cpp
	solutions/day10a.cpp
	solutions/day12a.cpp
	solutions/day13a.cpp
	solutions/day14a.cpp)
