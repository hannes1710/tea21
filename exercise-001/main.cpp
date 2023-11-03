#include <fmt/chrono.h>
#include <fmt/format.h>

#include <iostream>
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

// .bss segment
int foo;

// .data segment
int data = 4711;

// .rodata segment
const int rodata = 5000; 

auto main(int argc, char **argv) -> int
{

    fmt::print("Wert der Variable rodata {}, Speicherort der Variable rodata {}", rodata, fmt::ptr(&rodata));

    return 0; /* exit gracefully*/
}
