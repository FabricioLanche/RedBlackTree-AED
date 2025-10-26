#ifndef BENCHMARKS_COMPARISONS_H
#define BENCHMARKS_COMPARISONS_H

#include "RB_tree_comparisons.h"
#include <random>
#include <vector>

struct BenchmarkComparisonResult {
    long long insert_comparisons;
    long long search_comparisons;
    long long delete_comparisons;
    int data_size;
};

BenchmarkComparisonResult run_benchmark_comparisons(int size) {
    BenchmarkComparisonResult result;
    result.data_size = size;
    
    // Generar datos aleatorios
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, size * 10);
    
    for (int i = 0; i < size; i++) {
        data[i] = dis(gen);
    }
    
    RB_tree_comparisons<int> tree;
    
    // Benchmark INSERT - número total de comparaciones
    tree.reset_comparisons();
    for (int i = 0; i < size; i++) {
        tree.add_leaf(data[i]);
    }
    result.insert_comparisons = tree.get_comparisons();
    
    // Benchmark SEARCH - número total de comparaciones
    std::vector<int> search_keys(size / 10);
    for (int i = 0; i < size / 10; i++) {
        search_keys[i] = data[i * 10];
    }
    
    tree.reset_comparisons();
    for (int i = 0; i < size / 10; i++) {
        tree.find(search_keys[i]);
    }
    result.search_comparisons = tree.get_comparisons();
    
    // Benchmark DELETE - número total de comparaciones
    std::vector<int> delete_keys(size / 10);
    for (int i = 0; i < size / 10; i++) {
        delete_keys[i] = data[i * 10];
    }
    
    tree.reset_comparisons();
    for (int i = 0; i < size / 10; i++) {
        tree.delete_leaf(delete_keys[i]);
    }
    result.delete_comparisons = tree.get_comparisons();
    
    return result;
}

#endif // BENCHMARKS_COMPARISONS_H