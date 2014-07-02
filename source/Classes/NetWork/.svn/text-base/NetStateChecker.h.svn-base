#pragma once

class NetStateChecker : public CCObject
{
public:	
	~NetStateChecker();
	static NetStateChecker* getInstance(void);
	static void Destroy();

	long GetTimeWithLua();

	/// start say hello
	void Start();

	/// stop say hello
	void Stop();
    
    
    void QuickSendRqsToServer();
	void SendRqsToServer();
    void stopQuickCheck();
    
    
	void RecieveRqsFromServer();
	long GetDeltaTime(){
		return mDeltaTime;
	}


protected:
	/// hello package
	void  update(float dt);
    void quick_udpate(float dt);

private:
	NetStateChecker();
    void checkNetWork();
    
	bool bStartTesting;
	long int mTimeInMs;
	long int mDeltaTime;

	bool bSendContent;

	float m_fLifeHelloTime;
};