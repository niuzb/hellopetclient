//
//  EncodeUFloat.h
//  iSeer
//
//  Created by danny on 9/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  @没有重载布尔运算符

#ifndef iSeer_EncodeUFloat_h
#define iSeer_EncodeUFloat_h


struct EncodeUFloat
{
    
public:
    
    EncodeUFloat();
    EncodeUFloat(float orig);
    
    EncodeUFloat  operator= (float orig);
    EncodeUFloat  operator= (int orig);
    EncodeUFloat  operator= (unsigned int orig);
    EncodeUFloat  operator= (double orig);
    EncodeUFloat  operator= (EncodeUFloat value);
    
    float         operator+(float orig);
    float         operator+(int orig);
    float         operator+(unsigned int orig);
    
    friend  float operator+(float orig, EncodeUFloat& value);
    friend  float operator+(int orig, EncodeUFloat& value);
    friend  float operator+(unsigned int orig, EncodeUFloat& value);
    
    float         operator-(float orig);
    float         operator-(int orig);
    float         operator-(unsigned int orig);
    
    friend  float operator-(float orig, EncodeUFloat& value);
    friend  float operator-(int orig, EncodeUFloat& value);
    friend  float operator-(unsigned int orig, EncodeUFloat& value);
    
    void          operator+=(float orig);
    void          operator+=(int orig);
    void          operator+=(unsigned int orig);
    void          operator+=(EncodeUFloat value);
    
    void          operator-=(float orig);
    void          operator-=(int orig);
    void          operator-=(unsigned int orig);
    void          operator-=(EncodeUFloat value);
    
    float         operator*(float orig);
    float         operator*(int orig);
    float         operator*(unsigned int orig);
    
    friend float  operator*(float orig, EncodeUFloat& value);
    friend float  operator*(int orig, EncodeUFloat& value);
    friend float  operator*(unsigned int orig, EncodeUFloat& value);
    
    float         operator/(float orig);
    float         operator/(int orig);
    float         operator/(unsigned int orig);
    
    friend  float operator/(float orig, EncodeUFloat& value);
    friend  float operator/(int orig, EncodeUFloat& value);
    friend  float operator/(unsigned int orig, EncodeUFloat& value);
    
    operator float();
    operator float()const;
    
    operator int();
    operator int()const;
    
    operator unsigned int();
    operator unsigned int()const;
    
        
private:
    
    unsigned char encodeChar(unsigned char orig);
    unsigned char decodeChar(unsigned char orig)const;
    
    void         encode(float orig);
    float        decode()const;
    
private:
    
    float        mData;
    
};
#endif
