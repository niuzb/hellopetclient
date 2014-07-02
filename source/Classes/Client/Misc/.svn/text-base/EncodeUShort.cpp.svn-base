//
//  EncodeUShort.cpp
//  iSeer
//
//  Created by chao li on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EncodeUShort.h"


EncodeUShort::EncodeUShort()
:mData(0)
{
    
}


EncodeUShort::EncodeUShort(unsigned short orig)
{
    encode(orig);
}

EncodeUShort::EncodeUShort(unsigned int orig)
{
    unsigned short value = orig;
    encode(value);
}

EncodeUShort::EncodeUShort(int orig)
{
    short value = orig;
    encode(value);
}


EncodeUShort EncodeUShort::operator=(unsigned short orig)
{
    encode(orig);
    return *this;
}

EncodeUShort EncodeUShort::operator=(short orig)
{
    unsigned short value = orig;
    encode(value);
    return *this;
}

EncodeUShort EncodeUShort::operator=(unsigned int orig)
{
    unsigned short value = orig;
    encode(value);
    return *this;
}

EncodeUShort EncodeUShort::operator=(int orig)
{
    unsigned short value = orig;
    encode(value);
    return *this;
}

EncodeUShort EncodeUShort::operator=(EncodeUShort value)
{
    this->mData = value.mData;
    return *this;
}


unsigned short EncodeUShort::operator+(unsigned short orig)
{
    unsigned short value = decode();
    return value + orig;
}

unsigned short EncodeUShort::operator+(short orig)
{
    unsigned short value = decode();
    return value + orig;
}


unsigned int EncodeUShort::operator+(unsigned int orig)
{
    unsigned short value = decode();
    return value + orig;
}

unsigned int EncodeUShort::operator+(int orig)
{
    unsigned short value = decode();
    return value + orig;
}

unsigned int EncodeUShort::operator+(EncodeUShort value)
{
    unsigned short left = decode();
    unsigned short right = value.decode();
    return left + right;
}

unsigned short EncodeUShort::operator-(unsigned short orig)
{
    unsigned short value = decode();
    return value - orig;
}

unsigned short EncodeUShort::operator-(short orig)
{
    unsigned short value = decode();
    return value - orig;
}


unsigned int EncodeUShort::operator-(unsigned int orig)
{
    unsigned short value = decode();
    return value - orig;
}

unsigned int EncodeUShort::operator-(int orig)
{
    unsigned short value = decode();
    return value - orig;
}

int EncodeUShort::operator-(EncodeUShort value)
{
    short left = this->decode();
    short right = value.decode();
    return left - right;
}


void EncodeUShort::operator+=(unsigned short orig)
{
    unsigned short value = decode();
    unsigned short result = value + orig;
    encode(result);     
}

void EncodeUShort::operator+=(short orig)
{
    unsigned short value = decode();
    unsigned short result = value + orig;
    encode(result);    
}


void EncodeUShort::operator+=(unsigned int orig)
{
    unsigned short value = decode();
    unsigned short result = value + orig;
    encode(result);  
    
}

void EncodeUShort::operator+=(int orig)
{
    unsigned short value = decode();
    unsigned short result = value + orig;
    encode(result);    
}

void EncodeUShort::operator+=(EncodeUShort value)
{
    unsigned short left = this->decode();
    unsigned short right = value.decode();
    encode(left + right);
}


void EncodeUShort::operator-=(unsigned short orig)
{
    unsigned short value = decode();
    unsigned short result = value - orig;
    encode(result);     
}

void EncodeUShort::operator-=(short orig)
{
    unsigned short value = decode();
    unsigned short result = value - orig;
    encode(result);    
}


void EncodeUShort::operator-=(unsigned int orig)
{
    unsigned short value = decode();
    unsigned short result = value - orig;
    encode(result);  
    
}

void EncodeUShort::operator-=(int orig)
{
    unsigned short value = decode();
    unsigned short result = value - orig;
    encode(result);    
}

void EncodeUShort::operator-=(EncodeUShort value)
{
    unsigned short left = this->decode();
    unsigned short right = value.decode();
    encode(left - right);
}

