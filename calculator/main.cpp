#include <iostream>
#include <string>
#include <vector>

void printUsage() {
    std::cout << "Калькулятор (Вариант 16 - Аддитивный)" << std::endl;
    std::cout << "Доступные команды:" << std::endl;
    std::cout << "  add      - сложение всех чисел" << std::endl;
    std::cout << "  sub      - вычитание всех последующих из первого" << std::endl;
    std::cout << "  help     - справка по программе" << std::endl;
    std::cout << "Требование: от 4 до 6 операндов" << std::endl;
    std::cout << "Пример:" << std::endl;
    std::cout << "  ./calc -o add 10 20 30 40" << std::endl;
    std::cout << "  ./calc --operation sub 100 10 5 2" << std::endl;
}

class CalcCore {
private:
    std::vector<double> numbers;
    double total;

public:
    CalcCore() : total(0) {}

    void pushNum(double val) {
        numbers.push_back(val);
    }

    int countNums() const {
        return numbers.size();
    }
    void doAddition() {
        if (numbers.empty()) return;
        total = 0;
        for (size_t i = 0; i < numbers.size(); i++) {
            total += numbers[i];
        }
        std::cout << "Результат: " << total << std::endl;
    }

    void doSubtraction() {
        if (numbers.empty()) return;
        total = numbers[0];
        for (size_t i = 1; i < numbers.size(); i++) {
            total -= numbers[i];
        }
        std::cout << "Результат: " << total << std::endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 0;
    }

    std::string mode = "";
    CalcCore processor;

    for (int i = 1; i < argc; i++) {
        std::string token = argv[i];

        if (token == "-h" || token == "--help") {
            printUsage();
            return 0;
        }
        else if (token == "-o" || token == "--operation") {
            if (i + 1 < argc) {
                mode = argv[i + 1];
                i++;
            }
        }
        else if (token.substr(0, 12) == "--operation=") {
            mode = token.substr(12);
        }
        else if (token.substr(0, 3) == "-o=") {
            mode = token.substr(3);
        }
        else {
            try {
                double number = std::stod(token);
                processor.pushNum(number);
            } catch (...) {
                std::cerr << "Ошибка: не удалось распознать число: " << token << std::endl;
                printUsage();
                return 1;
            }
        }
    }

    if (mode == "") {
        std::cerr << "Ошибка: не задана операция" << std::endl;
        printUsage();
        return 1;
    }
    if (processor.countNums() < 4 || processor.countNums() > 6) {
        std::cerr << "Ошибка: требуется от 4 до 6 чисел Передано: " << processor.countNums() << std::endl;
        printUsage();
        return 1;
    }

    if (mode != "add" && mode != "sub") {
        std::cerr << "Ошибка: неизвестная операция '" << mode << std::endl;
        printUsage();
        return 1;
    }

    if (mode == "add") {
        processor.doAddition();
    } else if (mode == "sub") {
        processor.doSubtraction();
    }

    return 0;
}
