#include "Searching.h"
#include <iostream>

int main() {
	std::vector<int> a ({ 2,4,7,9,12,15,15,15,15,15,29,70,80,80});
	int result;
	result = binarySearch(a, 15);
	std::cout << result << std::endl;
	

}