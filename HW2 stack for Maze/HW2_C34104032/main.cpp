#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Stack.h"

#define mazeRow 17
#define mazeCol 17




//declare moving offsets
offsets move[8];
//declare maze array
char maze[mazeRow][mazeCol];
//initialize mark array
int mark[mazeRow+2][mazeCol+2] = {0};	

void Path(const int, const int);

int main(int argc, char** argv) {
	//Initialize moving offsets
	/*E*/move[0].a = 0; move[0].b = 1; /*SE*/move[1].a = 1; move[1].b = 1;
	/*S*/move[2].a = 1; move[2].b = 0; /*SW*/move[3].a = 1; move[3].b = -1;
	/*W*/move[4].a = 0; move[4].b = -1; /*NW*/move[5].a = -1; move[5].b = -1;
	/*N*/move[6].a = -1; move[6].b = 0; /*NE*/move[7].a = -1; move[7].b = 1;	

	char inputName[40];
	cout<< "enter filename : ";
	cin>> inputName;
	
	ifstream input;
	input.open(inputName);
	char c = ' ';
	//Read the maze into 2D Array and print it on Console Window
	if(!input.fail()){
		for(int i = 0; i < 17; i++){
			for(int j = 0; j<18; j++){ //every end of row is '\n'
				input.get(c);
				if(c != '\n'){
					maze[i][j] = c;
					cout<<maze[i][j];
				}
				
			}
			cout<<endl;
		}		
	}	
	input.close();
	
	Path(mazeRow, mazeCol);
	
	return 0;
}

void Path(const int m, const int p){
	//start at (1,0)
	mark[1][0] = 1;
	Stack stack(m*p); //capacity of stack
	Items temp(1,1,E); //set temp.x, temp.y, temp.dir
	stack.Push(temp);
	
	while(!stack.IsEmpty()){
		temp = stack.Top();
		stack.Pop();//unstack
		int i = temp.x; int j = temp.y; int d = temp.dir;
		while(d<8){//move forward
			int g = i + move[d].a; int h = j + move[d].b;
			if(g==m && h==p){//reach exit
				//output path
				cout<<stack;
				cout<<i<<" "<<j<<endl; // last two squares on the path
				cout<< m << " " << p << endl;
				return;
				
			}
			if((!maze[g][h]) && (!mark[g][h])){ //new position
				mark[g][h] = 1;
				temp.x = i; temp.y = j; temp.dir = d+1;
				stack.Push(temp); //stack it
				i = g; j =h; d = E/*East*/; //move to (g, h)
			}
			else d++; //try next dir
		}
	}
	cout<<"No path in maze"<<endl;
	
}


