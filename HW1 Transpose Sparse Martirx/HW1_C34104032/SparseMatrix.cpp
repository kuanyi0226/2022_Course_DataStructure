#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#include "SparseMatrix.h"
#include "MatrixTerm.h"



//Constructor
SparseMatrix :: SparseMatrix(int maxRow, int maxCol, int termsNum){
    rows = maxRow;
    cols = maxCol;
    terms = termsNum;
    smArray = (MatrixTerm*)malloc( sizeof(MatrixTerm) * terms );
}

//For Problem1: Store all the elements using the 2-dimensional array representation, then transpose it.
SparseMatrix SparseMatrix::tradiTranspose(){
	SparseMatrix b(cols,rows,terms); 
	if(terms>0){ //non-zero matrix
		//generate 2D array
		int twodiArray[rows][cols];
		for(int i =0;i<rows;i++){
			for(int j =0;j<cols;j++){
			twodiArray[i][j]=0;
			}
		}
		for(int i = 0; i<terms; i++){		
			twodiArray[(smArray+ i)->getRow()][(smArray+ i)->getCol()]= (smArray+ i)->getVal();					
		}
	    //establish temp 2D array for storing the transposed array
	    int transResult[cols][rows];
	    //transpose the 2D array
	    for(int i =0;i<cols;i++){
			for(int j =0;j<rows;j++){
			transResult[i][j]= twodiArray[j][i];
			}
		}
		//Store the transposed result into b.smArray
		int b_row, b_col, b_value;
		for(int termIndex = 0; termIndex<terms; termIndex++){
			b_row = (smArray+ termIndex)->getCol();
			b_col = (smArray+ termIndex)->getRow();
			b_value = transResult[b_row][b_col];
			(b.smArray+ termIndex)-> setTerm(b_row,b_col,b_value);
		}
		
		/*The "ordered" transposed result 
		for(int i =0;i<rows;i++){
			for(int j =0;j<cols;j++){
				if(transResult[i][j] !=0){
					p1Out<<"("<<i<<","<<j<<","<<transResult[i][j]<<")\n";
				}		
			}
		}
		*/
		
		
	}
	
	
	return b;

} //end of transpose

//For Problem2: 
SparseMatrix SparseMatrix::Transpose(){
	SparseMatrix b(cols,rows,terms);
	
	if(terms>0){ //non-zero matrix
		int currentB = 0; //index for transposed smArray (b's)
		int b_row, b_col, b_value; //variables in b.smArray
		
		for(int c = 0; c < cols; c++){ //transpose by cols
			for(int i = 0; i < terms; i++){ //scan the terms
				if((smArray+i)->getCol() == c){ //find elements in column c
					b_row = c;
					b_col = (smArray+ i)->getRow();
					b_value = (smArray+ i)->getVal();
					(b.smArray+ currentB)-> setTerm(b_row,b_col,b_value);
					currentB++;
				}
			}
		}
	}
	
	return b;
}//end of transpose

void SparseMatrix::setSmArray(int termIndex, MatrixTerm arrayTerm){ //put a MatrixTerm Object into smArray
	*(smArray+termIndex) = arrayTerm;	
}

void SparseMatrix::printResult(SparseMatrix result1){	
	//printout the result
	ofstream p1Out;
    p1Out.open("p1.out", ios::out);
    
    int result_row, result_col, result_val;
	for(int termIndex = 0; termIndex< terms; termIndex++){
		result_row = ((result1.smArray)+ termIndex)->getRow();
		result_col = ((result1.smArray)+ termIndex)->getCol();
		result_val = ((result1.smArray)+ termIndex)->getVal();
		
		p1Out<<"("<<(smArray+ termIndex)->getRow()<<", "<<(smArray+ termIndex)->getCol()<<", "<<(smArray+ termIndex)->getVal()<<
		") becomes ("<<result_row<<", "<<result_col<<", "<< result_val<<") in the transpose"<<endl;
	}
	
	
	p1Out.close(); //close p1.out
}



