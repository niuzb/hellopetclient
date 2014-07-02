#pragma  once
#include "Singleton_t.h"
#include "cocos2d.h"
#include "SceneLayer.h"


USING_NS_CC;

class SpriteSeer;
class ILogicManager;

class GameManager : public TSingleton<GameManager>
{
public :
	GameManager();
	virtual ~GameManager();

	void SetLogicManager(ILogicManager *pILogicMgr);

	SceneLayer* GetSceneLayer();

	SpriteSeer *getHero();

	void setHero(SpriteSeer* hero);

	int getHeroTypeId();
	void setHeroTypeId(int typeId);

	void processTouchBegan(CCPoint touchPoint);

	void changeMap(int mapId, KMapFromType fromMapType);

	CCScene* goToSplash();
	/*
	* @prototype: goToFrontend()
	* @note:
	*     bring the game to the front of the screen. prepare the resources and init all the game components.
	* @param: void
	* @return: void
	*/
	void goToFrontend();

    /*
	* @prototype: startGame()
	* @note:
	*     start the game now, bring the player to the hometown.
	* @param: void
	* @return: void
	*/
	void startGame();

	void exitGame();

protected:
	SceneLayer* m_sceneLayer;
	ILogicManager* m_pLogicMgr;
	SpriteSeer* m_pSpriteSeer;
	int m_spriteSeerTypeId;
};