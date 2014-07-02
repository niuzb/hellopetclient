//
//  EncodeUInt.cpp
//  iSeer
//
//  Created by chao li on 7/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EncodeUInt.h"


EncodeUInt::EncodeUInt()
{
    mData = 0;  
}

EncodeUInt::EncodeUInt(unsigned int orig)
{
    encode(orig);    
}


EncodeUInt EncodeUInt::operator=(unsigned int orig)
{
    encode(orig);
    return *this;
}

EncodeUInt EncodeUInt::operator=(int orig)
{
    encode(orig);
    return *this;
}

EncodeUInt EncodeUInt::operator=(unsigned long orig)
{
    encode((unsigned int)orig);
    return *this;
}

EncodeUInt EncodeUInt::operator=(float orig)
{
    encode((unsigned int)orig);
    return *this;
}


EncodeUInt EncodeUInt::operator=(EncodeUInt value)
{
    mData = value.mData;
    return *this;
}


unsigned int EncodeUInt::operator+(unsigned int orig)
{
    unsigned int value = decode();    
    return value + orig;    
}

unsigned int EncodeUInt::operator+(int orig)
{
    unsigned int value = decode();    
    return value + orig;
}

float EncodeUInt::operator+(float orig)
{
    unsigned int value = decode();
    return value + orig;
}

int EncodeUInt::operator+(EncodeUInt value)
{
    unsigned int left = decode();
    unsigned int right = value.decode();
    return left + right;
}

unsigned int operator+(unsigned int orig, EncodeUInt& value)
{
    return orig + value.decode();
}

unsigned int operator+(int orig, EncodeUInt& value)
{
    return orig + value.decode();
}

float operator+(float orig, EncodeUInt& value)
{
    return orig + value.decode();
}

int operator+(EncodeUInt& orig, EncodeUInt& value)
{
    unsigned int left = orig.decode();
    unsigned int right = value.decode();
    return left + right;
}


unsigned int EncodeUInt::operator-(unsigned int orig)
{
    unsigned int value = decode();    
    return value - orig;    
}

unsigned int EncodeUInt::operator-(int orig)
{
    unsigned int value = decode();    
    return value - orig;
}

float EncodeUInt::operator-(float value)
{
    unsigned int v = decode();
    return v - value;
}

int EncodeUInt::operator-(EncodeUInt orig)
{
    unsigned int value = decode();
    return value - orig;
}

unsigned int operator-(unsigned int orig, EncodeUInt& value)
{
    return orig - value.decode();
}

unsigned int operator-(int orig, EncodeUInt& value)
{
    return orig - value.decode();
}

float operator-(float orig, EncodeUInt& value)
{
    return orig - value.decode();
}

int operator-(EncodeUInt& left, EncodeUInt& right)
{
    return left.decode() - right.decode();
}

void EncodeUInt::operator+=(unsigned int orig)
{
    unsigned int value = decode();
    value += orig;
    encode(value);   
}

void EncodeUInt::operator+=(int orig)
{
    unsigned int value = decode();
    value += orig;
    encode(value);   
}

void EncodeUInt::operator+=(EncodeUInt value)
{
    unsigned int a = value.decode();
    unsigned int b = this->decode();
    encode(a + b);
}

void EncodeUInt::operator-=(unsigned int orig)
{
    unsigned int value = decode();
    value -= orig;    
    encode(value);     
}

void EncodeUInt::operator-=(int orig)
{
    unsigned int value = decode();
    value -= orig;    
    encode(value);    
}

void EncodeUInt::operator-=(EncodeUInt value)
{
    unsigned int a = value.decode();
    unsigned int b = this->decode();    
    encode(b - a);
}

