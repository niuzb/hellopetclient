#ifndef LUATABLEADAPT_HPP_
#define LUATABLEADAPT_HPP_
#include <cstring> 
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

extern "C" 
{
	 #include "lua.h"
	 #include "lauxlib.h"
	 #include "lualib.h"
}

namespace base {

class LuatableAdapt {
public:
	LuatableAdapt(std::string file_name, std::string table_name);

	LuatableAdapt(LuatableAdapt& parent, std::string key);
	
	LuatableAdapt(LuatableAdapt& parent, uint32_t key);
	
	~LuatableAdapt();

	bool available();

	std::string name();

	template<typename ValueType >
	void get(std::string attr_name, ValueType& value);

private:
	lua_State* m_state;

	std::string m_table_name;

	int m_index;	
};

LuatableAdapt::LuatableAdapt(std::string file_name, std::string table_name) :
	m_state(NULL),
	m_table_name(table_name),
	m_index(0)
{
	m_state = luaL_newstate();
	if(luaL_dofile(m_state, file_name.c_str()) !=0) {
		lua_close(m_state);
		m_state = NULL;
		return ;
	}
	lua_getglobal(m_state, table_name.c_str());
	m_index = lua_gettop(m_state);
}
	
LuatableAdapt::LuatableAdapt(LuatableAdapt& parent, std::string key) :
	m_state(parent.m_state),
	m_table_name(key),
	m_index(0)
{
	lua_pushstring(m_state, m_table_name.c_str());
	lua_gettable(m_state, parent.m_index);
	if(!lua_istable(m_state, -1)) {
		m_state = NULL;
		m_index = 0;
	} else {
		m_index = lua_gettop(m_state);
	}
}
	
LuatableAdapt::LuatableAdapt(LuatableAdapt& parent, uint32_t key) :
	m_state(parent.m_state),
	m_index(0)
{
	m_table_name = key,
	lua_pushnumber(m_state, key);
	lua_gettable(m_state, parent.m_index);
	if(!lua_istable(m_state, -1)) {
		m_state = NULL;
		m_index = 0;
	} else {
		m_index = lua_gettop(m_state);
	}
}
	
LuatableAdapt::~LuatableAdapt() {
	if(m_state && m_index) {
		lua_remove(m_state, m_index);	
		if(!lua_gettop(m_state))
			lua_close(m_state);
	}
}
	
bool LuatableAdapt::available() {
	return m_state != NULL;
}

std::string LuatableAdapt::name() {
	return m_table_name;
}
	
template<typename ValueType >
void LuatableAdapt::get(std::string attr_name, ValueType& value) {
	lua_pushstring(m_state, attr_name.c_str());
	lua_gettable(m_state, m_index);
	if (lua_isstring(m_state, -1)) {
        std::string value_str = lua_tostring(m_state, -1);	
		std::istringstream iss(value_str.c_str());
        iss >> value;
	}
	lua_pop(m_state, 1);
}

}

#endif
