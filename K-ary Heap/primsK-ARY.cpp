
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <sstream>
using namespace std;
using namespace std::chrono;
# define INF 0x3f3f3f3f

int V;
struct node{
    int vertexU;
    int vertexV;
    int weight;
};

// K-ary heap code STARTS
class karyHeap{
private:
    vector<node*> heap;
    int num_elems = 0;
    
    // Shifts the last element of the heap to it's correct position
    void siftUp(int k){
        int index = num_elems-1;
        while(index > 0){
            int parent = floor((index -1)/k);
            if(heap[parent]->weight > heap[index]->weight){
                node* temp = heap[parent];
                heap[parent] = heap[index];
                heap[index] = temp;
                index = parent;
            }
            else
                break;
        }
    }
    
    // Shifts the root element to it's correct position.
    void siftDown(int k){
        int index = 0;
        while(index < num_elems){
            int startChild = index*k + 1;
            int endChild = index*k + k;
            int childIndex = -1;
            if(startChild >= num_elems)
                return;
            if(endChild > num_elems)
                endChild = num_elems;
            // find minimum of the k childrens of parent at index
            int min = heap[startChild]->weight;
            childIndex = startChild;
            for(int child = startChild+1; child <= endChild; child++ ){
                if(min > heap[child]->weight){
                    min = heap[child]->weight;
                    childIndex = child;
                }
            }
            // swap the min valued child with the parent
            if(heap[index]->weight > heap[childIndex]->weight){
                node* temp = heap[index];
                heap[index] = heap[childIndex];
                heap[childIndex] = temp;
                index = childIndex;
            }
            else
                break;
        }
    }
    
public:
    // constructor
    karyHeap(){
        heap.clear();
        num_elems = 0;
    }
    
    // for inserting just add the element to the end of heap and then shift it up to the correct position
    void insertIntoHeap(int k, node* n1){
        if(num_elems >= heap.size())
            heap.push_back(n1);
        else
            heap[num_elems] = n1;
        num_elems++;
        siftUp(k);
    }
    
    // for getting the Min remove the root and place last element at its position and then shift it down to the appropriate position
    node* getMin(int k){
        if(num_elems <= 0)
            return NULL;
        node* result = heap[0];
        num_elems -= 1;
        heap[0] = heap[num_elems];
        siftDown(k);
        heap[num_elems] = NULL;
        return result;
    }
    
    // Show the contents of the heap at this point
    void showHeap(){
        for(int j =0; j < num_elems; j++){
            printf("(%d, %d, %d)\t", heap[j]->vertexU, heap[j]->vertexV, heap[j]->weight);
        }
        printf("\n");
    }
    
    //size of heap
    int size(){
        return num_elems;
    }
};
// K-ary heap code ENDS

//Writing results to file
void FilePrintMST(vector<int> parent, vector<int> fWeight, int k, string pOutputMSTFileName){
    ofstream outputFile;
    outputFile.open(pOutputMSTFileName , ios::out | ios::app);
    outputFile<<"Minimum Spanning Tree in case of "<<k<<"-ary heap:"<<endl;
    for(int i = 0; i < V; i++){
        outputFile<<i<<" <- "<<parent[i]<<" = "<<fWeight[i]<<endl;
    }
    outputFile<<endl;
    outputFile.close();
    fWeight.clear();
    parent.clear();
}

