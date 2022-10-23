#include "MatrixTerm.h"

void MatrixTerm::setTerm(int Row, int Col, int Value){
	row = Row;
	col = Col;
	value = Value;
}

int MatrixTerm::getRow(){
	return row;
}
int MatrixTerm::getCol(){
	return col;
}
int MatrixTerm::getVal(){
	return value;
}


