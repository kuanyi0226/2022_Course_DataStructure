#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

//Initialize the framework of maze problem solving
#define mazeRow 17
#define mazeCol 17

struct offsets{
	int a;//row
	int b;//col
} ;
enum directions{
	O, E, SE, S, SW, W, NW, N, NE
};

struct Items{ //list of triple to record the pass history
	int x, y, dir;
	//Constructor
	Items(){
	}
	Items(int i, int j, directions Dir){
		x = i; y = j; dir = Dir;
	}	
};

class Stack
{
	private:
		Items* stack; //an Array
		int top;
		int stackCapacity;
		
	public:
		Stack(int stackCapacity);
		bool IsEmpty();
		Items& Top();
		void Push(const Items& item);
		void Pop();
	
};


//declare moving offsets
offsets moveDir[9]; 

//declare maze array
char maze[mazeRow][mazeCol];
//initialize mark array
int mark[mazeRow][mazeCol] = {0};	

void Path(const int, const int);
void printStep(int count, int row, int col);

int main(int argc, char** argv) {
	//Initialize moving offsets
	/*O*/moveDir[0].a = 0; moveDir[0].b = 0;
	/*E*/moveDir[1].a = 0; moveDir[1].b = 1; /*SE*/moveDir[2].a = 1; moveDir[2].b = 1;
	/*S*/moveDir[3].a = 1; moveDir[3].b = 0; /*SW*/moveDir[4].a = 1; moveDir[4].b = -1;
	/*W*/moveDir[5].a = 0; moveDir[5].b = -1; /*NW*/moveDir[6].a = -1; moveDir[6].b = -1;
	/*N*/moveDir[7].a = -1; moveDir[7].b = 0; /*NE*/moveDir[8].a = -1; moveDir[8].b = 1;	

	char inputName[40];
	cout<< "enter filename : ";
	cin>> inputName;
	
	ifstream input;
	input.open(inputName);
	char c = ' ';
	//Read the maze into 2D Array and print it on Console Window
	if(!input.fail()){
		for(int i = 0; i < mazeRow; i++){
			for(int j = 0; j<mazeCol+1; j++){ //every end of row is '\n'
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
	
	Path(mazeRow, mazeCol);//m=17 p=17

	system("pause");
	return 0;
}

void Path(const int m, const int p){
	//Initialize: start at (1,0)
	int counter = 0; //total steps
	mark[1][0] = 1;
	Stack stack(m*p); //capacity of stack
	Items temp(1,0,E); //set temp.x, temp.y, temp.dir
	stack.Push(temp);
	
	while(!stack.IsEmpty()){
		temp = stack.Top();
		stack.Pop();//unstack
		int i = temp.x; int j = temp.y; int d = temp.dir;	
		
		while(d<9){//move forward
			int g = i + moveDir[d].a; int h = j + moveDir[d].b;

			if(g==(m-2) && h==(p-1)){//reach exit	
				//print last two steps on the path 	
				ofstream stepOut;
				stepOut.open("output.txt", ios::app);

				stepOut<<counter<< ":"<< i<<","<<j<<endl; 
				cout<<counter<< ":"<< i<<","<<j<<endl; 
				counter++;

				stepOut<<counter<< ":"<< m-2<<","<<p-1<<endl;
				cout<<counter<< ":"<< m-2<<","<<p-1<<endl;

				stepOut<<"successfully escaped!!"<<endl;	
				cout<<"successfully escaped!!"<<endl;			
				stepOut.close();
									
				return;
				
			}
			if(maze[g][h]=='0' && mark[g][h] == 0){ //new position

				mark[g][h] = 1;				
				temp.x = i; temp.y = j; temp.dir = d+1; 
				//d or temp.dir can only be 1~8
				if(temp.dir == 9){
					temp.dir = 1;
				}
								
				printStep(counter, temp.x, temp.y);
				counter++;

				stack.Push(temp); //stack it
				i = g; j =h; d = E; //East; move to (g, h)
				

			}
			
			else {
				d++; //try next dir
				
				if(d==9){//record and print the position having no way to go
					printStep(counter, i, j);
					counter++;
				}

			} 
		} //End of finding dir
	} //End of finding path
	ofstream stepOut;
	stepOut.open("output.txt", ios::app);
	stepOut << "fail to escape."<< endl;
	cout<<"Failed to escape."<<endl;
	stepOut.close();
	
}//End of Path Func

void printStep(int count, int row, int col){
	ofstream stepOut;
	if(count == 0){//While writing the first one, clear up the file first!
		stepOut.open("output.txt", ios::out);
		stepOut << count << ":" << row << "," << col << endl;
		cout << count << ":" << row << "," << col << endl;

		stepOut.close();
	}
	else{ //step by step, print the steps to the end of file
		stepOut.open("output.txt", ios::app);
		stepOut << count << ":" << row << "," << col << endl;
		cout << count << ":" << row << "," << col << endl;

		stepOut.close();
	}


}

//Further Definition of Stack class
//Const.
Stack::Stack(int StackCapacity)
{
	stackCapacity = StackCapacity;
	stack = new Items[stackCapacity];//(Items*)malloc(sizeof(Items) * stackCapacity); //include <cstdlib>
	top = -1;
}

inline bool Stack::IsEmpty(){
	return top == -1;
}


inline Items& Stack::Top() {
	if(!IsEmpty()){
		return stack[top];
	}
	
}

void Stack::Push(const Items& x){
	stack[++top] = x;
}

void Stack::Pop(){//
	if(!IsEmpty()){
		top--;
	}
	
}


