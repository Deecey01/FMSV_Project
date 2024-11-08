#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to read matrix from file
vector<vector<long long>> readMatrixFromFile(const string& input_filename) {
    vector<vector<long long>> matrix;
    ifstream file(input_filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << input_filename << endl;
        return matrix;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<long long> row;
        long long value;
        while (iss >> value) {
            row.push_back(value);  // Convert each line into a list of integers
        }
        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

// Function to generate CNF content from the matrix
string generateCNF(const vector<vector<long long>>& matrix) {
    long long rows = matrix.size();    // Number of sets (rows)
    long long cols = matrix[0].size(); // Number of elements (columns)
    
    vector<vector<long long>> clauses;
    
    // Generating clauses for each element (columns)
    for (long long col = 0; col < cols; ++col) {
        vector<long long> covering_sets;
        
        // Collect the sets (rows) covering this element
        for (long long row = 0; row < rows; ++row) {
            if (matrix[row][col] == 1) {
                covering_sets.push_back(row + 1);
            }
        }
        
        // At least one of the sets must cover the element
        covering_sets.push_back(0);  // Add 0 to terminate the clause
        clauses.push_back(covering_sets);
        
        // No two sets should cover the same element
        for (size_t i = 0; i < covering_sets.size() - 1; ++i) {
            for (size_t j = i + 1; j < covering_sets.size() - 1; ++j) {
                vector<long long> clause = {-covering_sets[i], -covering_sets[j], 0};
                clauses.push_back(clause);
            }
        }
    }
    
    // Prepare CNF content
    stringstream cnf_content;
    cnf_content << "p cnf " << rows << " " << clauses.size() << "\n";
    
    for (const auto& clause : clauses) {
        for (long long var : clause) {
            cnf_content << var << " ";
        }
        cnf_content << "\n";
    }

    return cnf_content.str();
}

// Function to write CNF content to a file
void writeCNFToFile(const vector<vector<long long>>& matrix, const string& output_filename) {
    string cnf_content = generateCNF(matrix);
    ofstream file(output_filename);
    
    if (file.is_open()) {
        file << cnf_content;
        file.close();
    } else {
        cerr << "Error: Could not write to file " << output_filename << endl;
    }
}

// Main function to read matrix, generate CNF, and write it to output file
void mainProgram(const string& input_filename, const string& output_filename) {
    // Step 1: Read input matrix from the file
    vector<vector<long long>> matrix = readMatrixFromFile(input_filename);
    
    // Step 2: Generate CNF and write it to the output file
    writeCNFToFile(matrix, output_filename);
    cout << "CNF file has been written to " << output_filename << endl;
}

int main() {
    string input_filename = "input.txt";
    string output_filename = "exact_cover.cnf";
    
    mainProgram(input_filename, output_filename);
    
    return 0;
}
