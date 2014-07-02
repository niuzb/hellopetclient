#ifndef MSGBLOCK_HPP_
#define MSGBLOCK_HPP_

#include <string.h>
#include <vector>
#include <set>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <exception>

#include <libtaomee++/inet/pdumanip.hpp>

namespace base {

#define DEFAULT_DATA_SIZE (1024)

class ExtractException: public std::exception {
public:
	ExtractException(uint32_t request_size, uint32_t remain_size):
	 request_(request_size), remain_(remain_size) {
	}
	uint32_t request_;
	uint32_t remain_;
};

template <bool LENDIAN = true>
class MsgBlock
{
public:
	MsgBlock():
		LE(LENDIAN), buffer(NULL), capacity(DEFAULT_DATA_SIZE), package_size(0), read_pos(0) {
		buffer = (char*) malloc(DEFAULT_DATA_SIZE);
		assert(buffer!=NULL);
		memset(buffer, 0 , DEFAULT_DATA_SIZE);
	}

	MsgBlock(const void* msg, size_t length):
	LE(LENDIAN), read_pos(0) {
		buffer = (char*) malloc(length);
		assert(buffer!=NULL);
		memcpy(buffer, msg, length);
		capacity = length;
		package_size = length;
	}

	~MsgBlock() {
        if (buffer != NULL) {
            free(buffer);
            buffer = NULL;
        }
    }

	virtual char * data() {
		return buffer;
	}

	virtual size_t size() {
		return package_size;
	}

	char* get_remain_data() {
		return buffer + read_pos;
	}
	
	size_t get_remain_size() {
		return package_size - read_pos;
	}
		
	void BigEndian() {
		LE = false;
	}
	
	void LittleEndian() {
		LE = true;
	}

	MsgBlock &operator <<(uint64_t value) {
		if(LE) {
			expand_le(value);
		} else {
			expand_be(value);
		}
		return *this;
	}

	MsgBlock &operator <<(uint32_t value) {
		if(LE) {
			expand_le(value);
		} else {
			expand_be(value);
		}
		return *this;
	}

	MsgBlock &operator <<(uint16_t value) {
		if(LE) {
			expand_le(value);
		} else {
			expand_be(value);
		}
		return *this;
	}

	MsgBlock &operator <<(uint8_t value) {
		if(LE) {
			expand_le(value);
		} else {
			expand_be(value);
		}
		return *this;
	}

	MsgBlock &operator <<(char value) {
		if(LE) {
			expand_le(value);
		} else {
			expand_be(value);
		}
		return *this;
	}

	MsgBlock &operator <<(int value) {
		if(LE) {
			expand_le(value);
		} else {
			expand_be(value);
		}
		return *this;
	}

	MsgBlock &operator <<(std::string value) {
		uint32_t len = value.length();
		*this << len;
		expand(value.c_str(), len);
		return *this;
	}

	MsgBlock &operator >>(uint32_t &value) {
		if(LE) {
			extract_le(value);
		} else {
			extract_be(value);
		}
		return *this;
	}

	MsgBlock &operator >>(uint16_t &value) {
		if(LE) {
			extract_le(value);
		} else {
			extract_be(value);
		}
		return *this;
	}

	MsgBlock &operator >>(uint8_t &value) {
		if(LE) {
			extract_le(value);
		} else {
			extract_be(value);
		}
		return *this;
	}

	MsgBlock &operator >>(uint64_t &value) {
		if(LE) {
			extract_le(value);
		} else {
			extract_be(value);
		}
		return *this;
	}

	MsgBlock &operator >>(char &value) {
		if(LE) {
			extract_le(value);
		} else {
			extract_be(value);
		}
		return *this;
	}

	MsgBlock &operator >>(int &value) {
		if(LE) {
			extract_le(value);
		} else {
			extract_be(value);
		}
		return *this;
	}

	MsgBlock &operator >>(std::string &value) {
		uint32_t len;
		*this >> len;
		if (read_pos+len > package_size) {
            throw ExtractException(len, package_size-read_pos);
        }
		value.assign(buffer+read_pos, len);	
        read_pos += len;
		return *this;
	}
	
	MsgBlock &append(std::string& value) {
		expand(value.c_str(), value.length());
		return *this;
	}

private:
	template <class T>
	void expand_le (T value) {
		size_t size = sizeof(value);
		if(capacity < package_size + size) {
			size_t increase =  DEFAULT_DATA_SIZE *( size / DEFAULT_DATA_SIZE + 1);
			buffer = (char*) realloc(buffer, capacity + increase );
			capacity +=increase;
		}
		*(reinterpret_cast<T*>(buffer + package_size)) = value;	
		package_size += size;
		expand_size(size);
	}

