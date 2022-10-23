#ifndef MATRIXTERM_H
#define MATRIXTERM_H

class MatrixTerm{
    public:
    	void setTerm(int,int,int);
    	int getRow(); int getCol(); int getVal(); 

    	
    private:
        int row, col, value;
};

#endif
