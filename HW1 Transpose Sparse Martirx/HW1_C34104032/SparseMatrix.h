#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "MatrixTerm.h"
#include <cstdlib>

class SparseMatrix{
public:
	//Constructor
    SparseMatrix(int, int, int);
    SparseMatrix tradiTranspose(); //for Problem1
    SparseMatrix Transpose(); //for Problem2
    void setSmArray(int, MatrixTerm);
    void printResult(SparseMatrix); //print the required Sample Output

private:
	int rows, cols, terms;
	MatrixTerm * smArray; //terms = capacity of smArray
};


#endif