	template <class T>
	void expand_be (T value) {
		size_t size = sizeof(value);
		if(capacity < package_size + size) {
			size_t increase =  DEFAULT_DATA_SIZE *( size / DEFAULT_DATA_SIZE + 1);
			buffer = (char*) realloc(buffer, capacity + increase );
			capacity +=increase;
		}
		*(reinterpret_cast<T*>(buffer + package_size)) = taomee::bswap(value);	
		package_size += size;
	}

	void expand(const char* data, size_t size) {
		if(capacity < package_size + size) {
			size_t increase =  DEFAULT_DATA_SIZE *( size / DEFAULT_DATA_SIZE + 1);
			buffer = (char*) realloc(buffer, capacity + increase );
			capacity +=increase;
		}
		memcpy(buffer+package_size, data, size);
		package_size += size;
		expand_size(size);
	}

	virtual void expand_size(size_t size) {

	}

	template <class T>
	void extract_le(T& value) {
		if (read_pos+sizeof(T) > package_size) {
			throw ExtractException(sizeof(T), package_size-read_pos);
		}
		value = *(reinterpret_cast<const T*>(buffer + read_pos));
		read_pos += sizeof(T);
	}
	
	template <class T>
	void extract_be(T& value) {
		if (read_pos+sizeof(T) > package_size) {
			throw ExtractException(sizeof(T), package_size-read_pos);
		}
		value = taomee::bswap(*(reinterpret_cast<const T*>(buffer + read_pos)));
		read_pos += sizeof(T);
	}

	void extract(char* data, size_t size) {
		if (read_pos+size > package_size) {
			throw ExtractException(size, package_size-read_pos);
		}
		assert(read_pos+size <= package_size);
		memcpy(data, buffer+read_pos, size);
		read_pos += size;
	}

private:
	bool LE;		

protected:
	char* buffer;
	size_t capacity;
	size_t package_size;
	size_t read_pos;
};

#pragma pack(1)
struct serv_proto_head {
    /*! package length */
    uint32_t    len;
    /*! sequence number ((p->fd << 16) | p->waitcmd) */
    uint32_t    seq;
    /*! command id */
    uint16_t    cmd;
    /*! errno */
    uint32_t    ret;
    /*! user id */
    uint32_t id;
    /*! package body */
};
#pragma pack()

class ServBlock: public MsgBlock<> {
public:
	ServBlock() :
		MsgBlock<>() {
		package_size += sizeof(head_);
		((serv_proto_head *)buffer)->len = package_size;	
		read_pos = package_size;
		((serv_proto_head *)buffer)->seq = 1;
	}
	ServBlock(const void* msg, size_t length) :
		MsgBlock<>(msg, length) {
		(*this) >> head_.len;
		(*this) >> head_.seq;
		(*this) >> head_.cmd;
		(*this) >> head_.ret;
		(*this) >> head_.id;	
	}
	ServBlock(uint32_t cmd, uint32_t uid, uint32_t seq, uint32_t ret):
		MsgBlock<>() {
		head_.len = 0;
		head_.seq = seq;
		head_.cmd = cmd;
		head_.ret = ret;
		head_.id  = uid;
		(*this) << head_.len << head_.seq << head_.cmd << head_.ret << head_.id;
	}

	void fix_capacity() {
		uint32_t len = get_len();
		if(capacity < len) {
			buffer = (char*) realloc(buffer, len);
			capacity = len;
		}
		package_size = len;
	}

	void expand_size(size_t size) {
		((serv_proto_head *)buffer)->len +=size;
	}
	uint32_t get_len() {
		return *((uint32_t *)buffer);
	}
	uint32_t get_cmd() {
		return head_.cmd;
	}
	uint64_t get_id() {
		return head_.id;
	}
	uint32_t get_seq() {
		return ((serv_proto_head *)buffer)->seq;
	}

	void set_cmd(uint32_t cmd) {
		((serv_proto_head *)buffer)->cmd = cmd;
	}

	void set_ret(uint32_t ret) {
		((serv_proto_head *)buffer)->ret = ret;
	}

	void set_id(uint32_t id) {
		((serv_proto_head *)buffer)->id = id;
	}
	
	void compress () {
		memmove(buffer+sizeof(head_), buffer+read_pos, package_size-read_pos);		
		package_size -= read_pos;
		package_size += sizeof(head_);
		read_pos = sizeof(head_);
		((serv_proto_head *)buffer)->len = package_size;
		head_.len = package_size;
	}

	bool empty() {
		return (read_pos == package_size);
	}

	void set_empty() {
		read_pos = package_size;
	}

private:
	serv_proto_head head_;
};


}

#endif
