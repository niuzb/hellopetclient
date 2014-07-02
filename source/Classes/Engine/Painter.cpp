//
//  Painter.cpp
//  iSeer
//
//  Created by wuwei on 2/13/12.
//  Copyright 2012 Taomee.Inc. All rights reserved.
//

#include "Painter.h"
#include "CrossUtil.h"
using namespace cocos2d;

#define NUM_SEGMENTS    36                  // number of segments to make up the circle perimeter
#define FILL_COLOR      1.0f,0.0f,1.0f,0.2f // filling color
#define EDGE_COLOR      1.0f,0.0f,1.0f,0.8f // edge color

void Painter::drawCircle(CCPoint c, float r)
{
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
    // delta radian of each segment
    float dR = float( 2 * M_PI / NUM_SEGMENTS);
    
    // initialize the vertex array
    // number of vertices: 1 center + (NUM_SEGMENT + 1) endpoints
    int numVerts = 1 + (NUM_SEGMENTS + 1);
    float* pVerts = new float[numVerts * 2];
    memset(pVerts, 0, numVerts * 2);
    
    // insert the vertices
    // center and the first endpoint
    pVerts[0] = c.x;
    pVerts[1] = c.y;
    pVerts[2] = c.x + r;
    pVerts[3] = c.y;
    
    // endpoints on the perimeter
    for(int i = 0; i < NUM_SEGMENTS; ++i)
    {
        float radian    = dR * (i+1);
        pVerts[4+i*2]   = c.x + r * cosf(radian);
        pVerts[4+i*2+1] = c.y + r * sinf(radian);
    }
    
    glDisable(GL_TEXTURE_2D);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
    
    // set blend mode
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // fill circle
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, pVerts);
    ccDrawColor4F(1.0f,0.0f,1.0f,0.2f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numVerts);
    
    // highlight edges
    ccDrawColor4F(1.0f,0.0f,1.0f,0.8f);
    glDrawArrays(GL_LINE_STRIP, 1, numVerts - 1);
    
    // restore default state
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
    
    delete[] pVerts;
}

void Painter::drawFan(CCPoint c, float r, float a1, float a2)
{
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
    // delta radian of each segment
    float dR = float(2 * M_PI / NUM_SEGMENTS);
    float radian1 = a1 * M_PI / 180;
    float radian2 = a2 * M_PI / 180;
    
    // number of segments to make up the fan arc
    int numSegments = ceilf((radian2 - radian1) / dR);
    
    // initialize the vertex array
    // number of vertices: 1 center + (numSegments + 1) endpoints + 1 close point
    int numVerts = 1 + (numSegments + 1) + 1;
    float* pVerts = new float[numVerts * 2];
    memset(pVerts, 0, numVerts * 2);
    
    // insert the vertices
    // center and the first endpoint
    pVerts[0] = c.x;
    pVerts[1] = c.y;
    pVerts[2] = c.x + r * cosf(radian1);
    pVerts[3] = c.y + r * sinf(radian1);
    
    for(int i = 0; i < numSegments; ++i)
    {
        float radian    = (i == numSegments - 1) ? radian2 : radian1 + dR * (i+1);
        pVerts[4+i*2]   = c.x + r * cosf(radian);
        pVerts[4+i*2+1] = c.y + r * sinf(radian);
    }
    
    // reinsert the center as the close point, used to draw the close edge
    pVerts[numVerts*2-2] = c.x;
    pVerts[numVerts*2-1] = c.y;
    
    glDisable(GL_TEXTURE_2D);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
    
    // set blend mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	// fill the fan
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, pVerts);
	ccDrawColor4F(1.0f,0.0f,1.0f,0.2f);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numVerts - 1);

	// highlight the edge
	ccDrawColor4F(1.0f,0.0f,1.0f,0.8f);
	glDrawArrays(GL_LINE_STRIP, 0, numVerts);
    
    // restore default state
	//glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
    
    delete[] pVerts;
}

