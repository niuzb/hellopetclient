#ifndef JOINTMANAGER_HPP_
#define JOINTMANAGER_HPP_

#include <string>
#include "Singleton.hpp"
#include "Manager.hpp"

namespace base{

class Generator {
public:
	template<typename ValueType>
	Generator& operator & (ValueType value);

	void to_string(std::string& str);

	void from_string(std::string& str);

private:
	bool input;
};

class Joint: public Object<std::string> {
public:
	template <typename KeyType>
	Joint(KeyType key, std::string name);

	~Joint();

	virtual void serialization();

	void sync();

protected:

	std::string key;

	Generator gen;

	bool host;
};

template <typename KeyType>
Joint::Joint(KeyType key, std::string name): object() {
	GJoint.add_obj(this);
};

std::string Joint::generate_full_name() {

};

class JointManager: public Manager<Joint> {
public:
	void connect();

	void on_message();

	int get_package_len();

	void send_message();
private:
};

}

#define GJoint base::JointManager::get_singleton();

#endif
