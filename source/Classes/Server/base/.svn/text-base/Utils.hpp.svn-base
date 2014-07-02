/*
 * =====================================================================================
 *
 *       Filename:  Utils.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/02/2013 07:29:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Plus Wu (), plus.wu1986@gmail.com
 *        Company:  Taomee
 *
 * =====================================================================================
 */
#pragma once

namespace base {
/************************************************************************/
/*函数*/
/************************************************************************/
// 切割字符(以单个符号为间断)like: 1,2,3 or 1;2;3 or aa/b/cc ... [8/7/2010 kevin]
template <typename T>
void g_cat_string(std::vector<T>& dst_result,std::string& src_str,char tag){
	std::stringstream ss(src_str);        
	std::string sub_str;        
	while(std::getline(ss,sub_str,tag)){
		//以tag为间隔分割str的内容 
		T i;
		g_convertFromString(i,sub_str);
		dst_result.push_back(i);
	}
};

template <typename T> 
void g_convertFromString(T &dst_value, const std::string &src_str){
	std::stringstream ss(src_str);
	ss >> dst_value;
};

template <class T> 
std::string g_convert_to_string(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

template<typename T>
void ReFresh(std::vector<T> & Data)
{
	T a;
	for (uint32_t i = 0; i < Data.size(); i++) {
		a = Data[i];
		int j = rand() %(Data.size() - i) + i;
		Data[i] = Data[j];
		Data[j] = a;
	}
}

}