void Painter::drawHintBkg(CCPoint leftTop, float width, float height, ccColor3B color)
{
	// a hint background looks like following:
	// 1---3---5
	// |       | 
	// 2---4---6
	// the middle is opaque and the sides are semi-transparent

    float deviceScale = CC_CONTENT_SCALE_FACTOR();
    
//	if(IsRetinaDisplay())
//	{
//		leftTop  = ccpMult(leftTop, 2.f);   //ccp(leftTop.x * 2, leftTop.y * 2);
//		width   *= 2;
//		height  *= 2;
//	}
    
    leftTop = ccpMult(leftTop, deviceScale);
    width *= deviceScale;
    height *= deviceScale;

	// screen center
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//CCPoint c = ccp(winSize.width * 0.5f, winSize.height * 0.5f);
	float halfW = width * 0.5f;
	//float halfH = height * 0.5f;

	// initialize vertices
	const int numVerts = 6;
	//    float* pVerts = new float[numVerts << 1];
	float pVerts[numVerts << 1];
	memset(pVerts, 0, sizeof(float) * (numVerts << 1));

	pVerts[0] = leftTop.x;          //c.x - halfW;
	pVerts[1] = leftTop.y;          //c.y + halfH;
	pVerts[2] = leftTop.x;          //c.x - halfW;
	pVerts[3] = leftTop.y - height; //c.y - halfH;
	pVerts[4] = leftTop.x + halfW;  //c.x;
	pVerts[5] = leftTop.y;          //c.y + halfH;
	pVerts[6] = leftTop.x + halfW;  //c.x;
	pVerts[7] = leftTop.y - height; //c.y - halfH;
	pVerts[8] = leftTop.x + width;  //c.x + halfW;
	pVerts[9] = leftTop.y;          //c.y + halfH;
	pVerts[10] = leftTop.x + width; //c.x + halfW;
	pVerts[11] = leftTop.y - height;    //c.y - halfH;

	// initialize colors
	//    unsigned char* pColors = new unsigned char[numVerts << 2];
	unsigned char pColors[numVerts << 2];
	memset(pColors, 0, sizeof(unsigned char) * (numVerts << 2));

	pColors[0] = pColors[4] = pColors[8] = pColors[12] = pColors[16] = pColors[20] = color.r;
	pColors[1] = pColors[5] = pColors[9] = pColors[13] = pColors[17] = pColors[21] = color.g;
	pColors[2] = pColors[6] = pColors[10] = pColors[14] = pColors[18] = pColors[22] = color.b;
	pColors[3] = pColors[7] = pColors[19] = pColors[23] = 0;
	pColors[11] = pColors[15] = 128;

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
	//glDisable(GL_TEXTURE_2D);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	int oldSrc, oldDst;
	glGetIntegerv(GL_BLEND_SRC_ALPHA, &oldSrc);
	glGetIntegerv(GL_BLEND_DST_ALPHA, &oldDst);


	// set blend mode
	ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// fill the background
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, pVerts);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, pColors);

	// restore blend func
	//glBlendFunc(oldSrc, oldDst);

	// restore default state
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnable(GL_TEXTURE_2D);

	//    delete[] pVerts;    pVerts = NULL;
	//    delete[] pColors;   pColors = NULL;

	return;
}

