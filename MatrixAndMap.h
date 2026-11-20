#ifndef MATRIXANDMAP_H
#define MATRIXANDMAP_H
#include "Utilities.h"
#include <iostream>
#include <string>


    // 5 types of cells
    //
    // 1 high mountain M
    // 2 plain         w
    // 3 forest        T
    // 4 desert        _
    // 5 ocean         ~

    

    class Matrix {
    private:
        Node** data;
        int rows;
        int cols;
    public: 
        Matrix();
        Matrix(int r, int c);
        void setValue(int row, int col, int val, char c);
        int getValue(int r, int c) const;
        void print(int caseNum) const;
        ~Matrix();

        

        
        Matrix(const Matrix& other); // deep copy constructor
        Matrix& operator=(const Matrix& other);
        
};
    class Map {
    private:
        Matrix weightedMap;
    public:
        Map();
        Map(std::string file);
        Matrix fileToWeightedMap(std::string file);
        void printColoredMap();
    };






#endif