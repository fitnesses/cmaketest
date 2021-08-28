

#include <fmt/core.h>
#include <fmt/format.h>

#include <iostream>

#include "adder/adder.h"
#include "config.h"

int main(int argc, char const* argv[]) {
    /* code */
    std::cout << "hello world" << std::endl;

    fmt::print("hello\n");

    std::cout << PROJECT_VERSION_MAJOR << " git hash " << GIT_HASH << std::endl;

    std::cout << add(23.0f, 24) << std::endl;

    return 0;
}
