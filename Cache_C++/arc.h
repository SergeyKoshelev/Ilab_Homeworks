#pragma once

#include <cassert>
#include <iostream>
#include <list>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

size_t max(size_t a, size_t b)
{
	return  (b > a) ? b : a;
}

size_t min(size_t a, size_t b)
{
	return  (b < a) ? b : a;
}


template <typename T, typename KeyT = int>  
class cache_t {

	using List = std::list<T>;
	using ListIt = typename List::iterator;
	using Hash = std::unordered_map<KeyT, ListIt>;
	using HashIt = typename Hash::iterator;

	size_t size;
	List T1, T2, B1, B2; //T1, T2 - real; B1, B2 - ghost
	Hash T1_hash, T2_hash, B1_hash, B2_hash;
	size_t p = 0;

public:

	cache_t(size_t sz) : size(sz) {}

	//lookup elem in cache
	bool lookup(T elem)
	{
		//case 1: Hit in T1||T2
		auto T1_hit = T1_hash.find(elem);
		auto T2_hit = T2_hash.find(elem);
		if ((T1_hit != T1_hash.end()) || (T2_hit != T2_hash.end()))
		{
			case1(elem, T1_hit, T2_hit);  //swap
			return true;
		}

		//case 2: hit in ghost B1
		auto B1_hit = B1_hash.find(elem);
		if (B1_hit != B1_hash.end())
		{
			case2(elem, B1_hit); //swap
			return false;
		}

		//case 3: hit in ghost B2
		auto B2_hit = B2_hash.find(elem);
		if (B2_hit != B2_hash.end())
		{
			case3(elem, B2_hit); //swap
			return false;
		}

		//case 4: no hit at all
		size_t L1_length = B1.size() + T1.size();
		size_t L2_length = B2.size() + T2.size();
		if (L1_length == size)
			case4_1(elem);
		else if ((L1_length < size) && ((L1_length + L2_length) >= size))
			case4_2(elem, L1_length, L2_length);

		T1.push_front(elem);
		T1_hash[elem] = T1.begin();
		return false;
	}

	//number of lookups using cache in arr
	int lookups(int count, T* arr)
	{
		int hits = 0;
		for (int i = 0; i < count; i++)
			if (lookup(arr[i]))
				hits++;
		return hits;
	}

	//clear everything in cache
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

	
private:

	//replace elems according to p
	void replace(T elem)
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

	//hit in T1||T2
	void case1(T elem, HashIt T1_hit, HashIt T2_hit) 
	{
		if (T1_hit != T1_hash.end())
		{
			T1.erase(T1_hit->second);
			T1_hash.erase(T1_hit);
			T2.push_front(elem);
			T2_hash[elem] = T2.begin();
		}
		else
		{
			T2.erase(T2_hit->second);
			T2_hash.erase(T2_hit);
			T2.push_front(elem);
			T2_hash[elem] = T2.begin();
		}
	}

	//hit in ghost B1
	void case2(T elem, HashIt B1_hit) 
	{
		p = min(size, (p + max((B2.size()) / (B1.size()), 1)));
		replace(elem);

		B1.erase(B1_hit->second);
		B1_hash.erase(B1_hit);
		T2.push_front(elem);
		T2_hash[elem] = T2.begin();
	}

	//hit in ghost B2
	void case3(T elem, HashIt B2_hit) 
	{
		p = max(0, p - max((B1.size()) / (B2.size()), 1));
		replace(elem);

		B2.erase(B2_hit->second);
		B2_hash.erase(B2_hit);
		T2.push_front(elem);
		T2_hash[elem] = T2.begin();
	}

	//no hit at all, L1 is full
	void case4_1(T elem)
	{
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
	}

	//no hit at all, L1 isn't full and L1+L2>size
	void case4_2(T elem, size_t L1_length, size_t L2_length)
	{
		if ((L1_length + L2_length) == (2 * size))
		{
			B2_hash.erase(B2.back());
			B2.pop_back();
		}
		replace(elem);
	}
};
