#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

#define MAXVERTEX 26 //a~z
#define INFINITY 1e9

int findMinVer(vector<int> distance, vector<bool> visited, int totalVer);
void Dijkstra(int graph[MAXVERTEX][MAXVERTEX], int totalVer, int startVer, vector<int>& shortest);

int main(int argc, char** argv) {
	//prepare
	ifstream input; ofstream output;
	int temp_adjMatrix[MAXVERTEX][MAXVERTEX]; //represent a graph
	for(int i = 0; i < MAXVERTEX; i++)
		for(int j = 0; j < MAXVERTEX; j++)
			temp_adjMatrix[i][j] = 0;
	int totalVer = 0, totalEdge = 0;
	int startVer; //0~25(a~z)

	//clear output file
	output.open("output_d.txt", ios::out);
	output.close();

	//Select input file
	char inputName[255];
	cout<< "Enter file name : ";
	cin>> inputName;

	//Start to scan input_file
	input.open(inputName);
	if(input.is_open()){
		char tempVer1, tempVer2, tempStartVer;
		int tempWeight, totalVerFinder[MAXVERTEX] = {0};

		input >> totalEdge;
		for(int i = 0; i < totalEdge; i++){
			input >> tempVer1 >>tempVer2 >> tempWeight;
			temp_adjMatrix[tempVer1-97][tempVer2-97] = tempWeight; //把a~z 讀成0~25
			totalVerFinder[tempVer1-97] = 1; totalVerFinder[tempVer2-97] = 1;
		}
		input >> tempStartVer; startVer = tempStartVer - 97; //read startVertex
		//find vertexNumber
		for(int i = 0; i < MAXVERTEX; i++){
			if(totalVerFinder[i] == 1)
				totalVer++;
		}
	}
	input.close();

	//create a vector to store final shortest path to each point
	vector<int> shortest(totalVer, 0); //init as 0

	Dijkstra(temp_adjMatrix, totalVer, startVer, shortest);

	//print out the result to console & file
	vector<bool> printed(totalVer, false); //printed?
	//do not print the vertex that the startVer can't reach(dis is INFINITY)
	for(int i = 0; i < totalVer; i++){
		if(shortest[i] >= INFINITY)
			printed[i] = true;
	}
	output.open("output_d.txt", ios::app);
	if(output.is_open()){
		for(int i = 0; i < totalVer; i++){
			int minVer = findMinVer(shortest, printed, totalVer);
			if(printed[minVer] == false){
				cout << (char)(minVer + 97) << " " << shortest[minVer] << endl;
				output << (char)(minVer + 97) << " " << shortest[minVer] << endl;
				printed[minVer] = true;
			}
		}

	}
	output.close();
	
	return 0;
}

void Dijkstra(int graph[MAXVERTEX][MAXVERTEX], int totalVer, int startVer, vector<int>& shortest){
	//original adjMatrix with size = totalVer*totalVer(not MAXVERTEX)
	int adjMatrix[totalVer][totalVer];
	for(int i = 0; i <totalVer; i++) //init
		for(int j = 0; j <totalVer; j++)
			adjMatrix[i][j] = graph[i][j];

	vector<int> distance(totalVer, INFINITY); //every distance is infinity
	vector<bool> visited(totalVer, false); //Vertices in graph

	//put in first vertex(start vertex)
	distance[startVer] = 0; //distance to itself = 0

	for(int i = 0; i < totalVer; i++){
		int minVer = findMinVer(distance, visited, totalVer);
		int minDis = distance[minVer];
		visited[minVer] = true;

		//find minVer's adjacent edge
		for(int j = 0; j < totalVer;j++){
			if(adjMatrix[minVer][j] > 0){ //has adjacent edge to another vertex
				if(minDis + adjMatrix[minVer][j] < distance[j]){ //繞路後比原本短
					distance[j] = minDis + adjMatrix[minVer][j];
				}
			}
		}
	}

	//copy the shortest path result to main()
	for(int i =0; i <totalVer; i++){
		shortest[i] = distance[i];
	}
}

int findMinVer(vector<int> distance, vector<bool> visited, int totalVer){
	int minVertex, min = INFINITY;
	
	for(int i = 0; i < totalVer; i++){
		if(visited[i] == false && distance[i] < min){
			min = distance[i];
			minVertex = i; 
		}
	}
	return minVertex;
}