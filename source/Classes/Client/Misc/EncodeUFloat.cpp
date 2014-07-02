//
//  EncodeUFloat.cpp
//  iSeer
//
//  Created by danny on 9/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EncodeUFloat.h"

EncodeUFloat::EncodeUFloat()
{
    mData = 0.0;
}
EncodeUFloat::EncodeUFloat(float orig)
{
    encode(orig);
}

EncodeUFloat EncodeUFloat::operator= (float orig)
{
    encode(orig);
    return *this;
}
EncodeUFloat EncodeUFloat::operator= (int orig)
{
    float value = orig;
    encode(value);
    return *this;
}
EncodeUFloat EncodeUFloat::operator= (unsigned int orig)
{
    float value = orig;
    encode(value);
    return *this;
}
EncodeUFloat EncodeUFloat::operator= (double orig)
{
    float value = orig;
    encode(value);
    return *this;
}
EncodeUFloat EncodeUFloat::operator= (EncodeUFloat value)
{
    mData = value.mData;
    return *this;
}
float EncodeUFloat::operator+(float orig)
{
    float value = decode();
    return orig + value;
}
float EncodeUFloat::operator+(int orig)
{
    float value = decode();
    return orig + value;
}
float EncodeUFloat::operator+(unsigned int orig)
{
    float value = decode();
    return orig + value;
}
float operator+(float orig, EncodeUFloat&value)
{
    return orig + value.decode();
}
float operator+(int orig, EncodeUFloat&value)
{
    return orig + value.decode();
}
float operator+(unsigned int orig, EncodeUFloat&value)
{
    return orig + value.decode();
}
float EncodeUFloat::operator-(float orig)
{
    float value = decode();
    return value - orig;
}
float EncodeUFloat::operator-(int orig)
{
    float value = decode();
    return value - orig;
}
float EncodeUFloat::operator-(unsigned int orig)
{
    float value = decode();
    return value - orig;
}
float operator-(float orig, EncodeUFloat& value)
{
    return  (orig - value.decode());
}
float operator-(int orig, EncodeUFloat& value)
{
    return  (orig - value.decode());
}
float operator-(unsigned int orig, EncodeUFloat& value)
{
    return  (orig - value.decode());
}
void EncodeUFloat::operator+=(float orig)
{
    float value = decode();
    value += orig;
    encode(value);
}

void EncodeUFloat::operator+=(int orig)
{
    float value = decode();
    value += orig;
    encode(value);
}
void EncodeUFloat::operator+=(unsigned int orig)
{
    float value = decode();
    value += orig;
    encode(value);
}
void EncodeUFloat::operator+=(EncodeUFloat value)
{
    float a = decode();
    float b = value.decode();
    encode(a + b);
}

void EncodeUFloat::operator-=(float orig)
{
    float value = decode();
    value -= orig;
    encode(value);
}
void EncodeUFloat::operator-=(int orig)
{
    float value = decode();
    value -= orig;
    encode(value);
}
void EncodeUFloat::operator-=(unsigned int orig)
{
    float value = decode();
    value -= orig;
    encode(value);
}
void EncodeUFloat::operator-=(EncodeUFloat value)
{
    float a = decode();
    float b = value.decode();
    encode(a -b);
}
float EncodeUFloat::operator*(float orig)
{
    float value = decode();
    return  value * orig;
}
float EncodeUFloat::operator*(int orig)
{
    float value = decode();
    return  value * orig;
}
float EncodeUFloat::operator*(unsigned int orig)
{
    float value = decode();
    return  value * orig;
}
float  operator*(float orig, EncodeUFloat& value)
{
    return orig * value.decode();
}
float  operator*(int orig, EncodeUFloat& value)
{
    return orig * value.decode();
}
float  operator*(unsigned int orig, EncodeUFloat& value)
{
    return orig * value.decode();
}
float EncodeUFloat::operator/(float orig)
{
    float value = decode();
    return  value / orig;
}
float EncodeUFloat::operator/(int orig)
{
    float value = decode();
    return  value / orig;
}
float EncodeUFloat::operator/(unsigned int orig)
{
    float value = decode();
    return  value / orig;
}
float operator/(float orig, EncodeUFloat& value)
{
    return orig / value.decode();
}
float operator/(int orig, EncodeUFloat& value)
{
    return orig / value.decode();
}
float operator/(unsigned int orig, EncodeUFloat& value)
{
    return orig / value.decode();
}
EncodeUFloat::operator float()
{
    return decode();
}
EncodeUFloat::operator float()const
{
    return decode();
}

EncodeUFloat::operator int()
{
    return (int)decode();
}
EncodeUFloat::operator int()const
{
    return (int)decode();
}

EncodeUFloat::operator unsigned int()
{
    return (unsigned int)decode();
}
EncodeUFloat::operator unsigned int()const
{
    return (unsigned int)decode();
}
unsigned char EncodeUFloat::encodeChar(unsigned char orig)
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


unsigned char EncodeUFloat::decodeChar(unsigned char orig)const
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



void EncodeUFloat::encode(float orig)
{
    unsigned int *ptr = (unsigned int *)(&orig);    /*float 类型不支持位运算，通过整形指针操作float的位*/
    unsigned char part1 = (*ptr & 0x000000ff) >> 0;
    unsigned char part2 = (*ptr & 0x0000ff00) >> 8;
    unsigned char part3 = (*ptr & 0x00ff0000) >> 16;
    unsigned char part4 = (*ptr & 0xff000000) >> 24;
    
    part1 = encodeChar(part1);
    part2 = encodeChar(part2);
    part3 = encodeChar(part3);
    part4 = encodeChar(part4);    
    
    //change order from 4,3,2,1 to 3,4,1,2
    unsigned int *mDataPtr = (unsigned int *)(&mData);
    *mDataPtr = (part3<< 24) | (part4 << 16) | (part1 << 8) | (part2 << 0);   
}


float EncodeUFloat::decode()const
{
    unsigned int *ptr = (unsigned int *)(&mData);
    unsigned char part1 = (*ptr & 0x000000ff) >> 0;
    unsigned char part2 = (*ptr & 0x0000ff00) >> 8;
    unsigned char part3 = (*ptr & 0x00ff0000) >> 16;
    unsigned char part4 = (*ptr & 0xff000000) >> 24;
    
    part1 = decodeChar(part1);
    part2 = decodeChar(part2);
    part3 = decodeChar(part3);
    part4 = decodeChar(part4);   
    
    float tmp;
    unsigned int *tmpPtr = (unsigned int *)(&tmp);
    *tmpPtr =  (part3 << 24) | (part4 << 16) | (part1 << 8) | (part2 << 0);
    return tmp;
}