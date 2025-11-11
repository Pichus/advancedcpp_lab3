#include <barrier>
#include <format>
#include <iostream>
#include <map>
#include <syncstream>
#include <thread>
#include <vector>
#include <memory>

constexpr int kThreadCount = 5;

void PerformComputations(const char set_name, const int action_number) {
    std::osyncstream(std::cout)
            << std::format("З набору {}, виконано дію {}.\n", set_name, action_number);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void RunMultithreaded(const std::vector<std::string> &thread_tasks, std::map<char, int> &set_action_current_ids) {
    std::vector<std::jthread> threads(kThreadCount);
    std::barrier sync_point(kThreadCount);

    std::vector<std::vector<std::pair<char, int> > > set_actions;

    for (int i = 0; i < kThreadCount; i++) {
        for (const char &set_name: thread_tasks[i]) {
            set_actions[i].emplace_back(set_name, set_action_current_ids[set_name]++);
        }
    }

    for (int thread_i = 0; thread_i < kThreadCount; thread_i++) {
        threads.emplace_back([&set_actions, &thread_i, &sync_point]() {
            for (const auto [set_name, action_id]: set_actions[thread_i]) {
                if (set_name != ' ') {
                    PerformComputations(set_name, action_id);
                }
                sync_point.arrive_and_wait();
            }
        });
    }
}


int main() {
    std::cout << "Обчислення розпочато\n";

    std::map<char, int> set_action_current_ids;

    for (int i = 0; i < 10; i++) {
        char set_name = 'a' + i; // convert i from int to char
        set_action_current_ids[set_name] = 1;
    }

    std::vector<std::string> thread_tasks = {
        "aabcdeeffhiijj",
        "abccdeefghi jj",
        "abccdeffghi jj",
        "abccdeffghi j ",
        "abcdeffghi j "
    };

    RunMultithreaded(thread_tasks, set_action_current_ids);


    std::cout << "Обчислення завершено\n";


    // const std::map<std::string, int> set_actions = {
    //     {"a", 6},
    //     {"b", 5},
    //     {"c", 8},
    //     {"d", 5},
    //     {"e", 8},
    //     {"f", 9},
    //     {"g", 4},
    //     {"h", 5},
    //     {"i", 6},
    //     {"j", 8}
    // };

    return 0;
}
