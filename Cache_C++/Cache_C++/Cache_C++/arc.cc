#include <cassert>
#include <iostream>
#include <list>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include "arc.h"



int main()
{
		int hits = 0;
		size_t cache_size = 0;
		int req_count = 0;

		std::cout << "Input cache size and number of requests\n";
		std::cin >> cache_size >> req_count;
		assert(std::cin.good());

		struct cache_t ARC{ cache_size };
		int req = 0;

		std::cout << "Input requests" << std::endl;
		for (int i = 0; i < req_count; i++)
		{
			std::cin >> req;
			assert(std::cin.good());
			if (ARC.lookup(req))
				hits++;
		}

		std::cout << "Hits: " << hits << "\n";

	//
	//Tests were realized in special test project using GTest
    //
	/*
	else //tests from file
	{

		std::ifstream file("tests.txt");
		int hits = 0;
		int req_count = 0;

		for (size_t cache_size = 0; file >> cache_size; )
		{
			file >> req_count;
			cache_t ARC{ cache_size };
			int req = 0;
			hits = 0;

			std::cout << "Test: cache size = " << cache_size << "  requests count = " << req_count << std::endl;
			std::cout << "Requests: ";

			for (int i = 0; i < req_count; i++)
			{
				file >> req;
				std::cout << req << " ";
				if (ARC.lookup(req))
					hits++;
			}
			std::cout << std::endl;

			int correct_count = 0;
			file >> correct_count;
			std::cout << "Hits: " << hits << " Correct number: " << correct_count;
			if (hits == correct_count)
				std::cout << " Test passed" << std::endl << std::endl;
			else
				std::cout << " Test failed" << std::endl << std::endl;

			ARC.clear();

		}

		file.close();
	}
*/
	return 0;
}