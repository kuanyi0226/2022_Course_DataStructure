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
	//Initialize: start at (1,0)
	int counter = 0; //走了幾步
	mark[1][0] = 1;
	for(int i = 0; i<17; i++){
		for(int j=0;j<17;j++)
			cout<< mark[i][j];
		cout<<endl;
	}
	Stack stack(m*p); //capacity of stack
	Items temp(1,0,E); //set temp.x, temp.y, temp.dir
	stack.Push(temp);
	
	
	while(!stack.IsEmpty()){
		temp = stack.Top();
		stack.Pop();//unstack
		int i = temp.x; int j = temp.y; int d = temp.dir;
		
		while(d<9){//move forward
			int g = i + moveDir[d].a; int h = j + moveDir[d].b;
			//cout<< g<< " "<< h<<" "<< temp.dir << endl;


			if(g==m && h==p){//reach exit
				
				//output path
				//cout<<stack.;
				cout<<i<<" "<<j<<endl; // last two squares on the path
				cout<< m << " " << p << endl;
				cout<<"successfully escaped!!";
				return;
				
			}
			if(!(maze[g][h]) && !(mark[g][h])){ //new position

				mark[g][h] = 1;				
				temp.x = i; temp.y = j; temp.dir = d+1;
				//cout<< temp.x<< " "<< temp.y<<" "<< temp.dir << endl;
				stack.Push(temp); //stack it
				i = g; j =h; d = E; //East; move to (g, h)
				

			}
			
			else {
				//cout<< "d++"<<endl;
				d++; //try next dir
			} 
		} //End of finding dir
	} //End of finding path
	cout<<"Failed to escape."<<endl;
	
}//End of Path Func

//Definition of Stack class
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


