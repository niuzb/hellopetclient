//
//  EncodeUShort.h
//  iSeer
//
//  Created by chao li on 7/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iSeer_EncodeUShort_h
#define iSeer_EncodeUShort_h


struct EncodeUShort
{
    
public:
    
    EncodeUShort();
    EncodeUShort(unsigned short orig);
    EncodeUShort(unsigned int orig);
    EncodeUShort(int orig);
    
    
    EncodeUShort    operator= (unsigned short orig);
    EncodeUShort    operator= (short orig);
    EncodeUShort    operator= (unsigned int orig);
    EncodeUShort    operator= (int orig);
    EncodeUShort    operator= (EncodeUShort value);
    
    unsigned short  operator+(unsigned short orig);
    unsigned short  operator+(short orig);
    unsigned int    operator+(unsigned int orig);
    unsigned int    operator+(int orig);
    unsigned int    operator+(EncodeUShort value);
    
    unsigned short  operator-(unsigned short orig);
    unsigned short  operator-(short orig);
    unsigned int    operator-(unsigned int orig);
    unsigned int    operator-(int orig);
    int             operator-(EncodeUShort value);
    
    void        operator+=(unsigned short orig);
    void        operator+=(short orig);
    void        operator+=(unsigned int orig);
    void        operator+=(int orig);
    void        operator+=(EncodeUShort value);
    
    void        operator-=(unsigned short orig);
    void        operator-=(short orig);
    void        operator-=(unsigned int orig);
    void        operator-=(int orig);
    void        operator-=(EncodeUShort value);
    
    bool        operator<(unsigned short orig);
    bool        operator<(short orig);
    bool        operator<(int orig);
    bool        operator<(unsigned int orig);
    bool        operator<(float orig);
    bool        operator<(double orig);
    bool        operator<(EncodeUShort value);
    
    bool        operator<=(unsigned short orig);
    bool        operator<=(short orig);
    bool        operator<=(int orig);
    bool        operator<=(unsigned int orig);
    bool        operator<=(float orig);
    bool        operator<=(double orig);
    bool        operator<=(EncodeUShort value);
    
    bool        operator>(unsigned short orig);
    bool        operator>(short orig);
    bool        operator>(int orig);
    bool        operator>(unsigned int orig);
    bool        operator>(float orig);
    bool        operator>(double orig);
    bool        operator>(EncodeUShort value);
    
    bool        operator>=(unsigned short orig);
    bool        operator>=(short orig);
    bool        operator>=(int orig);
    bool        operator>=(unsigned int orig);
    bool        operator>=(float orig);
    bool        operator>=(double orig);
    bool        operator>=(EncodeUShort value);
    
    bool        operator==(unsigned int orig);
    bool        operator==(unsigned short orig);
    bool        operator==(int orig);
    bool        operator==(short orig);
    bool        operator==(EncodeUShort value);
    
    bool        operator!=(unsigned int orig);
    bool        operator!=(unsigned short orig);
    bool        operator!=(int orig);
    bool        operator!=(short orig);
    bool        operator!=(EncodeUShort value);
    
    int         operator--(int);
    int         operator++(int);
    
    
    operator unsigned short();
    operator unsigned short()const;
    operator short();
    operator short()const;
    
    operator unsigned int();
    operator unsigned int()const;
    operator int();
    operator int()const;
    
    operator float();   
    operator float()const;   
    
private:
    
    unsigned char encodeChar(unsigned char orig);
    unsigned char decodeChar(unsigned char orig)const;
    
    void           encode(unsigned short orig);
    unsigned short decode()const;   
    
private:
    
    unsigned short        mData;
    
};




#endif