void Painter::drawNameBkg(CCPoint center, float width, float height, ccColor3B color)
{
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
	// a background looks like following:
	// 1---3---5
	// |       | 
	// 2---4---6
	// the middle is opaque and the left & right sides are semi-transparent
	// two real lines at the top & bottom sides

	// draw the background firstly
	CCPoint leftTop = ccp(center.x - width * 0.5f, center.y + height * 0.5f);
	drawHintBkg(leftTop, width, height, color);

////this will cause display error on UI	
//    float deviceScale = CC_CONTENT_SCALE_FACTOR();
//    
//	// convert for retina
////	if(IsRetinaDisplay())
////	{
////		center  = ccpMult(center, 2.f);     // ccp(center.x * 2, center.y * 2);
////		leftTop = ccpMult(leftTop, 2.f);    // ccp(leftTop.x * 2, leftTop.y * 2);
////		width   *= 2;
////		height  *= 2;
////	}
//    
//    center = ccpMult(center, deviceScale);
//    leftTop = ccpMult(leftTop, deviceScale);
//    width *= deviceScale;
//    height *= deviceScale;
//
//	// draw 2 real lines, devided into 4 lines:
//	// 1-3, 3-5, 2-4, 4-6
//
//	// initialize vertices
//	const int numVerts = 8;
//	//    float* pVerts = new float[numVerts<<1];
//	float pVerts[numVerts<<1];
//	memset(pVerts, 0, sizeof(float)*(numVerts<<1));
//
//	pVerts[0] = leftTop.x;
//	pVerts[1] = leftTop.y;
//	pVerts[2] = center.x;
//	pVerts[3] = leftTop.y;
//	pVerts[4] = center.x;
//	pVerts[5] = leftTop.y;
//	pVerts[6] = leftTop.x + width;
//	pVerts[7] = leftTop.y;
//
//	pVerts[8] = leftTop.x;
//	pVerts[9] = leftTop.y - height;
//	pVerts[10] = center.x;
//	pVerts[11] = leftTop.y - height;
//	pVerts[12] = center.x;
//	pVerts[13] = leftTop.y - height;
//	pVerts[14] = leftTop.x + width;
//	pVerts[15] = leftTop.y - height;
//
//	// initialize colors
//	//    unsigned char* pColors = new unsigned char[numVerts << 2];
//	unsigned char pColors[numVerts << 2];
//	memset(pColors, 0, sizeof(unsigned char) * (numVerts << 2));
//
//	pColors[0] = pColors[4] = pColors[8] = pColors[12] = pColors[16] = pColors[20] = pColors[24] = pColors[28] = color.r;
//	pColors[1] = pColors[5] = pColors[9] = pColors[13] = pColors[17] = pColors[21] = pColors[25] = pColors[29] = color.g;
//	pColors[2] = pColors[6] = pColors[10] = pColors[14] = pColors[18] = pColors[22] = pColors[26] = pColors[30] = color.b;
//	pColors[3] = pColors[15] = pColors[19] = pColors[31] = 0;
//	pColors[7] = pColors[11] = pColors[23] = pColors[27] = 128;//255;//128;
//
//	glDisable(GL_TEXTURE_2D);
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//
//	int oldSrc, oldDst;
//	glGetIntegerv(GL_BLEND_SRC, &oldSrc);
//	glGetIntegerv(GL_BLEND_DST, &oldDst);
//
//	// set blend mode
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glLineWidth(1.0f);
//
//	// fill the background
//	glVertexPointer(2, GL_FLOAT, 0, pVerts);
//	glColorPointer(4, GL_UNSIGNED_BYTE, 0, pColors);
//	glDrawArrays(GL_LINES, 0, numVerts);
//
//	// restore blend func
//	glBlendFunc(oldSrc, oldDst);
//
//	// restore default state
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//	glEnable(GL_TEXTURE_2D);
//
//	//    delete[] pVerts;    pVerts = NULL;
//	//    delete[] pColors;   pColors = NULL;

	return;
}

void Painter::drawRect(CCRect rect,GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	int width = rect.size.width;
	int height = rect.size.height;
	         
	if (width == 0 || height == 0)
	{
		return ;
	}
	CCPoint upLeftPoint(rect.origin.x,rect.origin.y + height);
	CCPoint downRightPoint(rect.origin.x + width,rect.origin.y);
	{
		ccDrawColor4B(r, g, b, a);
	}
	glLineWidth( 2.0f );			
	ccDrawRect(upLeftPoint,downRightPoint);
	return ;
}