#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define max(a, b) (a > b) ? a : b

class binary_heap {
public:
	struct bhnode { // node
		std::string data;
		int priority;
	};

	struct binary_heap_struct {
		bhnode *body;
		int bodysize;
		int numnodes;
		// binary_heap(int maxsize);
	};

	binary_heap(int maxsize) {
		body = new bhnode[maxsize+1];
		bodysize = maxsize;
		numnodes = 0;
	}
	~binary_heap() {
		delete body;
	}
	void swap(int a, int b) {
		std::swap(body[a],body[b]);
	}

	std::optional<bhnode> fetchMin() {
		if (numnodes <= 0) return std::nullopt;
		return {body[1]};
	}
private:
	bhnode *body;
	int max_nodes;
	int bodysize;
}

int main() {
	BinaryHeap bh(10);
}
