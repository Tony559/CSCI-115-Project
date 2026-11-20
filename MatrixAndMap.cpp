#include "Utilities.h"
#include "MatrixAndMap.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <fstream>

#define ESC "\033["
#define RESET "\033[0m"

#define PLAINSBG "48;5;41"
#define MOUNTAINBG "48;5;243"
#define WATERBG "48;5;18"
#define FORESTBG "48;5;22"
#define DESERTBG "48;5;222"

#define FORESTTEXT "38;5;41"
#define MOUNTAINTEXT "38;5;249"
#define WATERTEXT "38;5;69"
#define DESERTTEXT "38;5;221"

//define animal colors


Matrix::Matrix() { 
    rows = 10;
    cols = 10;

    data = new Node*[rows];

    for (int i = 0; i < rows; i++) { 
        data[i] = new Node[cols]();
    }
}
// allocate the matrix rows and columns
Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;

    data = new Node*[rows]; // array of pointers for each row

    for (int i = 0; i < rows; i++) {
        data[i] = new Node[cols]();  // create each row with values set to 0
    }
}

// set an element at the given row and column
void Matrix::setValue(int row, int col, int val, char c) {
    data[row][col].weight = val;
    data[row][col].ch = c;
}

// return an element from the matrix
int Matrix::getValue(int r, int c) const {
    return data[r][c].weight;
}

// print each row of the matrix
void Matrix::print(int caseNum) const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (caseNum == 0) {
                std::cout << data[i][j].weight << " ";
            } 
            else if (caseNum == 1) { 
                char c = data[i][j].ch;

                if (c == '^') {
                    std::cout << ESC << MOUNTAINBG << ";" << MOUNTAINTEXT << "m" << '^' << RESET;
                }
                else if (c == '"') {
                    std::cout << ESC << FORESTBG << ";" << FORESTTEXT << "m" << '"' << RESET;
                }
                else if (c == '.') {
                    std::cout << ESC << DESERTBG << ";" << DESERTTEXT << "m" << '.' << RESET;
                }
                else if (c == ' ') {
                    std::cout << ESC << PLAINSBG << ";" << MOUNTAINTEXT << "m" << ' ' << RESET;
                }
                else if (c == '~') {
                    std::cout << ESC << WATERBG << ";" << WATERTEXT << "m" << '~' << RESET;
                }
                std::cout << " ";
            }
            
        }
        std::cout << std::endl;
    }
}

// delete each row first, then the array of row pointers
Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) { 
        delete[] data[i];
    }
    delete[] data;
}

// deep copy so the new matrix has its own allocated data
Matrix::Matrix(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;

    data = new Node*[rows]; // array of pointers for each row

    for (int i = 0; i < rows; i++) {
        data[i] = new Node[cols];

        for (int j = 0; j < cols; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}
// deep copy when assigning to an existing matrix
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // delete the old matrix
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;

        rows = other.rows;
        cols = other.cols;

        // allocate and copy the new matrix
        data = new Node*[rows];

        for (int i = 0; i < rows; i++) {
            data[i] = new Node[cols];

            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    return *this;
}
Map::Map() {
    weightedMap;
}
Map::Map(std::string file) { 
    weightedMap = fileToWeightedMap(file);
    weightedMap.print(1);
}

Matrix Map::fileToWeightedMap(std::string file) {
    Matrix result(23, 28);

    std::ifstream f(file);
    if (!f.is_open()) {
        throw std::runtime_error("Error opening file: " + file);
    }

    char c;
    int row = 0;
    int col = 0;

    while (row < 23 && f.get(c)) {
        int weight = 0;

        if (c == '^') {
            weight = 5;
        }
        else if (c == '"') {
            weight = 4;
        }
        else if (c == '.') {
            weight = 3;
        }
        else if (c == ' ') {
            weight = 2;
        }
        else if (c == '~') {
            weight = 1;
        }

        // only store terrain characters, skip borders and newlines
        if (weight != 0) {
            result.setValue(row, col, weight, c);
            col++;

            // move to the next row after 25 terrain characters
            if (col == 28) {
                col = 0;
                row++;
            }
        }
    }

    return result;
}

void Map::printColoredMap() { 

}
