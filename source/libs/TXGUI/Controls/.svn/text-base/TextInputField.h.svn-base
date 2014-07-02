#ifndef iSeer_TextInputField_h
#define iSeer_TextInputField_h

#include "cocos2d.h"

USING_NS_CC;

namespace TXGUI
{
	class TextInputField: public CCTextFieldTTF, public CCTextFieldDelegate, public CCTouchDelegate
	{
	private:
		// 点击开始位置
		CCPoint m_beginPos;

		// 光标精灵
		CCSprite *m_pCursorSprite;

		// 光标动画
		CCAction *m_pCursorAction;

		// 光标坐标
		CCPoint m_cursorPos;

		// 输入框内容
		std::string m_strInputText;

		// 是否密码输入
		bool m_bIsPassword;

		// 显示内容
		std::string m_strShowText;

		// 是否已经schedule
		bool m_bIsScheduled;

		// 字数限制
		int m_iLengthLimit;

	protected:
		// CCTextFieldTTF
		virtual const char *getContentText();

	public:
		TextInputField();
		~TextInputField();

		// static
		static TextInputField* textFieldWithPlaceHolder(const char *placeholder, CCSize dimensions, 
			CCTextAlignment alignment, const char *fontName, float fontSize);
		static TextInputField* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);

		// CCTextFieldTTF
		virtual void onEnter();
		virtual void onExit();

		// 初始化光标精灵
		void initCursorSprite(int nHeight);

		// CCTextFieldTTF
		virtual bool attachWithIME();
		virtual bool detachWithIME();

		// CCTextFieldDelegate
		virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
		virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
		virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
		virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);

        virtual void resetInputText(const char *label);
		// CCLayer Touch
		bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

		// 设置是否密码输入
		void setIsPassword(bool value);

		// 将显示字符串转换为密码形式
		void ChangeToPassword(float dt);

		// 设置字数限制
		void setLengthLimit(int value);

		// 得到dimensions
		CCSize getDimensions();

		// 获取输入的内容
		virtual const char *getString();

		// 清空输入的内容
		virtual void clearString();

	private:
		// 判断是否点击在TextField处
		bool isInTextField(CCTouch *pTouch);
		// 得到TextField矩形
		CCRect getRect();
	};
}


#endif
