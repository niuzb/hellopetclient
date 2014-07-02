#ifndef MEMSORT_HPP_
#define MEMSORT_HPP_

#include <vector>
#include <map>
#include <string>
#include <limits.h>
#include <functional>
#include <algorithm>

namespace base {
namespace memsort {

namespace template_function_for_default_sort {

template<class Type>
inline bool operator<(const Type& value1, const Type& value2) {
	std::string value_str1 = std::string((char*)&value1, sizeof(value1));
	std::string value_str2 = std::string((char*)&value2, sizeof(value2));
	if(value_str1.compare(value_str2) < 0) {
		return true;
	}else {
		return false;
	}
};

template<class Type>
inline bool operator==(const Type& value1, const Type& value2) {
	std::string value_str1 = std::string((char*)&value1, sizeof(value1));
	std::string value_str2 = std::string((char*)&value2, sizeof(value2));
	if(value_str1.compare(value_str2) == 0) {
		return true;
	}else {
		return false;
	}
};

template <class T>
struct ValueLess : std::binary_function <T,T,bool> {
  bool operator() (const T& x, const T& y) const
    {return x<y;}
};

}

using namespace template_function_for_default_sort;

template <class SortType, class ValueType>
class MemSort {
public:

MemSort(uint32_t toplimit = UINT_MAX):top_limit(toplimit) {
};

struct SortContent{
	SortType key;
	ValueType value;
};

typedef SortContent Type;
typedef std::vector<SortContent> SortListType;
typedef std::map<ValueType, uint32_t, ValueLess<ValueType> > SortMapType;


void init_by_values(const std::map<ValueType, SortType>& value_map) {
	std::multimap<SortType, ValueType> tmp_map;
	typename std::map<ValueType, SortType>::const_iterator itr = value_map.begin();
	for(; itr!=value_map.end(); itr++) {
		tmp_map.insert(std::pair<SortType, ValueType>(itr->second, itr->first));
	};
	init(tmp_map);
};

void init(const std::multimap<SortType, ValueType>& value_map) {
	sort_list.clear();
	sort_map.clear();
	uint32_t count = 0;
	if( value_map.size()) {
		typename std::multimap<SortType, ValueType>::const_reverse_iterator itr = value_map.rbegin();
		for(;itr!=value_map.rend() && count < top_limit ;itr++) {
			Type content;
			content.key = itr->first;
			content.value = itr->second;
			sort_list.push_back(content);
			sort_map[content.value] = sort_list.size()-1; 
			count ++;
		}
	}
}

void merge(MemSort<SortType,  ValueType>& new_sort) {
	SortListType sort_list_temp;
	typename SortListType::iterator itr_old = sort_list.begin();
	typename SortListType::iterator itr_new = new_sort.sort_list.begin();
	uint32_t index = 0;
	while (itr_old!=sort_list.end() && itr_new!=new_sort.sort_list.end())
	{
		if(itr_new->key > itr_old->key) {
			sort_list_temp.push_back(*itr_new);
			sort_map[itr_new->value] = index;
			itr_new ++;
			index ++ ;
		}else {
			if (new_sort.Exist(itr_old->value)) {
				itr_old ++;
				continue;	
			} else {
				sort_list_temp.push_back(*itr_old);
				sort_map[itr_old->value] = index;
				itr_old ++;
				index++;
			}
		}
	}
	while ( ++itr_old !=sort_list.end()) {
		sort_list_temp.push_back(*itr_old);
		sort_map[itr_old->value] = index;
		index ++;
	}
	while ( ++itr_new !=new_sort.sort_list.end() ) {
		sort_list_temp.push_back(*itr_new);
		index ++ ;
	}
	sort_list = sort_list_temp;
}

uint32_t size() {
	return sort_list.size();
}

void clear() {
	sort_list.clear();
	sort_map.clear();
}

uint32_t index(ValueType& value) {
	if(sort_map.find(value) == sort_map.end() ) {
		return 0;
	}
	else {
		return sort_map[value]+1;
	}
}

bool exist(ValueType& value) {
	if(sort_map.find(value) == sort_map.end()) {
		return false;
	}
	return true;
}

SortType get_sort(ValueType& value) {
	if(sort_map.find(value)!=sort_map.end()) {
		return sort_list[sort_map[value]].key;
	}
	return SortType();
}

SortType index_to_sort(uint32_t index) {
	if(index > sort_list.size()) {
		return SortType();
	} else {
		return sort_list[index-1].key;
	}
}

ValueType index_to_value(uint32_t index) {
	if(index > sort_list.size()) {
		return ValueType();
	} else {
		return sort_list[index-1].value;
	}
	
}

std::multimap<SortType, ValueType> range(uint32_t index_start , uint32_t index_end) {
	std::multimap<SortType, ValueType> result;
	if(!index_start || !index_end || index_start > sort_list.size() ) {
		return result;
	}
	index_start--; index_end --;
	for(uint32_t index= index_start; sort_list.size() && index < (uint32_t)sort_list.size() && index <= index_end ; index++) {
		result.insert(std::pair<SortType, ValueType>(sort_list[index].key ,sort_list[index].value));
	}
	return result;
}

std::multimap<SortType, ValueType> rrange(uint32_t index_start , uint32_t index_end) {
	std::multimap<SortType, ValueType> result;
	if(!index_start || !index_end || index_start > sort_list.size() ) {
		return result;
	}
	for(uint32_t index= sort_list.size()-index_start; sort_list.size() && index >= (uint32_t)sort_list.size()-index_end && index >= 0 ; index--) {
		result.insert(std::pair<SortType, ValueType>(sort_list[index].key ,sort_list[index].value));
	}
	return result;
}

private:
void BubbleTop(uint32_t index) {
	assert(index < sort_list.size());
	SortContent content = sort_list[index];
	uint32_t tmp_index = index;
	while(tmp_index){
		if( !(content.key < sort_list[tmp_index-1].key || (content.key == sort_list[tmp_index-1].key && content.value < sort_list[tmp_index-1].value ))) {
			sort_list[tmp_index] = sort_list[tmp_index-1];
			sort_map[sort_list[tmp_index-1].value] = tmp_index;
			tmp_index --;
		}
		else {
			sort_list[tmp_index] = content;
			sort_map[content.value] = tmp_index;
			break;
		}
	}
	if( !tmp_index ) {
		sort_list[tmp_index] = content;
        sort_map[content.value] = tmp_index;
	}
}

void BubbleBottom(uint32_t index) {
	assert(index < sort_list.size());
	SortContent content = sort_list[index];
	uint32_t tmp_index = index;
	while(tmp_index < (sort_list.size()-1) ){
		if( content.key < sort_list[tmp_index+1].key || (content.key == sort_list[tmp_index+1].key && content.value < sort_list[tmp_index+1].value )) {
			sort_list[tmp_index] = sort_list[tmp_index+1];
			sort_map[sort_list[tmp_index+1].value] = tmp_index;
			tmp_index ++;
		}
		else {
			sort_list[tmp_index] = content;
			sort_map[content.value] = tmp_index;
			break;
		}
	}
	if( tmp_index == sort_list.size()-1 ) {
		sort_list[tmp_index] = content;
        sort_map[content.value] = tmp_index;
	}

};

public:

void delete_value(ValueType value) {
	typename SortMapType::iterator itr = sort_map.find(value);
	if(itr!=sort_map.end()) {
		uint32_t index = sort_map[value];
		sort_list[index].key = sort_list[sort_list.size()-1].key;
		BubbleBottom(index);
		sort_list.erase(sort_list.end()-1);
		sort_map.erase(itr);
	}
}

void modify(SortType key, ValueType value) {
	typename SortMapType::iterator itr = sort_map.find(value);
	if(itr == sort_map.end()) {
		Type content;
		content.key = key;
		content.value = value;
		sort_list.push_back(content);
		BubbleTop(sort_list.size()-1);
		if(sort_list.size()> top_limit) {
			sort_map.erase(sort_list[sort_list.size() - 1].value);
			sort_list.erase(sort_list.end()-1);
			}
		}else {
		uint32_t index = sort_map[value];
		sort_list[index].key = key;
		BubbleTop(index);
		if(sort_map[value] == index) {
			BubbleBottom(index);
		}
	}
}

private:
	SortListType	sort_list;
	SortMapType		sort_map;
	uint32_t 		top_limit;
};


}
}
#endif
