#ifndef TINYXMLADAPT_HPP_
#define TINYXMLADAPT_HPP_
#include "tinystr.h"
#include "tinyxml.h"
#include <string>
#include <map>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "GameResourceManager.h"

namespace base {

class TinyxmlAdapt {
public:
	TinyxmlAdapt(std::string file_name);

	TinyxmlAdapt(TinyxmlAdapt& parent);

	bool available();

	std::string name();

	template<typename ValueType >
	void get(std::string attr_name, ValueType& value);

private:
	void parse();

typedef std::map<std::string , std::string> AttrMap;
	AttrMap m_attributes;

	TiXmlElement * m_node;

	TiXmlElement * m_current_child;
};

TinyxmlAdapt::TinyxmlAdapt(std::string file_name)
{
	std::string path = GameResourceManager::sharedManager()->storedFullPathFromRelativePath(file_name.c_str());


	TiXmlDocument *myDocument = new TiXmlDocument(path.c_str());
	myDocument->LoadFile();
	m_node = myDocument->FirstChildElement();
	m_current_child = NULL;
	parse();
}
	
TinyxmlAdapt::TinyxmlAdapt(TinyxmlAdapt& parent)
{
	m_current_child = NULL;
	m_node = NULL;
	if(parent.available()) {
		if(!parent.m_current_child) {
			m_node = parent.m_node->FirstChildElement();
			parent.m_current_child = m_node;
		} else {
			m_node = parent.m_current_child->NextSiblingElement();
			if(m_node) parent.m_current_child = m_node;	
		}
 	}
	parse();
}
	
bool TinyxmlAdapt::available()
{
	return m_node != NULL;	
}

std::string TinyxmlAdapt::name()
{
	if (m_node)
	{		
		return m_node->Value();
	}

	return "";
}

void TinyxmlAdapt::parse() {
	if(m_node) {
		TiXmlAttribute *attri = m_node->FirstAttribute();
		while(attri!=NULL)
		{
			m_attributes[attri->Name()] = attri->Value();
   			attri=attri->Next();
  		}
	}
}

template<typename ValueType >
void TinyxmlAdapt::get(std::string attr_name, ValueType& value) {
	if(m_attributes.find(attr_name) != m_attributes.end()) {
		std::string str =  m_attributes[attr_name];
		std::istringstream iss(str.c_str());
		iss >> value;
	} else {
		value = ValueType();
	}
}

}
#endif
