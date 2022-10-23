#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#include "SparseMatrix.h"
#include "MatrixTerm.h"

void printTransTime(double,double); //declare a Timing Function 

int main(int argc, char** argv) {

	int maxRow;
    int maxCol;
    int terms=0; //amount of non-zero elements
    int row;
    int col;
    int value;
    //declare the variables for Timing
    LARGE_INTEGER freq1,freq2,beginTime1,beginTime2,endTime1,endTime2;
    

    ifstream p1In;
    p1In.open("p1.in");
    //Reading the row, col, terms from p1.in
	p1In>> maxRow >> maxCol;
	//Find terms value
	while(p1In>>row>>col>>value){
		terms++;
	}
	p1In.close();
	
	//Reading the data into smArray
	SparseMatrix sm(maxRow, maxCol, terms);
	MatrixTerm tempTerm;

	int termIndex = 0; //Record the term index in p1.in in every line
	p1In.open("p1.in");
	p1In>> maxRow >> maxCol;
	
	while(p1In>>row>>col>>value){		
		tempTerm.setTerm(row,col,value);
		sm.setSmArray(termIndex, tempTerm);
		termIndex++;
	}
	p1In.close();	
	
	//problem 1: Using traditional 2D array transpose method & print the result
	QueryPerformanceFrequency(&freq1); //get CPU Frequency1
	
	QueryPerformanceCounter(&beginTime1); //time begin for method1
	sm.tradiTranspose(); //transpose a 2D array
	QueryPerformanceCounter(&endTime1); //time end for method1
	
	sm.printResult(sm.tradiTranspose()); //print the result
		
	printTransTime((double)(endTime1.QuadPart-beginTime1.QuadPart),(double)freq1.QuadPart);//print Timing result
	
	//problem 2 : Using transpose method on textbook
	QueryPerformanceFrequency(&freq2); //get CPU Frequency2
	
	QueryPerformanceCounter(&beginTime2); //time begin for method2
	sm.Transpose(); //transpose method on textbook
	QueryPerformanceCounter(&endTime2); //time end for method2
	
	printTransTime((double)(endTime2.QuadPart-beginTime2.QuadPart),(double)freq2.QuadPart);//print Timing result
	
	
	return 0;

}

//Define timing function
void printTransTime(double difference, double freq){
	double timeOfSec = difference/freq; //in seconds
	//print to p1.out
	ofstream p1Out;
	p1Out.open("p1.out", ios::app);
	p1Out<< timeOfSec<<endl;
	p1Out.close();
	
}



