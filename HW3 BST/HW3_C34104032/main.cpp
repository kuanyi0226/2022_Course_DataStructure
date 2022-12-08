#include <iostream>
#include <fstream>
#include <vector> //可變大小版的array
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;

void printBoth(string); // print on console & into file
void printBothLine(string); //plus \n
void printNumBoth(int); // print on console & into file
void printNumBothLine(int); //plus \n

void printQuestions();

//about BST
typedef struct node{
	int data;
	node* leftChild;
	node* rightChild;
};

class BST{//Implement Binary Tree & its operations
	public:
		node* root = NULL; //pointer預設不是NULL

		void insert(node*);
		void delete_node(int);
		void search(int);
		void printpreorder(); void printpreorder(node*);
		void printinorder(); void printinorder(node*);
		void printpostorder(); void printpostorder(node*);
		void printlevelorder(); void printlevelorder(node*);

};
node* createNode(int Data){
	node* newNode = (node*)malloc(sizeof(node));
	newNode -> data = Data;
	newNode -> leftChild = NULL;
	newNode -> rightChild = NULL;
	return newNode;
}

int main(int argc, char** argv){
	//initialize
	ifstream input; ofstream output;
	char operation;
	BST bst;

	//Select input file
	char inputName[40];
	cout<< "Enter file name : ";
	cin>> inputName;
	cout<<endl;

	//output the input_file's name
	output.open("output.txt", ios::out); //Clean the file first
	output << "File name: " << inputName << endl;
	output << endl;
	output.close();

	//Start to scan input_file & do operations
	input.open(inputName);
	if(input.is_open()){
		char useless;
		string s;
		int number;
		vector<int> numbers;
		node* tempNode;
		while (1){
			numbers.clear(); //clear the numbers vector
			printQuestions();
			//read operation type
			input.get(operation);
			input.get(useless);
			if(operation == 'e' or operation == 'E'){
				printBothLine("Exit");
				break;
			}

			//read numbers
			if(operation != 'P' && operation != 'p' && operation != 'E' && operation != 'e'){
				getline(input, s);
				istringstream iss(s); //for string transferring to int
				while(iss >> number)
					numbers.push_back(number);
			}

			//do operations
			switch (operation){
				case 'I':
				case 'i':				
					printBothLine("Insert:");
					for(int i = 0; i < numbers.size()-1; i++){ //not include -1
					bst.insert(createNode(numbers[i]));
					}
					printBothLine("");
					break;
				case 'D':
				case 'd':
					printBothLine("Delete:");
					break;
				case 'S':
				case 's':
					printBothLine("Search:");
					for(int i = 0; i < numbers.size()-1; i++){ //not include -1
					bst.search(numbers[i]);
					}
					printBothLine("");
					break;
				case 'P':
				case 'p':
					printBothLine("Print:");
					bst.printpreorder(); printBothLine("");
					bst.printinorder(); printBothLine("");
					bst.printpostorder(); printBothLine("");
					bst.printlevelorder(); printBothLine("");
					printBothLine("");
					break;
			}
		}
	}
	input.close();
	
	

	return 0;
}
void printBoth(string s){
	cout<< s;

	ofstream output;
	output.open("output.txt", ios::app);
	output<< s;
	output.close();
}

void printBothLine(string s){
	cout<< s <<endl;

	ofstream output;
	output.open("output.txt", ios::app);
	output<< s <<endl;
	output.close();
}

void printNumBoth(int x){
	cout<< x;

	ofstream output;
	output.open("output.txt", ios::app);
	output<< x;
	output.close();
}

void printNumBothLine(int x){
	cout<< x <<endl;

	ofstream output;
	output.open("output.txt", ios::app);
	output<< x <<endl;
	output.close();
}

void printQuestions(){
	printBothLine("(I)nsert a number.");
	printBothLine("(D)elete a number.");
	printBothLine("(S)earch a number.");
	printBothLine("(P)rint 4 kinds of orders.");
	printBothLine("(E)xit");
	printBothLine("");
}


void BST::insert(node* newNode){
	if(root == NULL){
		root = newNode;
		printBoth("Number "); printNumBoth(newNode->data); printBothLine(" is inserted.");
		return;
	}

	node* p = root, *pp = NULL;
	while(p != NULL){
		pp = p;
		if(newNode->data < p->data) p = p->leftChild;
		else if (newNode->data > p->data) p = p->rightChild;
		else{ //existing node newNode-> data == p->data
			printBoth("Error! Number "); printNumBoth(newNode->data); printBothLine(" exists.");
			return;
		}
		
	}
	
	//reach bottom
	if(pp == NULL) pp = newNode;
	else if (newNode->data < pp->data) pp->leftChild = newNode;
	else pp->rightChild = newNode;
	printBoth("Number "); printNumBoth(newNode->data); printBothLine(" is inserted.");

}

void BST::search(int target){
	if(root == NULL){
		printBoth("Sorry! "); printNumBoth(target); printBothLine(" is not found.");
		return;
	}

	node* p = root, *pp = NULL;
	while(p != NULL){
		pp = p;
		if(target < p->data) p = p->leftChild;
		else if (target > p->data) p = p->rightChild;
		else{ //found
			printBoth("Bingo! "); printNumBoth(target); printBothLine(" is found.");
			return;
		}
		
	}
	//not found
	printBoth("Sorry! "); printNumBoth(target); printBothLine(" is not found.");
}

//Preorder
void BST::printpreorder(){ //driver
	printBoth("The tree in prefix order: ");
	printpreorder(root);
};
void BST::printpreorder(node* currentNode){ //workhorse
	if(currentNode){
		printNumBoth(currentNode->data);printBoth(" ");
		printpreorder(currentNode->leftChild);
		printpreorder(currentNode->rightChild);
	}
};
//Inorder
void BST::printinorder(){ //driver
	printBoth("The tree in infix order: ");
	printinorder(root);
};
void BST::printinorder(node* currentNode){ //workhorse
	if(currentNode){
		printinorder(currentNode->leftChild);
		printNumBoth(currentNode->data);printBoth(" ");
		printinorder(currentNode->rightChild);
	}
};
//Postorder
void BST::printpostorder(){ //driver
	printBoth("The tree in post order: ");
	printpostorder(root);
};
void BST::printpostorder(node* currentNode){ //workhorse
	if(currentNode){
		printpostorder(currentNode->leftChild);
		printpostorder(currentNode->rightChild);
		printNumBoth(currentNode->data);printBoth(" ");
	}
};

void BST::printlevelorder(){};


