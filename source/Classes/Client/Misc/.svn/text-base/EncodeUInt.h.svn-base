//
//  EncodeUInt.h
//  iSeer
//
//  Created by chao li on 7/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iSeer_EncodeUInt_h
#define iSeer_EncodeUInt_h

struct EncodeUInt
{
        
public:
    
    EncodeUInt();
    EncodeUInt(unsigned int orig);
    
    EncodeUInt operator= (unsigned int orig);
    EncodeUInt operator= (int orig);
    EncodeUInt operator= (unsigned long orig);
    EncodeUInt operator= (EncodeUInt value);
    EncodeUInt operator= (float value);
    
    unsigned int operator+(unsigned int orig);
    unsigned int operator+(int orig);
    float operator+(float value);
    int operator+(EncodeUInt value);
    
    friend unsigned int operator+(unsigned int orig, EncodeUInt& value);
    friend unsigned int operator+(int orig, EncodeUInt& value);
    friend float operator+(float orig, EncodeUInt &value);
    friend int operator+(EncodeUInt& orig, EncodeUInt& value2);
    
    
    unsigned int operator-(unsigned int orig);
    unsigned int operator-(int orig);
    float operator-(float orig);
    int operator-(EncodeUInt orig);
    
    friend unsigned int operator-(unsigned int orig, EncodeUInt& value);
    friend unsigned int operator-(int orig, EncodeUInt& value);
    friend float operator-(float orig, EncodeUInt& value);
    friend int operator-(EncodeUInt& orig, EncodeUInt& value);
    
    void        operator+=(unsigned int orig);
    void        operator+=(int orig);
    void        operator+=(EncodeUInt value);
    
    void        operator-=(unsigned int orig);
    void        operator-=(int orig);
    void        operator-=(EncodeUInt value);
    
    bool        operator<(unsigned int orig);
    bool        operator<(int orig);
    bool        operator<(float orig);
    bool        operator<(double orig);
    bool        operator<(EncodeUInt orig);
    
    bool        operator<=(unsigned int orig);
    bool        operator<=(int orig);
    bool        operator<=(float orig);
    bool        operator<=(double orig);
    bool        operator<=(EncodeUInt orig);
    
    bool        operator>(unsigned int orig);
    bool        operator>(int orig);
    bool        operator>(float orig);
    bool        operator>(double orig);
    bool        operator>(EncodeUInt value);
    
    friend bool operator>(unsigned int orig, EncodeUInt& value);
    friend bool operator>(int orig, EncodeUInt& value);
    friend bool operator>(float orig, EncodeUInt& value);
    friend bool operator>(double orig, EncodeUInt& value);
    
    bool        operator>=(unsigned int orig);
    bool        operator>=(int orig);
    bool        operator>=(float orig);
    bool        operator>=(double orig);
    bool        operator>=(EncodeUInt value);
    
    bool        operator==(unsigned int orig);
    bool        operator==(int orig);
    bool        operator==(unsigned int orig)const;
    bool        operator==(int orig)const;
    bool        operator==(EncodeUInt orig)const;
    bool        operator==(EncodeUInt orig);
    
    bool        operator!=(unsigned int orig);
    bool        operator!=(unsigned int orig) const;
    bool        operator!=(int orig);
    bool        operator!=(int orig) const;
    bool        operator!=(EncodeUInt orig);
    bool        operator!=(EncodeUInt orig) const;
    
    friend bool operator==(unsigned int orig, EncodeUInt& value);
    friend bool operator==(int orig, EncodeUInt& value);
    friend bool operator==(int orig, const EncodeUInt& value);
    
    unsigned int operator*(unsigned int orig);
    unsigned int operator*(int orig);
    
    friend unsigned int operator*(unsigned int orig, EncodeUInt& value);
    friend unsigned int operator*(int orig, EncodeUInt& value);
    
    unsigned int operator/(unsigned int orig);
    unsigned int operator/(int orig);
    
    friend unsigned int operator/(unsigned int orig, EncodeUInt& value);
    friend unsigned int operator/(int orig, EncodeUInt& value);
    
    int operator++(int);
    int operator--(int);
    
    operator unsigned int();
    operator unsigned int()const;
    operator int();
    operator int()const;
    operator unsigned short();
    operator unsigned short() const;
    operator float();
    operator float() const;
    
private:
    
    unsigned char encodeChar(unsigned char orig);
    unsigned char decodeChar(unsigned char orig)const;
    
    void         encode(unsigned int orig);
    unsigned int decode()const;
    
private:
    
    unsigned int        mData;
    
};


#endif
