#include <format>
#include <iostream>
#include <map>
#include <syncstream>
#include <thread>

constexpr int kThreadCount = 5;

void PerformComputations(const std::string &set_name, const int action_number) {
    std::osyncstream synced_output(std::cout);
    synced_output << std::format("З набору {}, виконано дію {}.\n", set_name, action_number);
    synced_output << "Обчислення розпочато\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    synced_output << "Обчислення завершено\n";
}


int main() {
    const std::map<std::string, int> set_actions = {
        {"a", 6},
        {"b", 5},
        {"c", 8},
        {"d", 5},
        {"e", 8},
        {"f", 9},
        {"g", 4},
        {"h", 5},
        {"i", 6},
        {"j", 8}
    };

    std::array<std::jthread, kThreadCount> threads;

    return 0;
}
