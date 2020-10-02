#include <cassert>
#include <iostream>
#include <list>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include "arc.h"
//#include "arc2.h"



int main()
{
	int hits = 0;
	size_t cache_size = 0;
	int req_count = 0;

	std::cout << "Input cache size and number of requests\n";
	std::cin >> cache_size >> req_count;
	//assert(std::cin.good());

	cache_t<int> ARC{ cache_size };
	//cache_t ARC{ cache_size };
	int req = 0;

	std::cout << "Input requests" << std::endl;
	for (int i = 0; i < req_count; i++)
	{
		std::cin >> req;
		//assert(std::cin.good());
		if (ARC.lookup(req))
			hits++;
	}

	std::cout << "Hits: " << hits << "\n";
	return 0;
}