//Prim's algorithm
void primMST(vector<vector<int> > graph, int k, string pOutputMSTFileName)
{
    karyHeap heap;
    vector<int> fWeight(V, INF);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);
    fWeight[0] = 0;
    parent[0] = 0;
    node* x = (node*) malloc(sizeof(node*));
    x->vertexU = 0;
    x->vertexV = 0;
    x->weight = 0;
    heap.insertIntoHeap(k, x);
    int countEdges = 0;
    
    for (int i = 0; i < V; i++) {
        if (visited[i] == false && graph[0][i] < fWeight[i]) {
            //cout << i << endl;
            fWeight[i] = graph[0][i];
            node* x = (node*) malloc(sizeof(node*));
            x->vertexU = 0;
            x->vertexV = i;
            x->weight = graph[0][i];
            heap.insertIntoHeap(k, x);
        }
    }
    
    while(countEdges < V){
        //cout<< countEdges<<endl;
        
        node* element = heap.getMin(k);
        int u = element->vertexU;
        int v = element->vertexV;
        int w = element->weight;
        
        if(visited[v] == false){
            //cout << v << endl;
            visited[v] = true;
            fWeight[v] = w;
            parent[v] = u;
            
            for (int i = 0; i < V; i++) {
                if (visited[i] == false && graph[v][i] < fWeight[i]) {
                    fWeight[i] = graph[v][i];
                    node* x = (node*) malloc(sizeof(node*));
                    x->vertexU = v;
                    x->vertexV = i;
                    x->weight = graph[v][i];
                    heap.insertIntoHeap(k, x);
                    
                }
               
            }
            //heap.showHeap();
            
            countEdges++;
        }
        
        //cout<< countEdges<<endl;
    }
    visited.clear();
    FilePrintMST(parent, fWeight, k, pOutputMSTFileName);
}

//main calling function
int main(int argc, char** argv)
{
    if(argc < 2){
		cout<< "Usage: ./prims <path to input graph>\n";
		exit(0);
	}

    vector<int> K;
    int start = 2, e = 0;
    
    ifstream infile;
    vector<int> list;
    vector<vector<int> > graph;
    
    string inputGraphFileName = argv[1];
    string outputFileName = "";
    string outputMSTFileName = "";
    
    replace(inputGraphFileName.begin(), inputGraphFileName.end(), '\\', '/');
    if(inputGraphFileName.find_last_of("/")!= string::npos){
    	int index = inputGraphFileName.find_last_of("/");

    	outputFileName = inputGraphFileName.substr(0,index) + "/timeTaken_"+ inputGraphFileName.substr(index+1);
        outputMSTFileName = inputGraphFileName.substr(0,index) + "/MST_"+ inputGraphFileName.substr(index+1);
    }
    else{
        outputFileName = "timeTaken_" + inputGraphFileName;
        outputMSTFileName = "MST_" + inputGraphFileName;
    }
    
    remove(outputFileName.c_str());
    
    //cout << inputGraphFileName << endl;
    //infile.open("/Users/shrishtijain/Desktop/Graphs/graph_120_6913.txt");
    infile.open(inputGraphFileName.c_str());
    if(!infile){
        cout<<"Error opening file"<<endl;
        exit(0);
    }
    string line;
    if(infile >> V){
        for(int i = 0; i < V - 2; i++){
            K.push_back(start);
            start++;
        }
        for(int i = 0; i < V; i++)
            list.push_back(INF);
        for(int i = 0; i < V; i++)
            graph.push_back(list);
        infile >> e;
        getline(infile,line);
        for(int i = 0; i < e; i++){
            vector<int> fields(3, 0);
            getline(infile, line);
            istringstream iss(line);
            iss>>fields[0]>>fields[1]>>fields[2];
            graph[fields[0]][fields[1]] = fields[2];
            graph[fields[1]][fields[0]] = fields[2];
        }
        infile.close();
    }
    for(int k = 0; k < K.size(); k++){
        auto start = high_resolution_clock::now();
        primMST(graph, K[k], outputMSTFileName);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        ofstream outputFile1;
        outputFile1.open(outputFileName.c_str(), ios::out | ios::app);
        if(!outputFile1){
        	cout<<"Error opening output file"<<endl;
        	exit(0);
   	}	
	outputFile1<<k + 1<<". For "<<K[k]<<"-ary heap: "<<duration.count()<<" microseconds"<<endl;
        outputFile1.close();
    }
    return 0;
}
