#include "sbu.hpp"

#include <Figlet.hh>

#include <iomanip>
#include <iostream>
#include <string>

namespace {
    constexpr auto kGreen = "\x1b[32m";
    constexpr auto kYellow = "\x1b[33m";
    constexpr auto kReset = "\x1b[0m";

    void printBanner() {
        std::cout << kGreen;
        Figlet::standard.print("SBU-EUR");
        std::cout << kReset << '\n';
        std::cout << kGreen << " :: SBU to Euro Converter ::              (v0.1.0)" << kReset << '\n';
    }

    void printConversion(float sbus) {
        std::cout << "  " << std::fixed << std::setprecision(2) << std::setw(12) << sbus
                << " SBU  =  " << kYellow << "\u20ac" << std::setw(10) << sbuToEuro(sbus)
                << kReset << '\n';
    }

    void usage() {
        std::cout << "usage: sbu-euro [sbus]\n";
        std::cout << "  sbu-euro 1000       convert 1000 SBU\n";
        std::cout << "  sbu-euro            interactive mode\n";
    }
} // namespace

int main(const int argc, char *argv[]) {
    printBanner();

    if (argc > 1) {
        if (const auto sbus = parseSbu(argv[1])) {
            printConversion(*sbus);
            return 0;
        }
        std::cerr << "error: '" << argv[1] << "' is not a non-negative number\n";
        usage();
        return 1;
    }

    std::cout << "Interactive mode \u2014 enter SBU amounts, 'q' to quit.\n";
    std::string line;
    while (true) {
        std::cout << "sbu> " << std::flush;
        if (!std::getline(std::cin, line)) break;
        const std::string_view input = trim(line);
        if (input.empty()) continue;
        if (input == "q" || input == "quit" || input == "exit") break;
        if (const auto sbus = parseSbu(input)) {
            printConversion(*sbus);
        } else {
            std::cout << "  invalid input: '" << input << "' (enter a number >= 0)\n";
        }
    }
    std::cout << "bye.\n";
    return 0;
}
