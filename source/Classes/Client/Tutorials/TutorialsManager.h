#pragma once

#include "cocos2d.h"
#include "TutorialsDataCenter.h"
#include "TutorialBase.h"

USING_NS_CC;

class TutorialsManager
{
public :
	TutorialsManager();
	~TutorialsManager();

	static TutorialsManager* Get();
	static void Destroy();

	void LoadData();
	/**
	* Instruction : 重置变量
	* @param 
	*/
	void ResetValue();

	/**
	* Instruction : 启动一个教程
	* @param 
	*/
	void StartOneTutorial(unsigned int id);

	/**
	* Instruction : 处理控件事件
	* @param type 0 单击 1 双击
	*/	
	void HandleOneEvent(const char* name,unsigned int type);
protected:
	/**
	* Instruction : 启动一个UI教程
	* @param 
	*/
	void StartOneUiTutorial(unsigned int id);
private:
	static TutorialsManager* mInstance;

	TutorialDataCenter* mDataCenter;
	TutorialBase* mTutorialInstance;	
};