bool EncodeUShort::operator<(unsigned short orig)
{
    unsigned short value = this->decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<(short orig)
{
    unsigned short value = this->decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<(int orig)
{
    unsigned short value = this->decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<(unsigned int orig)
{
    unsigned short value = this->decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<(float orig)
{
    unsigned short value = this->decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<(double orig)
{
    unsigned short value = this->decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}


bool EncodeUShort::operator<(EncodeUShort value)
{
    unsigned short left = this->decode();
    unsigned short right = value.decode();
    
    return left < right;
}


bool EncodeUShort::operator<=(unsigned short orig)
{
    unsigned short value = this->decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<=(short orig)
{
    unsigned short value = this->decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<=(int orig)
{
    unsigned short value = this->decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<=(unsigned int orig)
{
    unsigned short value = this->decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<=(float orig)
{
    unsigned short value = this->decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator<=(double orig)
{
    unsigned short value = this->decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}


bool EncodeUShort::operator<=(EncodeUShort value)
{
    unsigned short left = this->decode();
    unsigned short right = value.decode();
    
    return left <= right;
}



bool EncodeUShort::operator>(unsigned short orig)
{
    unsigned short value = this->decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>(short orig)
{
    unsigned short value = this->decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>(int orig)
{
    unsigned short value = this->decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>(unsigned int orig)
{
    unsigned short value = this->decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>(float orig)
{
    unsigned short value = this->decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>(double orig)
{
    unsigned short value = this->decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>(EncodeUShort value)
{
    unsigned short left = this->decode();
    unsigned short right = value.decode();
    
    return left > right;
}


bool EncodeUShort::operator>=(unsigned short orig)
{
    unsigned short value = this->decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>=(short orig)
{
    unsigned short value = this->decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>=(int orig)
{
    unsigned short value = this->decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>=(unsigned int orig)
{
    unsigned short value = this->decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>=(float orig)
{
    unsigned short value = this->decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>=(double orig)
{
    unsigned short value = this->decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator>=(EncodeUShort value)
{
    unsigned short left = this->decode();
    unsigned short right = value.decode();
    
    return left >= right;
}

bool EncodeUShort::operator==(int orig)
{
    unsigned short value = this->decode();
    if (value == orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator==(unsigned int orig)
{
    unsigned short value = this->decode();
    if (value == orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator==(short orig)
{
    unsigned short value = this->decode();
    if (value == orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator==(unsigned short orig)
{
    unsigned short value = this->decode();
    if (value == orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator==(EncodeUShort value)
{
    return this->mData == value.mData;
}


bool EncodeUShort::operator!=(int orig)
{
    unsigned short value = this->decode();
    if (value != orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator!=(unsigned int orig)
{
    unsigned short value = this->decode();
    if (value != orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator!=(short orig)
{
    unsigned short value = this->decode();
    if (value != orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator!=(unsigned short orig)
{
    unsigned short value = this->decode();
    if (value != orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUShort::operator!=(EncodeUShort value)
{
    return this->mData != value.mData;
}


int EncodeUShort::operator++(int)
{
    unsigned short value = this->decode();
    encode(value + 1);
    return value + 1;
}

int EncodeUShort::operator--(int)
{
    int value = this->decode();
    encode(value - 1);
    return value - 1;
}


EncodeUShort::operator unsigned short()
{
    return decode();
}


EncodeUShort::operator unsigned short()const
{
    return decode();
}

EncodeUShort::operator short()
{
    return decode();
}


EncodeUShort::operator short()const
{
    return decode();
}


EncodeUShort::operator unsigned int()
{
    return decode();
}


EncodeUShort::operator unsigned int()const
{
    return decode();
}

EncodeUShort::operator int()
{
    return decode();
}


EncodeUShort::operator int()const
{
    return decode();
}


EncodeUShort::operator float()
{
    return decode();
}


EncodeUShort::operator float()const
{
    return decode();
}


unsigned char EncodeUShort::encodeChar(unsigned char orig)
{
    unsigned char byte0 = orig & (0x1 << 0);
    unsigned char byte1 = orig & (0x1 << 1);
    unsigned char byte2 = orig & (0x1 << 2);
    unsigned char byte3 = orig & (0x1 << 3);
    unsigned char byte4 = orig & (0x1 << 4);
    unsigned char byte5 = orig & (0x1 << 5);
    unsigned char byte6 = orig & (0x1 << 6);
    unsigned char byte7 = orig & (0x1 << 7);
    
    unsigned char result =  (byte7 >> 1) | (byte6 << 1) | 
    (byte5 >> 1) | (byte4 << 1) |
    (byte3 >> 1) | (byte2 << 1) |
    (byte1 >> 1) | (byte0 << 1);  
    
    
    return result;    
}


unsigned char EncodeUShort::decodeChar(unsigned char orig)const
{
    unsigned char byte0 = orig & (0x1 << 0);
    unsigned char byte1 = orig & (0x1 << 1);
    unsigned char byte2 = orig & (0x1 << 2);
    unsigned char byte3 = orig & (0x1 << 3);
    unsigned char byte4 = orig & (0x1 << 4);
    unsigned char byte5 = orig & (0x1 << 5);
    unsigned char byte6 = orig & (0x1 << 6);
    unsigned char byte7 = orig & (0x1 << 7);
    
    unsigned char result =  (byte7 >> 1) | (byte6 << 1) | 
    (byte5 >> 1) | (byte4 << 1) |
    (byte3 >> 1) | (byte2 << 1) |
    (byte1 >> 1) | (byte0 << 1);   
    
    return result;    
}


void EncodeUShort::encode(unsigned short orig)
{
    unsigned char part1 = (orig & 0x00ff) >> 0;
    unsigned char part2 = (orig & 0xff00) >> 8;   
    
    part1 = encodeChar(part1);
    part2 = encodeChar(part2);
    
    mData = (part1 << 8) | (part2 << 0);
}


unsigned short EncodeUShort::decode()const
{
    unsigned char part1 = (mData & 0x00ff) >> 0;
    unsigned char part2 = (mData & 0xff00) >> 8;   
    
    part1 = decodeChar(part1);
    part2 = decodeChar(part2);
    
    return (part1 << 8) | (part2 << 0);
}









