#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
// #include <optional>


struct bhnode { // node
	string data;
	int priority;
};

struct binary_heap {
	bhnode *body;
	int bodysize;
	int numnodes;
	// binary_heap(int maxsize);

	binary_heap(int maxsize) {
		body = new bhnode[maxsize+1];
		bodysize = maxsize;
		numnodes = 0;
	}

	~binary_heap() {
		delete body;
	}

	void bh_swap(int a, int b) {
		swap(body[a],body[b]);
	}

	bhnode *fetchMin() {
		if (numnodes <= 0) return NULL;
		return body[1];
	}

	int insert(bhnode node) {
		if (numnodes > bodysize) {
			return -1; // or expand
		}
		body[++numnodes] = node;
		for (size_t i = numnodes;
			i > 1 && body[i].priority > body[i/2].priority;
			i /= 2) {
			bh_swap(i, i/2);
		}
		return 0;
	}

	void heapify(size_t index) {
		for (;;) {
			auto left = index + index, right = left + 1;
			// Who is greater, [index], [left], [right]?
			auto largest = index;
			if (left <= numnodes && body[left].priority > body[index].priority)
				largest = left;
			if (right <= numnodes && body[right].priority > body[largest].priority)
				largest = right;
			if (largest == index) break;
				bh_swap(index, largest);
			index = largest;
		}
	}
};

int main() {
	binary_heap bh(100);
}
