//
//  main.cpp
//  AES
//
//  Created by razer tong on 11-11-28.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//
#include "StdAfx.h"
#include <iostream>
#include "AES.h"
#include <stdio.h>


using namespace std;



int main (int argc, const char * argv[])
{
	unsigned char key[] = 
	{
		0x2b, 0x7e, 0x15, 0x16, 
		0x28, 0xae, 0xd2, 0xa6, 
		0xab, 0xf7, 0x15, 0x88, 
		0x09, 0xcf, 0x4f, 0x3c
	};
    
	AES aes(key);
    {
       
     
  

        FILE *fd = fopen(argv[1], "rb");
        size_t size =0;
        fseek(fd, 0, SEEK_END);
        size = ftell(fd);
        fseek(fd, 0, SEEK_SET);
        if (size %16!=0) 
        {
            size=size + 16-size %16;
        }
        
        unsigned char* out = new unsigned char[size];
        memset(out, 0, size);
        size_t read = fread(out, 1, size, fd);
        
        

        //printf("%s\n",out);
      
       aes.Cipher((void *)out, size);
        fclose(fd);
     
     
        
        FILE *fd2 = fopen(argv[2], "wb");
        fwrite(out, 1, size, fd2);
        fclose(fd2);
  
     }
    
    return 0;
}

