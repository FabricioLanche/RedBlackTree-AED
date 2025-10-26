#ifndef BENCHMARKS_SECONDS_H
#define BENCHMARKS_SECONDS_H

#include "../RB_tree.h"
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

struct BenchmarkResult {
    double insert_time;
    double search_time;
    double delete_time;
    int data_size;
};

BenchmarkResult run_benchmark(int size) {
    const int NUM_REPETITIONS = 10;
    BenchmarkResult result;
    result.data_size = size;
    result.insert_time = 0.0;
    result.search_time = 0.0;
    result.delete_time = 0.0;
    for (int rep = 0; rep < NUM_REPETITIONS; rep++) {
        // Generar datos aleatorios únicos
        std::vector<int> data(size);

        // Generar secuencia ordenada
        for (int i = 0; i < size; i++) {
            data[i] = i + 1;
        }

        // Barajar para obtener orden aleatorio
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(data.begin(), data.end(), gen);

        RB_tree<int> tree;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size; i++) {
            tree.add_leaf(data[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        result.insert_time += diff.count();

        std::vector<int> search_keys(size / 10);
        for (int i = 0; i < size / 10; i++) {
            search_keys[i] = data[i * 10];
        }

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size / 10; i++) {
            tree.find(search_keys[i]);
        }
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        result.search_time += diff.count();

        std::vector<int> delete_keys(size / 10);
        for (int i = 0; i < size / 10; i++) {
            delete_keys[i] = data[i * 10];
        }

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < size / 10; i++) {
            tree.delete_leaf(delete_keys[i]);
        }
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        result.delete_time += diff.count();
    }
    
    result.insert_time /= NUM_REPETITIONS;
    result.search_time /= NUM_REPETITIONS;
    result.delete_time /= NUM_REPETITIONS;

    return result;
}

#endif // BENCHMARKS_SECONDS_H