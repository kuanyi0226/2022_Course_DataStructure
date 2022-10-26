#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#define mazeRow 17
#define mazeCol 17

struct offsets{
	int a;//row
	int b;//col
} ;
enum directions{
	E, SE, S, SW, W, NW, N, NE
};

struct Items{ //list of triple to record the pass history
	int x, y, dir;
	//Constructor
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
offsets moveDir[8];

//declare maze array
char maze[mazeRow][mazeCol];
//initialize mark array
int mark[mazeRow+2][mazeCol+2] = {0};	

void Path(const int, const int);

int main(int argc, char** argv) {
	//Initialize moving offsets
	/*E*/moveDir[0].a = 0; moveDir[0].b = 1; /*SE*/moveDir[1].a = 1; moveDir[1].b = 1;
	/*S*/moveDir[2].a = 1; moveDir[2].b = 0; /*SW*/moveDir[3].a = 1; moveDir[3].b = -1;
	/*W*/moveDir[4].a = 0; moveDir[4].b = -1; /*NW*/moveDir[5].a = -1; moveDir[5].b = -1;
	/*N*/moveDir[6].a = -1; moveDir[6].b = 0; /*NE*/moveDir[7].a = -1; moveDir[7].b = 1;	

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
			int g = i + moveDir[d].a; int h = j + moveDir[d].b;
			if(g==m && h==p){//reach exit
				//output path
				//cout<<stack.;
				cout<<i<<" "<<j<<endl; // last two squares on the path
				cout<< m << " " << p << endl;
				return;
				
			}
			if((!maze[g][h]) && (!mark[g][h])){ //new position
				mark[g][h] = 1;
				temp.x = i; temp.y = j; temp.dir = d+1;
				stack.Push(temp); //stack it
				i = g; j =h; d = E; //East; move to (g, h)
			}
			else d++; //try next dir
		} 
	} //End of while
	cout<<"No path in maze"<<endl;
	
}//End of Path Func

//Definition of Stack class
//Const.
Stack::Stack(int StackCapacity)
{
	stackCapacity = StackCapacity;
	stack = (Items*)malloc(sizeof(Items) * stackCapacity); //include <cstdlib>
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

void Stack::Pop(){
	if(!IsEmpty()){
		stack[top--].~Items();
	}
	
}


