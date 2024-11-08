#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <random>

std::vector<std::vector<int>> generate_exact_cover_matrix(int num_subsets = 50, int num_elements = 30, double density = 0.3) {
    // Generate matrix
    std::vector<std::vector<int>> matrix(num_subsets, std::vector<int>(num_elements, 0));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < num_subsets; ++i) {
        bool has_one = false;
        for (int j = 0; j < num_elements; ++j) {
            if (dis(gen) < density || (j == num_elements - 1 && !has_one)) {
                matrix[i][j] = 1;
                has_one = true;
            } else {
                matrix[i][j] = 0;
            }
        }
    }

    // Write to file
    std::ofstream f("input.txt");
    
    // Write matrix
    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); ++j) {
            f << row[j];
            if (j < row.size() - 1) f << " ";
        }
        f << "\n";
    }
    
    return matrix;
}

int main() {
    // Generate a large instance
    auto matrix = generate_exact_cover_matrix(69, 690, 0.7);


    return 0;
}

