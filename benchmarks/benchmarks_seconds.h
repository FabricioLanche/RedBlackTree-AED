#ifndef BENCHMARKS_H
#define BENCHMARKS_H

#include "RB_tree.h"
#include <chrono>
#include <random>
#include <vector>

struct BenchmarkResult {
    double insert_time;
    double search_time;
    double delete_time;
    int data_size;
};

BenchmarkResult run_benchmark(int size) {
    BenchmarkResult result;
    result.data_size = size;
    
    // Generar datos aleatorios
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, size * 10);
    
    for (int i = 0; i < size; i++) {
        data[i] = dis(gen);
    }
    
    RB_tree<int> tree;
    
    // Benchmark INSERT - tiempo acumulado de todas las inserciones
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
        tree.add_leaf(data[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    result.insert_time = diff.count();
    
    // Benchmark SEARCH - tiempo acumulado de todas las búsquedas
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
    result.search_time = diff.count();
    
    // Benchmark DELETE - tiempo acumulado de todas las eliminaciones
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
    result.delete_time = diff.count();
    
    return result;
}

#endif // BENCHMARKS_H