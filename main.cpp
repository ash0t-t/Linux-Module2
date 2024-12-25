#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>
#include <numeric>

void find_max(const std::vector<int>& data, int start, int end, int& result) {
    result = *std::max_element(data.begin() + start, data.begin() + end);
}

int main(int argc, char* argv[]) {
    int M = std::stoi(argv[1]);
    std::ifstream file("random.txt");
    std::vector<int> data((std::istream_iterator<int>(file)), std::istream_iterator<int>());
    int global_max = *std::max_element(data.begin(), data.end());
    auto start_single = std::chrono::high_resolution_clock::now();
    int single_max = global_max;
    auto end_single = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads(M);
    std::vector<int> results(M);
    int chunk_size = data.size() / M;
    auto start_multi = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < M; ++i) {
        int start = i * chunk_size;
        int end = (i == M - 1) ? data.size() : start + chunk_size;
        threads[i] = std::thread(find_max, std::cref(data), start, end, std::ref(results[i]));
    }
    for (auto& t : threads) t.join();
    int multi_max = *std::max_element(results.begin(), results.end());
    auto end_multi = std::chrono::high_resolution_clock::now();
    std::cout << "Numbers count: " << data.size() << " Maximum value: " << single_max << "\n";
    std::cout << "Single thread time: " << std::chrono::duration<double>(end_single - start_single).count() << "s\n";
    std::cout << "Multiple threads time: " << std::chrono::duration<double>(end_multi - start_multi).count() << "s\n";
    std::cout << "Results match: " << (single_max == multi_max ? "yes" : "no") << "\n";
    return 0;
}
