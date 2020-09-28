#pragma once

#include <cassert>
#include <iostream>
#include <list>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>


int min(int a, int b)
{
	return  (b < a) ? b : a;
}

int max(int a, int b)
{
	return  (b > a) ? b : a;
}


struct cache_t {

	size_t size;
	std::list<int> T1;
	std::list<int> T2;
	std::list<int> B1;
	std::list<int> B2;

	unsigned long long p = 0;

	using ListIt = std::list<int>::iterator;
	std::unordered_map<int, ListIt> T1_hash;
	std::unordered_map<int, ListIt> T2_hash;
	std::unordered_map<int, ListIt> B1_hash;
	std::unordered_map<int, ListIt> B2_hash;

	cache_t(size_t sz) : size(sz) {}

	bool lookup(int elem)
	{

		//case 1
		auto T1_hit = T1_hash.find(elem);
		auto T2_hit = T2_hash.find(elem);
		if ((T1_hit != T1_hash.end()) || (T2_hit != T2_hash.end()))
			if (T1_hit != T1_hash.end())
			{
				T1.erase(T1_hit->second);
				T1_hash.erase(T1_hit);
				T2.push_front(elem);
				T2_hash[elem] = T2.begin();
				return true;
			}
			else
			{
				T2.erase(T2_hit->second);
				T2_hash.erase(T2_hit);
				T2.push_front(elem);
				T2_hash[elem] = T2.begin();
				return true;
			}


		//case 2
		auto B1_hit = B1_hash.find(elem);
		if (B1_hit != B1_hash.end())
		{
			p = min(size, p + max((B2.size()) / (B1.size()), 1));
			replace(elem);

			B1.erase(B1_hit->second);
			B1_hash.erase(B1_hit);
			T2.push_front(elem);
			T2_hash[elem] = T2.begin();

			return false;
		}

		//case 3
		auto B2_hit = B2_hash.find(elem);
		if (B2_hit != B2_hash.end())
		{
			p = max(0, p - max((B1.size()) / (B2.size()), 1));


			replace(elem);

			B2.erase(B2_hit->second);
			B2_hash.erase(B2_hit);
			T2.push_front(elem);
			T2_hash[elem] = T2.begin();

			return false;
		}

		//case 4
		size_t L1_length = B1.size() + T1.size();
		size_t L2_length = B2.size() + T2.size();

		if (L1_length == size)
			if (T1.size() < size)
			{
				B1_hash.erase(B1.back());
				B1.pop_back();
				replace(elem);
			}
			else
			{
				T1_hash.erase(T1.back());
				T1.pop_back();
			}

		else if ((L1_length < size) && ((L1_length + L2_length) >= size))
		{
			if ((L1_length + L2_length) == (2 * size))
			{
				B2_hash.erase(B2.back());
				B2.pop_back();
			}


			replace(elem);
		}

		T1.push_front(elem);
		T1_hash[elem] = T1.begin();
		return false;
	}

	void replace(int elem)
	{
		auto B2_hit = B2_hash.find(elem);
		if ((T1.size() >= 1) && (((B2_hit != B2_hash.end()) && (T1.size() == p)) || (T1.size() >= p)))
		{
			T1_hash.erase(T1.back());
			T1.pop_back();
			B1.push_front(elem);
			B1_hash[elem] = B1.begin();
		}
		else
		{
			T2_hash.erase(T2.back());
			T2.pop_back();
			B2.push_front(elem);
			B2_hash[elem] = B2.begin();
		}
	}

	int lookups(int count, int* arr)
	{
		int hits = 0;
		for (int i = 0; i < count; i++)
			if (lookup(arr[i]))
				hits++;
		return hits;
	}

	void clear()
	{
		T1.clear();
		T2.clear();
		B1.clear();
		B2.clear();
		T1_hash.clear();
		T2_hash.clear();
		B1_hash.clear();
		B2_hash.clear();
	}
};
