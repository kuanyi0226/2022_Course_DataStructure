#ifndef STACK_H
#define STACK_H
#include <cstdlib>

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

#endif
