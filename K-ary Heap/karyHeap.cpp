#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class karyHeap{
private: 
	vector<int> heap;
	int num_elems = 0;
	// Shifts the last element of the heap to it's correct position
	void siftUp(int k){
		int index = num_elems-1;

		while(index > 0){
			int parent = floor((index -1)/k);

			if(heap[parent] > heap[index]){
				int temp = heap[parent];
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
			int min = heap[startChild];
			childIndex = startChild;
			for(int child = startChild+1; child <= endChild; child++ ){
				if(min > heap[child]){
					min = heap[child];
					childIndex = child;
				}
			}
		
			// swap the min valued child with the parent
			if(heap[index] > heap[childIndex]){
				int temp = heap[index];
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
	void insertIntoHeap(int k, int val){
		heap.push_back(val);

		num_elems++;

		siftUp(k);
	}

	// for getting the Min remove the root and place last element at its position and then shift it down
	// to the appropriate position
	int getMin(int k){
		if(num_elems <= 0)
			return -1;

		int result = heap[0];
		num_elems -= 1;
		heap[0] = heap[num_elems];
		
		siftDown(k);

		heap[num_elems] = -1;

		return result;
	}

	// Show the contents of the heap at this point 
	void showHeap(){
		for(int j =0; j < heap.size(); j++){
			printf("%d\t", heap[j]);
		}
		printf("\n");
	}


};

/*int main(){

	karyHeap obj;

	
	obj.insertIntoHeap(3, 3);
	obj.insertIntoHeap(3, 5);
	obj.insertIntoHeap(3, 8);
	obj.insertIntoHeap(3, 1);

	obj.showHeap();

	cout << obj.getMin(3) << endl;
	obj.showHeap();

	cout << obj.getMin(3) << endl;
	obj.showHeap();

	cout << obj.getMin(3) << endl;
	obj.showHeap();

	cout << obj.getMin(3) << endl;
	obj.showHeap();

	cout << obj.getMin(3) << endl;
	obj.showHeap();

	return 0;
}*/