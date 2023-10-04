// your C++ implemnetation of the programming assignment 
// note: Do only one implemention, do not implement Python if you complete the C++ code
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cmath>

std::string getAlphabet(int base) {
    std::string alphabet;
    if (base == 2) {
        alphabet = "01";
    } else if (base == 8) {
        alphabet = "01234567";
    } else if (base == 10) {
        alphabet = "0123456789";
    } else if (base == 16) {
        alphabet = "0123456789ABCDEF";
    } else {
        std::cerr << "Error: Invalid base. Please use a base that is either 2, 8, 10, or 16." << std::endl;
        exit(1);
    }
    return alphabet;
}

bool isValidBase(int base) {
    return base == 2 || base == 8 || base == 10 || base == 16;
}

bool isValidLimit(int base, int limit, int number_of_digits) {
    int maxValue = std::pow(base, number_of_digits) - 1;
    return limit >= 0 && limit <= maxValue;
}

void performResetCarry(int base, int& num, int& resetCount, int& carryCount) {
    int resetValue = base;
    int carryValue = 1;

    while (num >= resetValue) {
        num -= resetValue;
        resetCount++;
        carryCount++;
    }

    while (num + carryValue >= base) {
        num -= resetValue;
        resetCount++;
        carryCount++;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <base> <number_of_digits> <limit>" << std::endl;
        return 1;
    }

    int base = std::stoi(argv[1]);
    int number_of_digits = std::stoi(argv[2]);
    int limit = std::stoi(argv[3]);

    if (!isValidBase(base)) {
        std::cerr << "Error: Invalid base. Please use a base that is either 2, 8, 10, or 16." << std::endl;
        return 1;
    }

    if (!isValidLimit(base, limit, number_of_digits)) {
        std::cerr << "Error: Invalid limit value for the specified number of digits." << std::endl;
        return 1;
    }
    std::string alphabet = getAlphabet(base);
    std::cout << "Alphabet: " << alphabet << std::endl;

    std::cout << std::setw(number_of_digits) << "Number" << " : Reset:Carry" << std::endl;

    for (int num = 0; num <= limit; num++) {
        int originalNum = num;
        int resetCount = 0;
        int carryCount = 0;
        performResetCarry(base, num, resetCount, carryCount);

        std::cout << std::setw(number_of_digits) << originalNum << " : ";
        if (resetCount > 0 || carryCount > 0) {
            std::cout << std::setw(2) << resetCount << ":" << std::setw(2) << carryCount;
        }
        std::cout << std::endl;
    }
    return 0;
}