bool EncodeUInt::operator<(unsigned int orig)
{
    unsigned int value = decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator<(int orig)
{
    unsigned int value = decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator<(float orig)
{
    unsigned int value = decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}


bool EncodeUInt::operator<(double orig)
{
    unsigned int value = decode();
    if (value < orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator<(EncodeUInt orig)
{
    unsigned int value = decode();
    unsigned int _orig = orig.decode();
    return (value<_orig);
}


bool EncodeUInt::operator<=(unsigned int orig)
{
    unsigned int value = decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator<=(int orig)
{
    unsigned int value = decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator<=(float orig)
{
    unsigned int value = decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator<=(double orig)
{
    unsigned int value = decode();
    if (value <= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator<=(EncodeUInt orig)
{
    unsigned int value = decode();
    unsigned int _orig = orig.decode();
    return (value <= _orig);
}


bool EncodeUInt::operator>(unsigned int orig)
{
    unsigned int value = decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator>(int orig)
{
    unsigned int value = decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator>(float orig)
{
    unsigned int value = decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator>(double orig)
{
    unsigned int value = decode();
    if (value > orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator>(EncodeUInt value)
{
    unsigned int left = this->decode();
    unsigned int right = value.decode();
    
    return left > right;
}

bool operator>(unsigned int orig, EncodeUInt& value)
{
    return orig > value.decode();
}

bool operator>(int orig, EncodeUInt& value)
{
    return orig > value.decode();
}

bool operator>(float orig, EncodeUInt& value)
{
    return orig > value.decode();
}

bool operator>(double orig, EncodeUInt& value)
{
    return orig > value.decode();
}


bool EncodeUInt::operator>=(unsigned int orig)
{
    unsigned int value = decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator>=(int orig)
{
    unsigned int value = decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator>=(float orig)
{
    unsigned int value = decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator>=(double orig)
{
    unsigned int value = decode();
    if (value >= orig)
    {
        return true;
    }
    
    return false;
}

bool EncodeUInt::operator>=(EncodeUInt value)
{
    unsigned int left = this->decode();
    unsigned int right = value.decode();
    
    return left >= right;
}

unsigned int EncodeUInt::operator*(unsigned int orig)
{
    unsigned int value = decode();
    return value * orig;
}

unsigned int EncodeUInt::operator*(int orig)
{
    unsigned int value = decode();
    return value * orig;
}

unsigned int operator*(unsigned int orig, EncodeUInt& value)
{
    return orig * value.decode();
}

unsigned int operator*(int orig, EncodeUInt& value)
{
    return orig * value.decode();
}

unsigned int EncodeUInt::operator/(unsigned int orig)
{
    unsigned int value = decode();
    return value / orig;
}

unsigned int EncodeUInt::operator/(int orig)
{
    unsigned int value = decode();
    return value / orig;
}

unsigned int operator/(unsigned int orig, EncodeUInt& value)
{
    return orig / value.decode();
}

unsigned int operator/(int orig, EncodeUInt& value)
{
    return orig / value.decode();
}

int EncodeUInt::operator++(int)
{
    unsigned int value = this->decode();
    encode(value+1);
    return (value+1);
}

int EncodeUInt::operator--(int)
{
    unsigned int value = this->decode();
    encode(value-1);
    return  value - 1;
}


bool EncodeUInt::operator==(unsigned int orig)
{
    unsigned int value = decode();
    return value == orig;
}

bool EncodeUInt::operator==(int orig)
{
    unsigned int value = decode();
    return value == orig;
}

bool EncodeUInt::operator==(unsigned int orig)const
{
    unsigned int value = decode();
    return value == orig;
}

bool EncodeUInt::operator==(int orig)const
{
    unsigned int value = decode();
    return value == orig;
}

bool EncodeUInt::operator==(EncodeUInt orig) const
{
    unsigned int value = decode();
    unsigned int _orig = orig.decode();
    return value == _orig;
}

bool EncodeUInt::operator==(EncodeUInt orig)
{
    unsigned int value = decode();
    unsigned int _orig = orig.decode();
    return value == _orig;
}

bool EncodeUInt::operator!=(unsigned int orig)
{
    return !(*this == orig);
}

bool EncodeUInt::operator!=(unsigned int orig) const
{
    return !(*this == orig);
}

bool EncodeUInt::operator!=(int orig)
{
    return !(*this == orig);
}

bool EncodeUInt::operator!=(int orig) const
{
    return !(*this == orig);
}

bool EncodeUInt::operator!=(EncodeUInt orig)
{
    return !(*this == orig);
}

bool EncodeUInt::operator!=(EncodeUInt orig) const
{
    return !(*this == orig);
}

bool operator==(unsigned int orig, EncodeUInt& value)
{
    return orig == value.decode();    
}
bool operator==(int orig, EncodeUInt& value)
{
    return orig == value.decode();
}
bool operator==(int orig, const EncodeUInt& value)
{
    return orig == value.decode();
}



EncodeUInt::operator unsigned int()
{
    return decode();
}

EncodeUInt::operator int()
{
    return decode();
}

EncodeUInt::operator unsigned int()const
{
    return decode();
}

EncodeUInt::operator int()const
{
    return decode();
}

EncodeUInt::operator unsigned short()
{
    return decode();
}

EncodeUInt::operator unsigned short() const
{
    return decode();
}

EncodeUInt::operator float()
{
    return decode();
}

EncodeUInt::operator float() const
{
    return decode();
}

unsigned char EncodeUInt::encodeChar(unsigned char orig)
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


unsigned char EncodeUInt::decodeChar(unsigned char orig)const
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



void EncodeUInt::encode(unsigned int orig)
{
    unsigned char part1 = (orig & 0x000000ff) >> 0;
    unsigned char part2 = (orig & 0x0000ff00) >> 8;
    unsigned char part3 = (orig & 0x00ff0000) >> 16;
    unsigned char part4 = (orig & 0xff000000) >> 24;
    
    part1 = encodeChar(part1);
    part2 = encodeChar(part2);
    part3 = encodeChar(part3);
    part4 = encodeChar(part4);    
    
    //change order from 4,3,2,1 to 3,4,1,2
    mData = (part3<< 24) | (part4 << 16) | (part1 << 8) | (part2 << 0);   
}


unsigned int EncodeUInt::decode()const
{
    unsigned char part1 = (mData & 0x000000ff) >> 0;
    unsigned char part2 = (mData & 0x0000ff00) >> 8;
    unsigned char part3 = (mData & 0x00ff0000) >> 16;
    unsigned char part4 = (mData & 0xff000000) >> 24;
    
    part1 = decodeChar(part1);
    part2 = decodeChar(part2);
    part3 = decodeChar(part3);
    part4 = decodeChar(part4);   
    
    
    return (part3 << 24) | (part4 << 16) | (part1 << 8) | (part2 << 0);
}



