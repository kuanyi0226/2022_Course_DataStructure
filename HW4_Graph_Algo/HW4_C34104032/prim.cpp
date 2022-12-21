#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

#define MAXVERTEX 26
#define INFINITY 1e9

typedef struct{
	int vertex1, vertex2;
	int weight;
} Edge;

void Prim(int graph[MAXVERTEX][MAXVERTEX], int totalVer, int startVer, vector<Edge>& mstGraph);
int findMinVer(vector<int> distance, vector<bool> visited, int totalVer);

int main(int argc, char** argv) {
	//prepare
	ifstream input; ofstream output;
	int temp_adjMatrix[MAXVERTEX][MAXVERTEX]; //represent a graph
	for(int i = 0; i < MAXVERTEX; i++)
		for(int j = 0; j < MAXVERTEX; j++)
			temp_adjMatrix[i][j] = 0;
	int totalVer = 0, totalEdge = 0;
	int startVer; //0~25

	//clear output file
	output.open("output_p.txt", ios::out);
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
			temp_adjMatrix[tempVer2-97][tempVer1-97] = tempWeight;
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

	//final mst's edges
	vector<Edge> mstGraph; //size = totalVertices -1
	//Start to find MST
	Prim(temp_adjMatrix, totalVer, startVer, mstGraph);

	//output result(by ascending weight)
	int compared[totalVer-1] = {0}; //false
	int temp_min_weight, temp_min_ver, outputNum = 0;
	output.open("output_p.txt", ios::app);
	if(output.is_open()){
		while(outputNum < totalVer-1){
			temp_min_weight = INFINITY;
			for(int i = 0; i < totalVer -1; i++){ //find a mst's edge which is min
				if(mstGraph[i].weight < temp_min_weight && compared[i] != 1){
					temp_min_ver = i;
					temp_min_weight = mstGraph[i].weight;
				}
			}
			compared[temp_min_ver] = 1; //true
			outputNum++;

			cout<< (char) (mstGraph[temp_min_ver].vertex1+97) <<" ";
			cout<< (char) (mstGraph[temp_min_ver].vertex2+97) <<" ";
			cout<< (mstGraph[temp_min_ver].weight) <<endl;

			output<< (char) (mstGraph[temp_min_ver].vertex1+97) <<" ";
			output<< (char) (mstGraph[temp_min_ver].vertex2+97) <<" ";
			output<< (mstGraph[temp_min_ver].weight) <<endl;
		}
	}
	output.close();
	
		
	return 0;
}

void Prim(int graph[MAXVERTEX][MAXVERTEX], int totalVer, int startVer, vector<Edge>& mstGraph){
	//original adjMatrix with size = totalVer*totalVer(not MAXVERTEX)
	int adjMatrix[totalVer][totalVer];
	for(int i = 0; i <totalVer; i++) //init
		for(int j = 0; j <totalVer; j++)
			adjMatrix[i][j] = graph[i][j];

	vector<int> distance(totalVer, INFINITY); //every distance is infinity
	vector<bool> visited(totalVer, false); //Vertices in MST
	int parent[totalVer]; //record every vertex's parent

	//put in first vertex(start vertex)
	distance[startVer] = 0; //distance to itself = 0
	parent[startVer] = -1;

	//find MST: having (totalVer -1 ) edges
	for(int i = 0; i < totalVer-1; i++){
		//find the target vertex with minimal weight
		//also, avoid finding visited one
		int minVer = findMinVer(distance, visited, totalVer);
		visited[minVer] = true; //update visited

		//update the distance to adjacent vertices from minVertex(selected vertex)
		//adjMatrix[minVer][ver]: distance(weight) from minVer to ver
		for(int ver = 0; ver < totalVer; ver++){
			if(adjMatrix[minVer][ver] !=0 && adjMatrix[minVer][ver] < distance[ver] && visited[ver] == false){
				distance[ver] = adjMatrix[minVer][ver];
				parent[ver] = minVer;
			}
		}
	}

	//output the result to mstGraph in main()
	//(totalVer -1) edges
	for(int i = 0; i <totalVer; i++){ 
		Edge tempEdge = {NULL,NULL,NULL};
		if(parent[i] >= 0){ // != -1
			tempEdge.weight = adjMatrix[parent[i]][i];
			//ascending order according to alphabetical order.
			tempEdge.vertex1 = (parent[i] < i) ? parent[i] : i; 
			tempEdge.vertex2 = (parent[i] < i) ? i : parent[i];

			mstGraph.push_back(tempEdge);
		}
		
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