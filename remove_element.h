#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <algorithm>
#include <cassert>

class NotFoundException {};

template<class T>
std::vector<T> RemoveElement(std::vector<T> list, T toRemove)
{
	typename std::vector<T>::iterator current = list.begin();
	for(; current != list.end(); ++current)
	{
		if(*current == toRemove)
		{
			break;
		}
	}

	if(current == list.end())
	{
		throw NotFoundException();
	}

	std::vector<T> newList(list.size() - 1);
	typename std::vector<T>::iterator mid = std::copy(list.begin(), current, newList.begin());
	++current; // Skip the item to be removed
	typename std::vector<T>::iterator end = std::copy(current, list.end(), mid);
	assert(end == newList.end());
	
	return newList;
}


#endif // COMMON_H

