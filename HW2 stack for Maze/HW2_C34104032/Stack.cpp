#include "Stack.h"

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
	return stack[top];
}

void Stack::Push(const Items& x){
	stack[++top] = x;
}

void Stack::Pop(){
	stack[top--].~Items();
}
