#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

struct node{
	int vertex;
	int weight;
};

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
			else{
				break;
			}
		}
	}

	// Shifts the root element to it's correct position.
	void siftDown(int k){
		int index = 0;

		while(index < num_elems){
			int startChild = index*k + 1;
			int endChild = index*k + k;
			int childIndex = -1;

			if(startChild >= num_elems){
				return;
			}
			if(endChild > num_elems){
				endChild = num_elems;
			}
			
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
			else{
				break;
			}
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
		heap.push_back(n1);

		num_elems++;

		siftUp(k);
	}

	// for getting the Min remove the root and place last element at its position and then shift it down
	// to the appropriate position
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
			printf("(%d, %d)\t", heap[j]->vertex, heap[j]->weight);
		}
		printf("\n");
	}


};

/*int main(){

	karyHeap obj;
	int ary = 3;

	node* x = (node*) malloc(sizeof(node*));
	x->vertex = 0;
	x->weight = 3;
	obj.insertIntoHeap(ary, x);
	node* x1 = (node*) malloc(sizeof(node*));
	x1->vertex = 1;
	x1->weight = 5;
	obj.insertIntoHeap(ary, x1);
	node* x2 = (node*) malloc(sizeof(node*));
	x2->vertex = 2;
	x2->weight = 8;
	obj.insertIntoHeap(ary, x2);
	node* x3 = (node*) malloc(sizeof(node*));
	x3->vertex = 3;
	x3->weight = 1;
	obj.insertIntoHeap(ary, x3);

	obj.showHeap();

	cout << obj.getMin(ary)->weight << endl;
	obj.showHeap();

	cout << obj.getMin(ary)->weight << endl;
	obj.showHeap();

	return 0;
}*/