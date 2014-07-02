/*
** Lua binding: LuaClient
** Generated automatically by tolua++-1.0.92 on 06/19/13 10:41:44.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_LuaClient_open (lua_State* tolua_S);

#include "LuaCocos2d.h"
#include "LuaClient.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ElfExploreManger (lua_State* tolua_S)
{
 ElfExploreManger* self = (ElfExploreManger*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_SpriteElfDataCenter (lua_State* tolua_S)
{
 SpriteElfDataCenter* self = (SpriteElfDataCenter*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_USERINFO (lua_State* tolua_S)
{
 USERINFO* self = (USERINFO*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ccColor3B (lua_State* tolua_S)
{
 ccColor3B* self = (ccColor3B*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
#ifndef Mtolua_typeid
#define Mtolua_typeid(L,TI,T)
#endif
 tolua_usertype(tolua_S,"CCPoint");
 Mtolua_typeid(tolua_S,typeid(CCPoint), "CCPoint");
 tolua_usertype(tolua_S,"SPRITEINFO");
 Mtolua_typeid(tolua_S,typeid(SPRITEINFO), "SPRITEINFO");
 tolua_usertype(tolua_S,"BackPackItem");
 Mtolua_typeid(tolua_S,typeid(BackPackItem), "BackPackItem");
 tolua_usertype(tolua_S,"ITEMATTR");
 Mtolua_typeid(tolua_S,typeid(ITEMATTR), "ITEMATTR");
 tolua_usertype(tolua_S,"TutorialsManager");
 Mtolua_typeid(tolua_S,typeid(TutorialsManager), "TutorialsManager");
 tolua_usertype(tolua_S,"PvAIManager");
 Mtolua_typeid(tolua_S,typeid(PvAIManager), "PvAIManager");
 tolua_usertype(tolua_S,"GemStonesFromLua");
 Mtolua_typeid(tolua_S,typeid(GemStonesFromLua), "GemStonesFromLua");
 tolua_usertype(tolua_S,"TimeManager");
 Mtolua_typeid(tolua_S,typeid(TimeManager), "TimeManager");
 tolua_usertype(tolua_S,"EquipmentItem");
 Mtolua_typeid(tolua_S,typeid(EquipmentItem), "EquipmentItem");
 tolua_usertype(tolua_S,"ElfExploreManger");
 Mtolua_typeid(tolua_S,typeid(ElfExploreManger), "ElfExploreManger");
 tolua_usertype(tolua_S,"ItemBase");
 Mtolua_typeid(tolua_S,typeid(ItemBase), "ItemBase");
 tolua_usertype(tolua_S,"NotificationCenter");
 Mtolua_typeid(tolua_S,typeid(NotificationCenter), "NotificationCenter");
 tolua_usertype(tolua_S,"ccColor3B");
 Mtolua_typeid(tolua_S,typeid(ccColor3B), "ccColor3B");
 tolua_usertype(tolua_S,"CCNode");
 Mtolua_typeid(tolua_S,typeid(CCNode), "CCNode");
 tolua_usertype(tolua_S,"KMapFromType");
 Mtolua_typeid(tolua_S,typeid(KMapFromType), "KMapFromType");
 tolua_usertype(tolua_S,"ItemManager");
 Mtolua_typeid(tolua_S,typeid(ItemManager), "ItemManager");
 tolua_usertype(tolua_S,"SkillUIManager");
 Mtolua_typeid(tolua_S,typeid(SkillUIManager), "SkillUIManager");
 tolua_usertype(tolua_S,"EQUIPINFO");
 Mtolua_typeid(tolua_S,typeid(EQUIPINFO), "EQUIPINFO");
 tolua_usertype(tolua_S,"MainMenuLayer");
 Mtolua_typeid(tolua_S,typeid(MainMenuLayer), "MainMenuLayer");
 tolua_usertype(tolua_S,"UserData");
 Mtolua_typeid(tolua_S,typeid(UserData), "UserData");
 tolua_usertype(tolua_S,"ParticleManagerX");
 Mtolua_typeid(tolua_S,typeid(ParticleManagerX), "ParticleManagerX");
 tolua_usertype(tolua_S,"GameAudioManager");
 Mtolua_typeid(tolua_S,typeid(GameAudioManager), "GameAudioManager");
 tolua_usertype(tolua_S,"SceneLayer");
 Mtolua_typeid(tolua_S,typeid(SceneLayer), "SceneLayer");
 tolua_usertype(tolua_S,"LevelManager");
 Mtolua_typeid(tolua_S,typeid(LevelManager), "LevelManager");
 tolua_usertype(tolua_S,"GameManager");
 Mtolua_typeid(tolua_S,typeid(GameManager), "GameManager");
 tolua_usertype(tolua_S,"CCScene");
 Mtolua_typeid(tolua_S,typeid(CCScene), "CCScene");
 tolua_usertype(tolua_S,"USERINFO");
 Mtolua_typeid(tolua_S,typeid(USERINFO), "USERINFO");
 tolua_usertype(tolua_S,"CCSprite");
 Mtolua_typeid(tolua_S,typeid(CCSprite), "CCSprite");
 tolua_usertype(tolua_S,"LUA_FUNCTION");
 Mtolua_typeid(tolua_S,typeid(LUA_FUNCTION), "LUA_FUNCTION");
 tolua_usertype(tolua_S,"SpriteElfDataCenter");
 Mtolua_typeid(tolua_S,typeid(SpriteElfDataCenter), "SpriteElfDataCenter");
 tolua_usertype(tolua_S,"SpriteSeer");
 Mtolua_typeid(tolua_S,typeid(SpriteSeer), "SpriteSeer");
 tolua_usertype(tolua_S,"SpriteFactory");
 Mtolua_typeid(tolua_S,typeid(SpriteFactory), "SpriteFactory");
}

/* method: PrintLog of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_PrintLog00
static int tolua_LuaClient_SpriteFactory_PrintLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintLog'", NULL);
#endif
  {
   self->PrintLog();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedFactory of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_sharedFactory00
static int tolua_LuaClient_SpriteFactory_sharedFactory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SpriteFactory* tolua_ret = (SpriteFactory*)  SpriteFactory::sharedFactory();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SpriteFactory");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedFactory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetValue of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_GetValue00
static int tolua_LuaClient_SpriteFactory_GetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetValue'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowElfOnLayerAtPoint of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_ShowElfOnLayerAtPoint00
static int tolua_LuaClient_SpriteFactory_ShowElfOnLayerAtPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
  CCPoint pos = *((CCPoint*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowElfOnLayerAtPoint'", NULL);
#endif
  {
   self->ShowElfOnLayerAtPoint(parentNode,type,pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowElfOnLayerAtPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveElfFromHero of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_RemoveElfFromHero00
static int tolua_LuaClient_SpriteFactory_RemoveElfFromHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
  unsigned int roleId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveElfFromHero'", NULL);
#endif
  {
   self->RemoveElfFromHero(roleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveElfFromHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AttachElfToOneHero of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_AttachElfToOneHero00
static int tolua_LuaClient_SpriteFactory_AttachElfToOneHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
  unsigned int elfTypeId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int heroId = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AttachElfToOneHero'", NULL);
#endif
  {
   self->AttachElfToOneHero(elfTypeId,heroId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AttachElfToOneHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMainMenuLayerNode of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_GetMainMenuLayerNode00
static int tolua_LuaClient_SpriteFactory_GetMainMenuLayerNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMainMenuLayerNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->GetMainMenuLayerNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMainMenuLayerNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetValue of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_ResetValue00
static int tolua_LuaClient_SpriteFactory_ResetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetValue'", NULL);
#endif
  {
   self->ResetValue();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowElfPanelWithBackPackLayer of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_ShowElfPanelWithBackPackLayer00
static int tolua_LuaClient_SpriteFactory_ShowElfPanelWithBackPackLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowElfPanelWithBackPackLayer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ShowElfPanelWithBackPackLayer();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowElfPanelWithBackPackLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendElfAwakeMessage of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_SendElfAwakeMessage00
static int tolua_LuaClient_SpriteFactory_SendElfAwakeMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
  unsigned int awakeType = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendElfAwakeMessage'", NULL);
#endif
  {
   self->SendElfAwakeMessage(awakeType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendElfAwakeMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendAwakeConfigMessage of class  SpriteFactory */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteFactory_SendAwakeConfigMessage00
static int tolua_LuaClient_SpriteFactory_SendAwakeConfigMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteFactory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteFactory* self = (SpriteFactory*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendAwakeConfigMessage'", NULL);
#endif
  {
   self->SendAwakeConfigMessage();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendAwakeConfigMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_new00
static int tolua_LuaClient_SpriteElfDataCenter_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SpriteElfDataCenter* tolua_ret = (SpriteElfDataCenter*)  Mtolua_new((SpriteElfDataCenter)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SpriteElfDataCenter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_new00_local
static int tolua_LuaClient_SpriteElfDataCenter_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SpriteElfDataCenter* tolua_ret = (SpriteElfDataCenter*)  Mtolua_new((SpriteElfDataCenter)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SpriteElfDataCenter");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_delete00
static int tolua_LuaClient_SpriteElfDataCenter_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteElfDataCenter* self = (SpriteElfDataCenter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_Get00
static int tolua_LuaClient_SpriteElfDataCenter_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SpriteElfDataCenter* tolua_ret = (SpriteElfDataCenter*)  SpriteElfDataCenter::Get();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SpriteElfDataCenter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_Destroy00
static int tolua_LuaClient_SpriteElfDataCenter_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SpriteElfDataCenter::Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipOneElf of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_EquipOneElf00
static int tolua_LuaClient_SpriteElfDataCenter_EquipOneElf00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteElfDataCenter* self = (SpriteElfDataCenter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int elfId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipOneElf'", NULL);
#endif
  {
   self->EquipOneElf(elfId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipOneElf'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendGetElfListMessage of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_SendGetElfListMessage00
static int tolua_LuaClient_SpriteElfDataCenter_SendGetElfListMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteElfDataCenter* self = (SpriteElfDataCenter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int roleId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendGetElfListMessage'", NULL);
#endif
  {
   self->SendGetElfListMessage(roleId,name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendGetElfListMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendSetElfStateMessage of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_SendSetElfStateMessage00
static int tolua_LuaClient_SpriteElfDataCenter_SendSetElfStateMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteElfDataCenter* self = (SpriteElfDataCenter*)  tolua_tousertype(tolua_S,1,0);
  unsigned int elfId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int state = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendSetElfStateMessage'", NULL);
#endif
  {
   self->SendSetElfStateMessage(elfId,state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendSetElfStateMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeroUserId of class  SpriteElfDataCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SpriteElfDataCenter_GetHeroUserId00
static int tolua_LuaClient_SpriteElfDataCenter_GetHeroUserId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteElfDataCenter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteElfDataCenter* self = (SpriteElfDataCenter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeroUserId'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->GetHeroUserId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeroUserId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sShareInstance of class  LevelManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_LevelManager_sShareInstance00
static int tolua_LuaClient_LevelManager_sShareInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LevelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LevelManager* tolua_ret = (LevelManager*)  LevelManager::sShareInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LevelManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sShareInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCurrentPPVELevel of class  LevelManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_LevelManager_isCurrentPPVELevel00
static int tolua_LuaClient_LevelManager_isCurrentPPVELevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LevelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LevelManager* self = (LevelManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCurrentPPVELevel'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCurrentPPVELevel();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCurrentPPVELevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCurrentPVELevel of class  LevelManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_LevelManager_isCurrentPVELevel00
static int tolua_LuaClient_LevelManager_isCurrentPVELevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LevelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LevelManager* self = (LevelManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCurrentPVELevel'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCurrentPVELevel();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCurrentPVELevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCurrentPVPLevel of class  LevelManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_LevelManager_isCurrentPVPLevel00
static int tolua_LuaClient_LevelManager_isCurrentPVPLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LevelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LevelManager* self = (LevelManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCurrentPVPLevel'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCurrentPVPLevel();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCurrentPVPLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_LuaClient_USERINFO_new00
static int tolua_LuaClient_USERINFO_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"USERINFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   USERINFO* tolua_ret = (USERINFO*)  Mtolua_new((USERINFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"USERINFO");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_LuaClient_USERINFO_new00_local
static int tolua_LuaClient_USERINFO_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"USERINFO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   USERINFO* tolua_ret = (USERINFO*)  Mtolua_new((USERINFO)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"USERINFO");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: id of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_id
static int tolua_get_USERINFO_unsigned_id(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: id of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_id
static int tolua_set_USERINFO_unsigned_id(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->id = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: userSession of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_userSession
static int tolua_get_USERINFO_userSession(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'userSession'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->userSession);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: userSession of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_userSession
static int tolua_set_USERINFO_userSession(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'userSession'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->userSession,(const char*)tolua_tostring(tolua_S,2,0),SESSION_LENGTH-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: szName of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_szName
static int tolua_get_USERINFO_szName(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->szName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: szName of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_szName
static int tolua_set_USERINFO_szName(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'szName'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->szName,(const char*)tolua_tostring(tolua_S,2,0),16-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ip of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_ip
static int tolua_get_USERINFO_ip(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ip'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->ip);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ip of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_ip
static int tolua_set_USERINFO_ip(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ip'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->ip,(const char*)tolua_tostring(tolua_S,2,0),30-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lastServerName of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_lastServerName
static int tolua_get_USERINFO_lastServerName(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lastServerName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->lastServerName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lastServerName of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_lastServerName
static int tolua_set_USERINFO_lastServerName(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lastServerName'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->lastServerName,(const char*)tolua_tostring(tolua_S,2,0),30-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: port of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_port
static int tolua_get_USERINFO_unsigned_port(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: port of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_port
static int tolua_set_USERINFO_unsigned_port(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->port = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: createdTime of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_createdTime
static int tolua_get_USERINFO_createdTime(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'createdTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->createdTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: createdTime of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_createdTime
static int tolua_set_USERINFO_createdTime(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'createdTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->createdTime = ((long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tokenId of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_tokenId
static int tolua_get_USERINFO_unsigned_tokenId(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tokenId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tokenId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tokenId of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_tokenId
static int tolua_set_USERINFO_unsigned_tokenId(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tokenId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tokenId = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_level
static int tolua_get_USERINFO_unsigned_level(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_level
static int tolua_set_USERINFO_unsigned_level(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: exp of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_exp
static int tolua_get_USERINFO_unsigned_exp(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->exp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: exp of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_exp
static int tolua_set_USERINFO_unsigned_exp(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exp = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mapId of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_mapId
static int tolua_get_USERINFO_unsigned_mapId(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mapId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mapId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mapId of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_mapId
static int tolua_set_USERINFO_unsigned_mapId(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mapId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mapId = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: xPos of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_xPos
static int tolua_get_USERINFO_unsigned_xPos(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'xPos'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->xPos);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: xPos of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_xPos
static int tolua_set_USERINFO_unsigned_xPos(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'xPos'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->xPos = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: yPos of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_yPos
static int tolua_get_USERINFO_unsigned_yPos(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'yPos'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->yPos);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: yPos of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_yPos
static int tolua_set_USERINFO_unsigned_yPos(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'yPos'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->yPos = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: orient of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_orient
static int tolua_get_USERINFO_unsigned_orient(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'orient'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->orient);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: orient of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_orient
static int tolua_set_USERINFO_unsigned_orient(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'orient'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->orient = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_type
static int tolua_get_USERINFO_unsigned_type(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_type
static int tolua_set_USERINFO_unsigned_type(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: battleId of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_battleId
static int tolua_get_USERINFO_unsigned_battleId(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'battleId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->battleId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: battleId of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_battleId
static int tolua_set_USERINFO_unsigned_battleId(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'battleId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->battleId = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: battleSide of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_battleSide
static int tolua_get_USERINFO_unsigned_battleSide(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'battleSide'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->battleSide);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: battleSide of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_battleSide
static int tolua_set_USERINFO_unsigned_battleSide(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'battleSide'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->battleSide = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_spriteEnergy of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_spriteEnergy
static int tolua_get_USERINFO_unsigned_m_spriteEnergy(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_spriteEnergy'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_spriteEnergy);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_spriteEnergy of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_spriteEnergy
static int tolua_set_USERINFO_unsigned_m_spriteEnergy(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_spriteEnergy'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_spriteEnergy = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_gold of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_gold
static int tolua_get_USERINFO_unsigned_m_gold(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_gold'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_gold);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_gold of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_gold
static int tolua_set_USERINFO_unsigned_m_gold(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_gold'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_gold = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_diamond of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_diamond
static int tolua_get_USERINFO_unsigned_m_diamond(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_diamond'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_diamond);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_diamond of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_diamond
static int tolua_set_USERINFO_unsigned_m_diamond(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_diamond'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_diamond = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_spriteChip of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_spriteChip
static int tolua_get_USERINFO_unsigned_m_spriteChip(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_spriteChip'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_spriteChip);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_spriteChip of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_spriteChip
static int tolua_set_USERINFO_unsigned_m_spriteChip(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_spriteChip'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_spriteChip = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_alchemyBagUnlockPos of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_alchemyBagUnlockPos
static int tolua_get_USERINFO_unsigned_m_alchemyBagUnlockPos(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_alchemyBagUnlockPos'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_alchemyBagUnlockPos);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_alchemyBagUnlockPos of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_alchemyBagUnlockPos
static int tolua_set_USERINFO_unsigned_m_alchemyBagUnlockPos(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_alchemyBagUnlockPos'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_alchemyBagUnlockPos = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_alchemyStorageUnlockPos of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_alchemyStorageUnlockPos
static int tolua_get_USERINFO_unsigned_m_alchemyStorageUnlockPos(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_alchemyStorageUnlockPos'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_alchemyStorageUnlockPos);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_alchemyStorageUnlockPos of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_alchemyStorageUnlockPos
static int tolua_set_USERINFO_unsigned_m_alchemyStorageUnlockPos(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_alchemyStorageUnlockPos'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_alchemyStorageUnlockPos = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_gemRecastTimes of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_gemRecastTimes
static int tolua_get_USERINFO_unsigned_m_gemRecastTimes(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_gemRecastTimes'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_gemRecastTimes);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_gemRecastTimes of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_gemRecastTimes
static int tolua_set_USERINFO_unsigned_m_gemRecastTimes(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_gemRecastTimes'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_gemRecastTimes = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: physical_attack of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_physical_attack
static int tolua_get_USERINFO_unsigned_physical_attack(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'physical_attack'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->physical_attack);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: physical_attack of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_physical_attack
static int tolua_set_USERINFO_unsigned_physical_attack(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'physical_attack'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->physical_attack = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: magic_attack of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_magic_attack
static int tolua_get_USERINFO_unsigned_magic_attack(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'magic_attack'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->magic_attack);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: magic_attack of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_magic_attack
static int tolua_set_USERINFO_unsigned_magic_attack(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'magic_attack'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->magic_attack = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skill_attack of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_skill_attack
static int tolua_get_USERINFO_unsigned_skill_attack(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill_attack'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->skill_attack);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skill_attack of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_skill_attack
static int tolua_set_USERINFO_unsigned_skill_attack(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill_attack'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill_attack = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: physical_defence of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_physical_defence
static int tolua_get_USERINFO_unsigned_physical_defence(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'physical_defence'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->physical_defence);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: physical_defence of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_physical_defence
static int tolua_set_USERINFO_unsigned_physical_defence(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'physical_defence'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->physical_defence = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: magic_defence of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_magic_defence
static int tolua_get_USERINFO_unsigned_magic_defence(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'magic_defence'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->magic_defence);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: magic_defence of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_magic_defence
static int tolua_set_USERINFO_unsigned_magic_defence(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'magic_defence'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->magic_defence = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skill_defence of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_skill_defence
static int tolua_get_USERINFO_unsigned_skill_defence(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill_defence'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->skill_defence);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skill_defence of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_skill_defence
static int tolua_set_USERINFO_unsigned_skill_defence(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill_defence'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill_defence = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: health_point of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_health_point
static int tolua_get_USERINFO_unsigned_health_point(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'health_point'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->health_point);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: health_point of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_health_point
static int tolua_set_USERINFO_unsigned_health_point(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'health_point'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->health_point = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: accurate of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_accurate
static int tolua_get_USERINFO_unsigned_accurate(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'accurate'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->accurate);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: accurate of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_accurate
static int tolua_set_USERINFO_unsigned_accurate(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'accurate'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->accurate = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dodge of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_dodge
static int tolua_get_USERINFO_unsigned_dodge(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dodge'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->dodge);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dodge of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_dodge
static int tolua_set_USERINFO_unsigned_dodge(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dodge'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dodge = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: wreck of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_wreck
static int tolua_get_USERINFO_unsigned_wreck(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wreck'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->wreck);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: wreck of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_wreck
static int tolua_set_USERINFO_unsigned_wreck(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'wreck'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->wreck = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: parry of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_parry
static int tolua_get_USERINFO_unsigned_parry(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parry'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->parry);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: parry of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_parry
static int tolua_set_USERINFO_unsigned_parry(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parry'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->parry = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: critical_strike of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_critical_strike
static int tolua_get_USERINFO_unsigned_critical_strike(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'critical_strike'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->critical_strike);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: critical_strike of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_critical_strike
static int tolua_set_USERINFO_unsigned_critical_strike(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'critical_strike'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->critical_strike = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tenacity of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_tenacity
static int tolua_get_USERINFO_unsigned_tenacity(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tenacity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tenacity);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tenacity of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_tenacity
static int tolua_set_USERINFO_unsigned_tenacity(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tenacity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tenacity = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: slay of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_slay
static int tolua_get_USERINFO_unsigned_slay(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'slay'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->slay);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: slay of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_slay
static int tolua_set_USERINFO_unsigned_slay(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'slay'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->slay = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: proficiency of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_proficiency
static int tolua_get_USERINFO_unsigned_proficiency(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'proficiency'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->proficiency);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: proficiency of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_proficiency
static int tolua_set_USERINFO_unsigned_proficiency(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'proficiency'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->proficiency = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: speed of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_speed
static int tolua_get_USERINFO_unsigned_speed(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'speed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->speed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: speed of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_speed
static int tolua_set_USERINFO_unsigned_speed(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'speed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->speed = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: total_hp of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_total_hp
static int tolua_get_USERINFO_unsigned_total_hp(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'total_hp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->total_hp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: total_hp of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_total_hp
static int tolua_set_USERINFO_unsigned_total_hp(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'total_hp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->total_hp = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: courage of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_courage
static int tolua_get_USERINFO_unsigned_courage(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'courage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->courage);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: courage of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_courage
static int tolua_set_USERINFO_unsigned_courage(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'courage'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->courage = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: charm of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_charm
static int tolua_get_USERINFO_unsigned_charm(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'charm'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->charm);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: charm of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_charm
static int tolua_set_USERINFO_unsigned_charm(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'charm'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->charm = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: trick of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_trick
static int tolua_get_USERINFO_unsigned_trick(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'trick'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->trick);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: trick of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_trick
static int tolua_set_USERINFO_unsigned_trick(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'trick'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->trick = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: effectiveness of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_effectiveness
static int tolua_get_USERINFO_unsigned_effectiveness(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'effectiveness'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->effectiveness);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: effectiveness of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_effectiveness
static int tolua_set_USERINFO_unsigned_effectiveness(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'effectiveness'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->effectiveness = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_player_exploit of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_player_exploit
static int tolua_get_USERINFO_unsigned_m_player_exploit(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_player_exploit'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_player_exploit);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_player_exploit of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_player_exploit
static int tolua_set_USERINFO_unsigned_m_player_exploit(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_player_exploit'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_player_exploit = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_playerExploerExperience of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_playerExploerExperience
static int tolua_get_USERINFO_unsigned_m_playerExploerExperience(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_playerExploerExperience'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_playerExploerExperience);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_playerExploerExperience of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_playerExploerExperience
static int tolua_set_USERINFO_unsigned_m_playerExploerExperience(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_playerExploerExperience'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_playerExploerExperience = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_playerGemAnima of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_get_USERINFO_unsigned_m_playerGemAnima
static int tolua_get_USERINFO_unsigned_m_playerGemAnima(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_playerGemAnima'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_playerGemAnima);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_playerGemAnima of class  USERINFO */
#ifndef TOLUA_DISABLE_tolua_set_USERINFO_unsigned_m_playerGemAnima
static int tolua_set_USERINFO_unsigned_m_playerGemAnima(lua_State* tolua_S)
{
  USERINFO* self = (USERINFO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_playerGemAnima'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_playerGemAnima = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  UserData */
#ifndef TOLUA_DISABLE_tolua_LuaClient_UserData_Get00
static int tolua_LuaClient_UserData_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UserData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UserData* tolua_ret = (UserData*)  UserData::Get();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UserData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUserId of class  UserData */
#ifndef TOLUA_DISABLE_tolua_LuaClient_UserData_getUserId00
static int tolua_LuaClient_UserData_getUserId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UserData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  UserData::getUserId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUserId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeroHp of class  UserData */
#ifndef TOLUA_DISABLE_tolua_LuaClient_UserData_getHeroHp00
static int tolua_LuaClient_UserData_getHeroHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UserData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  UserData::getHeroHp();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeroHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeroTotalHp of class  UserData */
#ifndef TOLUA_DISABLE_tolua_LuaClient_UserData_getHeroTotalHp00
static int tolua_LuaClient_UserData_getHeroTotalHp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UserData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  UserData::getHeroTotalHp();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeroTotalHp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUserType of class  UserData */
#ifndef TOLUA_DISABLE_tolua_LuaClient_UserData_GetUserType00
static int tolua_LuaClient_UserData_GetUserType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UserData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  UserData::GetUserType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUserType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUserInfo of class  UserData */
#ifndef TOLUA_DISABLE_tolua_LuaClient_UserData_GetUserInfo00
static int tolua_LuaClient_UserData_GetUserInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UserData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   USERINFO& tolua_ret = (USERINFO&)  UserData::GetUserInfo();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"USERINFO");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUserInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUserLevel of class  UserData */
#ifndef TOLUA_DISABLE_tolua_LuaClient_UserData_GetUserLevel00
static int tolua_LuaClient_UserData_GetUserLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UserData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   unsigned int tolua_ret = (unsigned int)  UserData::GetUserLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUserLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUserInfo of class  UserData */
#ifndef TOLUA_DISABLE_tolua_LuaClient_UserData_GetUserInfo01
static int tolua_LuaClient_UserData_GetUserInfo01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UserData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UserData* self = (UserData*)  tolua_tousertype(tolua_S,1,0);
  unsigned int id = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUserInfo'", NULL);
#endif
  {
   USERINFO* tolua_ret = (USERINFO*)  self->GetUserInfo(id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"USERINFO");
  }
 }
 return 1;
tolua_lerror:
 return tolua_LuaClient_UserData_GetUserInfo00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: defaultCenter of class  NotificationCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_NotificationCenter_defaultCenter00
static int tolua_LuaClient_NotificationCenter_defaultCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"NotificationCenter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   NotificationCenter* tolua_ret = (NotificationCenter*)  NotificationCenter::defaultCenter();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"NotificationCenter");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'defaultCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptObserver of class  NotificationCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_NotificationCenter_registerScriptObserver00
static int tolua_LuaClient_NotificationCenter_registerScriptObserver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NotificationCenter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NotificationCenter* self = (NotificationCenter*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptObserver'", NULL);
#endif
  {
   int tolua_ret = (int)  self->registerScriptObserver(handler);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptObserver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptObserver of class  NotificationCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_NotificationCenter_unregisterScriptObserver00
static int tolua_LuaClient_NotificationCenter_unregisterScriptObserver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NotificationCenter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NotificationCenter* self = (NotificationCenter*)  tolua_tousertype(tolua_S,1,0);
  int handler = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptObserver'", NULL);
#endif
  {
   self->unregisterScriptObserver(handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptObserver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterAllScriptObservers of class  NotificationCenter */
#ifndef TOLUA_DISABLE_tolua_LuaClient_NotificationCenter_unregisterAllScriptObservers00
static int tolua_LuaClient_NotificationCenter_unregisterAllScriptObservers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NotificationCenter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NotificationCenter* self = (NotificationCenter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterAllScriptObservers'", NULL);
#endif
  {
   self->unregisterAllScriptObservers();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterAllScriptObservers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_Get00
static int tolua_LuaClient_GameManager_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameManager* tolua_ret = (GameManager*)  GameManager::Get();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSceneLayer of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_GetSceneLayer00
static int tolua_LuaClient_GameManager_GetSceneLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSceneLayer'", NULL);
#endif
  {
   SceneLayer* tolua_ret = (SceneLayer*)  self->GetSceneLayer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SceneLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSceneLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHero of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_getHero00
static int tolua_LuaClient_GameManager_getHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHero'", NULL);
#endif
  {
   SpriteSeer* tolua_ret = (SpriteSeer*)  self->getHero();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SpriteSeer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHero of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_setHero00
static int tolua_LuaClient_GameManager_setHero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SpriteSeer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
  SpriteSeer* hero = ((SpriteSeer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHero'", NULL);
#endif
  {
   self->setHero(hero);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeroTypeId of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_getHeroTypeId00
static int tolua_LuaClient_GameManager_getHeroTypeId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeroTypeId'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getHeroTypeId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeroTypeId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHeroTypeId of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_setHeroTypeId00
static int tolua_LuaClient_GameManager_setHeroTypeId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
  int typeId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHeroTypeId'", NULL);
#endif
  {
   self->setHeroTypeId(typeId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHeroTypeId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeMap of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_changeMap00
static int tolua_LuaClient_GameManager_changeMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"KMapFromType",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
  int mapId = ((int)  tolua_tonumber(tolua_S,2,0));
  KMapFromType fromMapType = *((KMapFromType*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeMap'", NULL);
#endif
  {
   self->changeMap(mapId,fromMapType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: goToSplash of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_goToSplash00
static int tolua_LuaClient_GameManager_goToSplash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'goToSplash'", NULL);
#endif
  {
   CCScene* tolua_ret = (CCScene*)  self->goToSplash();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'goToSplash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: goToFrontend of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_goToFrontend00
static int tolua_LuaClient_GameManager_goToFrontend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'goToFrontend'", NULL);
#endif
  {
   self->goToFrontend();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'goToFrontend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startGame of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_startGame00
static int tolua_LuaClient_GameManager_startGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startGame'", NULL);
#endif
  {
   self->startGame();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: exitGame of class  GameManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameManager_exitGame00
static int tolua_LuaClient_GameManager_exitGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameManager* self = (GameManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'exitGame'", NULL);
#endif
  {
   self->exitGame();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'exitGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  SkillUIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SkillUIManager_getInstance00
static int tolua_LuaClient_SkillUIManager_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SkillUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SkillUIManager* tolua_ret = (SkillUIManager*)  SkillUIManager::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SkillUIManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetValue of class  SkillUIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SkillUIManager_ResetValue00
static int tolua_LuaClient_SkillUIManager_ResetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkillUIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkillUIManager* self = (SkillUIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetValue'", NULL);
#endif
  {
   self->ResetValue();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendGetUserSkillReqMessage of class  SkillUIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SkillUIManager_sendGetUserSkillReqMessage00
static int tolua_LuaClient_SkillUIManager_sendGetUserSkillReqMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkillUIManager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkillUIManager* self = (SkillUIManager*)  tolua_tousertype(tolua_S,1,0);
  bool bSender = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendGetUserSkillReqMessage'", NULL);
#endif
  {
   self->sendGetUserSkillReqMessage(bSender);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendGetUserSkillReqMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendAddUserSkillReqMessage of class  SkillUIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SkillUIManager_sendAddUserSkillReqMessage00
static int tolua_LuaClient_SkillUIManager_sendAddUserSkillReqMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkillUIManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkillUIManager* self = (SkillUIManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int skillId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int levelId = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendAddUserSkillReqMessage'", NULL);
#endif
  {
   self->sendAddUserSkillReqMessage(skillId,levelId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendAddUserSkillReqMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendUserSkillDiffReqMessage of class  SkillUIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SkillUIManager_sendUserSkillDiffReqMessage00
static int tolua_LuaClient_SkillUIManager_sendUserSkillDiffReqMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkillUIManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkillUIManager* self = (SkillUIManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int skillId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int levelId = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendUserSkillDiffReqMessage'", NULL);
#endif
  {
   self->sendUserSkillDiffReqMessage(skillId,levelId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendUserSkillDiffReqMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendSetSlotAttributeMessage of class  SkillUIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_SkillUIManager_sendSetSlotAttributeMessage00
static int tolua_LuaClient_SkillUIManager_sendSetSlotAttributeMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkillUIManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkillUIManager* self = (SkillUIManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int slotIndex = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int skillId = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendSetSlotAttributeMessage'", NULL);
#endif
  {
   self->sendSetSlotAttributeMessage(slotIndex,skillId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendSetSlotAttributeMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ElfExploreManger */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ElfExploreManger_new00
static int tolua_LuaClient_ElfExploreManger_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ElfExploreManger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ElfExploreManger* tolua_ret = (ElfExploreManger*)  Mtolua_new((ElfExploreManger)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ElfExploreManger");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ElfExploreManger */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ElfExploreManger_new00_local
static int tolua_LuaClient_ElfExploreManger_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ElfExploreManger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ElfExploreManger* tolua_ret = (ElfExploreManger*)  Mtolua_new((ElfExploreManger)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ElfExploreManger");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  ElfExploreManger */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ElfExploreManger_Get00
static int tolua_LuaClient_ElfExploreManger_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ElfExploreManger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ElfExploreManger* tolua_ret = (ElfExploreManger*)  ElfExploreManger::Get();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ElfExploreManger");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  ElfExploreManger */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ElfExploreManger_Destroy00
static int tolua_LuaClient_ElfExploreManger_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ElfExploreManger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ElfExploreManger::Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetValue of class  ElfExploreManger */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ElfExploreManger_ResetValue00
static int tolua_LuaClient_ElfExploreManger_ResetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ElfExploreManger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ElfExploreManger* self = (ElfExploreManger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetValue'", NULL);
#endif
  {
   self->ResetValue();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendExchangeElfReq of class  ElfExploreManger */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ElfExploreManger_SendExchangeElfReq00
static int tolua_LuaClient_ElfExploreManger_SendExchangeElfReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ElfExploreManger",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ElfExploreManger* self = (ElfExploreManger*)  tolua_tousertype(tolua_S,1,0);
  unsigned int elfId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendExchangeElfReq'", NULL);
#endif
  {
   self->SendExchangeElfReq(elfId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendExchangeElfReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendExploreReq of class  ElfExploreManger */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ElfExploreManger_SendExploreReq00
static int tolua_LuaClient_ElfExploreManger_SendExploreReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ElfExploreManger",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ElfExploreManger* self = (ElfExploreManger*)  tolua_tousertype(tolua_S,1,0);
  unsigned int type = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendExploreReq'", NULL);
#endif
  {
   self->SendExploreReq(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendExploreReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendExploreDetermineReq of class  ElfExploreManger */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ElfExploreManger_SendExploreDetermineReq00
static int tolua_LuaClient_ElfExploreManger_SendExploreDetermineReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ElfExploreManger",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ElfExploreManger* self = (ElfExploreManger*)  tolua_tousertype(tolua_S,1,0);
  unsigned int optionId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendExploreDetermineReq'", NULL);
#endif
  {
   self->SendExploreDetermineReq(optionId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendExploreDetermineReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setChatToolbar of class  MainMenuLayer */
#ifndef TOLUA_DISABLE_tolua_LuaClient_MainMenuLayer_setChatToolbar00
static int tolua_LuaClient_MainMenuLayer_setChatToolbar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MainMenuLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MainMenuLayer* self = (MainMenuLayer*)  tolua_tousertype(tolua_S,1,0);
  bool isChatVisible = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool isFunctionVisible = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool isExtraVisible = ((bool)  tolua_toboolean(tolua_S,4,false));
  int order = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setChatToolbar'", NULL);
#endif
  {
   self->setChatToolbar(isChatVisible,isFunctionVisible,isExtraVisible,order);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setChatToolbar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMainMenuLayer of class  MainMenuLayer */
#ifndef TOLUA_DISABLE_tolua_LuaClient_MainMenuLayer_getMainMenuLayer00
static int tolua_LuaClient_MainMenuLayer_getMainMenuLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MainMenuLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MainMenuLayer* tolua_ret = (MainMenuLayer*)  MainMenuLayer::getMainMenuLayer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MainMenuLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMainMenuLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumByFormat of class  MainMenuLayer */
#ifndef TOLUA_DISABLE_tolua_LuaClient_MainMenuLayer_GetNumByFormat00
static int tolua_LuaClient_MainMenuLayer_GetNumByFormat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MainMenuLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int num = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  MainMenuLayer::GetNumByFormat(num);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumByFormat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedManager of class  GameAudioManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameAudioManager_sharedManager00
static int tolua_LuaClient_GameAudioManager_sharedManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameAudioManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameAudioManager* tolua_ret = (GameAudioManager*)  GameAudioManager::sharedManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameAudioManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: playEffect of class  GameAudioManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameAudioManager_playEffect00
static int tolua_LuaClient_GameAudioManager_playEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAudioManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAudioManager* self = (GameAudioManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int soundID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  bool isLoop = ((bool)  tolua_toboolean(tolua_S,3,0));
  const float delay = ((const float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'playEffect'", NULL);
#endif
  {
   self->playEffect(soundID,isLoop,delay);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'playEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAllEffect of class  GameAudioManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GameAudioManager_stopAllEffect00
static int tolua_LuaClient_GameAudioManager_stopAllEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GameAudioManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GameAudioManager* self = (GameAudioManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAllEffect'", NULL);
#endif
  {
   self->stopAllEffect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAllEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedManager of class  ParticleManagerX */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ParticleManagerX_sharedManager00
static int tolua_LuaClient_ParticleManagerX_sharedManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ParticleManagerX",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ParticleManagerX* tolua_ret = (ParticleManagerX*)  ParticleManagerX::sharedManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ParticleManagerX");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParticles of class  ParticleManagerX */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ParticleManagerX_getParticles00
static int tolua_LuaClient_ParticleManagerX_getParticles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleManagerX",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleManagerX* self = (ParticleManagerX*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParticles'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getParticles(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParticles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParticles_uieffect of class  ParticleManagerX */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ParticleManagerX_getParticles_uieffect00
static int tolua_LuaClient_ParticleManagerX_getParticles_uieffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleManagerX",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleManagerX* self = (ParticleManagerX*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParticles_uieffect'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getParticles_uieffect(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParticles_uieffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attr_key of class  ITEMATTR */
#ifndef TOLUA_DISABLE_tolua_get_ITEMATTR_unsigned_attr_key
static int tolua_get_ITEMATTR_unsigned_attr_key(lua_State* tolua_S)
{
  ITEMATTR* self = (ITEMATTR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attr_key'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attr_key);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attr_key of class  ITEMATTR */
#ifndef TOLUA_DISABLE_tolua_set_ITEMATTR_unsigned_attr_key
static int tolua_set_ITEMATTR_unsigned_attr_key(lua_State* tolua_S)
{
  ITEMATTR* self = (ITEMATTR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attr_key'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attr_key = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attr_basic_value of class  ITEMATTR */
#ifndef TOLUA_DISABLE_tolua_get_ITEMATTR_unsigned_attr_basic_value
static int tolua_get_ITEMATTR_unsigned_attr_basic_value(lua_State* tolua_S)
{
  ITEMATTR* self = (ITEMATTR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attr_basic_value'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attr_basic_value);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attr_basic_value of class  ITEMATTR */
#ifndef TOLUA_DISABLE_tolua_set_ITEMATTR_unsigned_attr_basic_value
static int tolua_set_ITEMATTR_unsigned_attr_basic_value(lua_State* tolua_S)
{
  ITEMATTR* self = (ITEMATTR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attr_basic_value'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attr_basic_value = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attr_intensify_value of class  ITEMATTR */
#ifndef TOLUA_DISABLE_tolua_get_ITEMATTR_unsigned_attr_intensify_value
static int tolua_get_ITEMATTR_unsigned_attr_intensify_value(lua_State* tolua_S)
{
  ITEMATTR* self = (ITEMATTR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attr_intensify_value'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attr_intensify_value);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attr_intensify_value of class  ITEMATTR */
#ifndef TOLUA_DISABLE_tolua_set_ITEMATTR_unsigned_attr_intensify_value
static int tolua_set_ITEMATTR_unsigned_attr_intensify_value(lua_State* tolua_S)
{
  ITEMATTR* self = (ITEMATTR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attr_intensify_value'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attr_intensify_value = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attr_gem_value of class  ITEMATTR */
#ifndef TOLUA_DISABLE_tolua_get_ITEMATTR_unsigned_attr_gem_value
static int tolua_get_ITEMATTR_unsigned_attr_gem_value(lua_State* tolua_S)
{
  ITEMATTR* self = (ITEMATTR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attr_gem_value'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attr_gem_value);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attr_gem_value of class  ITEMATTR */
#ifndef TOLUA_DISABLE_tolua_set_ITEMATTR_unsigned_attr_gem_value
static int tolua_set_ITEMATTR_unsigned_attr_gem_value(lua_State* tolua_S)
{
  ITEMATTR* self = (ITEMATTR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attr_gem_value'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attr_gem_value = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getItemInfo of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_LuaClient_BackPackItem_getItemInfo00
static int tolua_LuaClient_BackPackItem_getItemInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BackPackItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getItemInfo'", NULL);
#endif
  {
   ItemBase* tolua_ret = (ItemBase*)  self->getItemInfo();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ItemBase");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getItemInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getItemId of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_LuaClient_BackPackItem_getItemId00
static int tolua_LuaClient_BackPackItem_getItemId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BackPackItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getItemId'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getItemId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getItemId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isLocked of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_get_BackPackItem_isLocked
static int tolua_get_BackPackItem_isLocked(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isLocked'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isLocked);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isLocked of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_set_BackPackItem_isLocked
static int tolua_set_BackPackItem_isLocked(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isLocked'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isLocked = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isEmpty of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_get_BackPackItem_isEmpty
static int tolua_get_BackPackItem_isEmpty(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isEmpty'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isEmpty);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isEmpty of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_set_BackPackItem_isEmpty
static int tolua_set_BackPackItem_isEmpty(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isEmpty'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isEmpty = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: position of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_get_BackPackItem_unsigned_position
static int tolua_get_BackPackItem_unsigned_position(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->position);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: position of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_set_BackPackItem_unsigned_position
static int tolua_set_BackPackItem_unsigned_position(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->position = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: amount of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_get_BackPackItem_unsigned_amount
static int tolua_get_BackPackItem_unsigned_amount(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'amount'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->amount);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: amount of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_set_BackPackItem_unsigned_amount
static int tolua_set_BackPackItem_unsigned_amount(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'amount'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->amount = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: itemLevel of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_get_BackPackItem_unsigned_itemLevel
static int tolua_get_BackPackItem_unsigned_itemLevel(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'itemLevel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->itemLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: itemLevel of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_set_BackPackItem_unsigned_itemLevel
static int tolua_set_BackPackItem_unsigned_itemLevel(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'itemLevel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->itemLevel = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_equipInfo of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_get_BackPackItem_m_equipInfo_ptr
static int tolua_get_BackPackItem_m_equipInfo_ptr(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_equipInfo'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_equipInfo,"EQUIPINFO");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_equipInfo of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_set_BackPackItem_m_equipInfo_ptr
static int tolua_set_BackPackItem_m_equipInfo_ptr(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_equipInfo'",NULL);
  if (!tolua_isusertype(tolua_S,2,"EQUIPINFO",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_equipInfo = ((EQUIPINFO*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: packType of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_get_BackPackItem_unsigned_packType
static int tolua_get_BackPackItem_unsigned_packType(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'packType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->packType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: packType of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_set_BackPackItem_unsigned_packType
static int tolua_set_BackPackItem_unsigned_packType(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'packType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->packType = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_spriteInfo of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_get_BackPackItem_m_spriteInfo_ptr
static int tolua_get_BackPackItem_m_spriteInfo_ptr(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_spriteInfo'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_spriteInfo,"SPRITEINFO");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_spriteInfo of class  BackPackItem */
#ifndef TOLUA_DISABLE_tolua_set_BackPackItem_m_spriteInfo_ptr
static int tolua_set_BackPackItem_m_spriteInfo_ptr(lua_State* tolua_S)
{
  BackPackItem* self = (BackPackItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_spriteInfo'",NULL);
  if (!tolua_isusertype(tolua_S,2,"SPRITEINFO",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_spriteInfo = ((SPRITEINFO*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  ItemManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ItemManager_Get00
static int tolua_LuaClient_ItemManager_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ItemManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ItemManager* tolua_ret = (ItemManager*)  ItemManager::Get();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ItemManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findItemByPos of class  ItemManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ItemManager_findItemByPos00
static int tolua_LuaClient_ItemManager_findItemByPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ItemManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ItemManager* self = (ItemManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int pos = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findItemByPos'", NULL);
#endif
  {
   BackPackItem* tolua_ret = (BackPackItem*)  self->findItemByPos(pos);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BackPackItem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findItemByPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIconSpriteById of class  ItemManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ItemManager_getIconSpriteById00
static int tolua_LuaClient_ItemManager_getIconSpriteById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ItemManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ItemManager* self = (ItemManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int ItemId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIconSpriteById'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->getIconSpriteById(ItemId);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIconSpriteById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIconFrame of class  ItemManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ItemManager_getIconFrame00
static int tolua_LuaClient_ItemManager_getIconFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ItemManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ItemManager* self = (ItemManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int level = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIconFrame'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->getIconFrame(level);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIconFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLabelColorByQuality of class  ItemManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ItemManager_getLabelColorByQuality00
static int tolua_LuaClient_ItemManager_getLabelColorByQuality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ItemManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ItemManager* self = (ItemManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int quality = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLabelColorByQuality'", NULL);
#endif
  {
   ccColor3B tolua_ret = (ccColor3B)  self->getLabelColorByQuality(quality);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccColor3B)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccColor3B));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3B");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLabelColorByQuality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getItemNumberById of class  ItemManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ItemManager_getItemNumberById00
static int tolua_LuaClient_ItemManager_getItemNumberById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ItemManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ItemManager* self = (ItemManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int id = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getItemNumberById'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getItemNumberById(id);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getItemNumberById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttributionText of class  ItemManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ItemManager_getAttributionText00
static int tolua_LuaClient_ItemManager_getAttributionText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ItemManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ItemManager* self = (ItemManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int key = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int value = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttributionText'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getAttributionText(key,value);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttributionText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEquipLevel of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_LuaClient_ItemBase_getEquipLevel00
static int tolua_LuaClient_ItemBase_getEquipLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ItemBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEquipLevel'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getEquipLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEquipLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_id of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_unsigned_m_id
static int tolua_get_ItemBase_unsigned_m_id(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_id of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_unsigned_m_id
static int tolua_set_ItemBase_unsigned_m_id(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_id = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_name of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_m_name
static int tolua_get_ItemBase_m_name(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_name'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->m_name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_name of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_m_name
static int tolua_set_ItemBase_m_name(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_name'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->m_name,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b_isPiledUp of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_b_isPiledUp
static int tolua_get_ItemBase_b_isPiledUp(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b_isPiledUp'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->b_isPiledUp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b_isPiledUp of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_b_isPiledUp
static int tolua_set_ItemBase_b_isPiledUp(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b_isPiledUp'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b_isPiledUp = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_maxPiledNum of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_unsigned_m_maxPiledNum
static int tolua_get_ItemBase_unsigned_m_maxPiledNum(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_maxPiledNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_maxPiledNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_maxPiledNum of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_unsigned_m_maxPiledNum
static int tolua_set_ItemBase_unsigned_m_maxPiledNum(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_maxPiledNum'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_maxPiledNum = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_source of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_LuaClient_ItemBase_m_source
static int tolua_get_LuaClient_ItemBase_m_source(lua_State* tolua_S)
{
 int tolua_index;
  ItemBase* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ItemBase*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=5)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->m_source[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_source of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_LuaClient_ItemBase_m_source
static int tolua_set_LuaClient_ItemBase_m_source(lua_State* tolua_S)
{
 int tolua_index;
  ItemBase* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ItemBase*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0);
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=5)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->m_source[tolua_index] = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_byeprice of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_unsigned_m_byeprice
static int tolua_get_ItemBase_unsigned_m_byeprice(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byeprice'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_byeprice);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_byeprice of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_unsigned_m_byeprice
static int tolua_set_ItemBase_unsigned_m_byeprice(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_byeprice'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_byeprice = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_sellprice of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_unsigned_m_sellprice
static int tolua_get_ItemBase_unsigned_m_sellprice(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sellprice'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_sellprice);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_sellprice of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_unsigned_m_sellprice
static int tolua_set_ItemBase_unsigned_m_sellprice(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_sellprice'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_sellprice = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_requiredLevel of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_unsigned_m_requiredLevel
static int tolua_get_ItemBase_unsigned_m_requiredLevel(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_requiredLevel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_requiredLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_requiredLevel of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_unsigned_m_requiredLevel
static int tolua_set_ItemBase_unsigned_m_requiredLevel(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_requiredLevel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_requiredLevel = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_type of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_unsigned_m_type
static int tolua_get_ItemBase_unsigned_m_type(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_type of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_unsigned_m_type
static int tolua_set_ItemBase_unsigned_m_type(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_type = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b_Destroyed of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_b_Destroyed
static int tolua_get_ItemBase_b_Destroyed(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b_Destroyed'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->b_Destroyed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b_Destroyed of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_b_Destroyed
static int tolua_set_ItemBase_b_Destroyed(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b_Destroyed'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b_Destroyed = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_szDescription of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_m_szDescription
static int tolua_get_ItemBase_m_szDescription(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_szDescription'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->m_szDescription);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_szDescription of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_m_szDescription
static int tolua_set_ItemBase_m_szDescription(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_szDescription'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->m_szDescription,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_quality of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_unsigned_m_quality
static int tolua_get_ItemBase_unsigned_m_quality(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_quality'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_quality);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_quality of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_unsigned_m_quality
static int tolua_set_ItemBase_unsigned_m_quality(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_quality'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_quality = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_szInlayHole of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_get_ItemBase_m_szInlayHole
static int tolua_get_ItemBase_m_szInlayHole(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_szInlayHole'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->m_szInlayHole);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_szInlayHole of class  ItemBase */
#ifndef TOLUA_DISABLE_tolua_set_ItemBase_m_szInlayHole
static int tolua_set_ItemBase_m_szInlayHole(lua_State* tolua_S)
{
  ItemBase* self = (ItemBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_szInlayHole'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->m_szInlayHole,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_ownerType of class  EquipmentItem */
#ifndef TOLUA_DISABLE_tolua_get_EquipmentItem_unsigned_m_ownerType
static int tolua_get_EquipmentItem_unsigned_m_ownerType(lua_State* tolua_S)
{
  EquipmentItem* self = (EquipmentItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_ownerType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_ownerType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_ownerType of class  EquipmentItem */
#ifndef TOLUA_DISABLE_tolua_set_EquipmentItem_unsigned_m_ownerType
static int tolua_set_EquipmentItem_unsigned_m_ownerType(lua_State* tolua_S)
{
  EquipmentItem* self = (EquipmentItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_ownerType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_ownerType = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_equipPart of class  EquipmentItem */
#ifndef TOLUA_DISABLE_tolua_get_EquipmentItem_unsigned_m_equipPart
static int tolua_get_EquipmentItem_unsigned_m_equipPart(lua_State* tolua_S)
{
  EquipmentItem* self = (EquipmentItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_equipPart'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_equipPart);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_equipPart of class  EquipmentItem */
#ifndef TOLUA_DISABLE_tolua_set_EquipmentItem_unsigned_m_equipPart
static int tolua_set_EquipmentItem_unsigned_m_equipPart(lua_State* tolua_S)
{
  EquipmentItem* self = (EquipmentItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_equipPart'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_equipPart = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_equipLevel of class  EquipmentItem */
#ifndef TOLUA_DISABLE_tolua_get_EquipmentItem_unsigned_m_equipLevel
static int tolua_get_EquipmentItem_unsigned_m_equipLevel(lua_State* tolua_S)
{
  EquipmentItem* self = (EquipmentItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_equipLevel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_equipLevel);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_equipLevel of class  EquipmentItem */
#ifndef TOLUA_DISABLE_tolua_set_EquipmentItem_unsigned_m_equipLevel
static int tolua_set_EquipmentItem_unsigned_m_equipLevel(lua_State* tolua_S)
{
  EquipmentItem* self = (EquipmentItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_equipLevel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_equipLevel = ((unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_attribute of class  EquipmentItem */
#ifndef TOLUA_DISABLE_tolua_get_EquipmentItem_m_attribute
static int tolua_get_EquipmentItem_m_attribute(lua_State* tolua_S)
{
  EquipmentItem* self = (EquipmentItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_attribute'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_attribute);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_attribute of class  EquipmentItem */
#ifndef TOLUA_DISABLE_tolua_set_EquipmentItem_m_attribute
static int tolua_set_EquipmentItem_m_attribute(lua_State* tolua_S)
{
  EquipmentItem* self = (EquipmentItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_attribute'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_attribute = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_Get00
static int tolua_LuaClient_TimeManager_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TimeManager* tolua_ret = (TimeManager*)  TimeManager::Get();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TimeManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurServerTime of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_getCurServerTime00
static int tolua_LuaClient_TimeManager_getCurServerTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurServerTime'", NULL);
#endif
  {
   long tolua_ret = (long)  self->getCurServerTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurServerTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: secondsToString of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_secondsToString00
static int tolua_LuaClient_TimeManager_secondsToString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  long seconds = ((long)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'secondsToString'", NULL);
#endif
  {
   string tolua_ret = (string)  self->secondsToString(seconds);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'secondsToString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLuaTimer of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_registerLuaTimer00
static int tolua_LuaClient_TimeManager_registerLuaTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
    (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
  int counterId = ((int)  tolua_tonumber(tolua_S,3,0));
  long endTime = ((long)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerLuaTimer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->registerLuaTimer(handler,counterId,endTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLuaTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterLuaTimer of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_unregisterLuaTimer00
static int tolua_LuaClient_TimeManager_unregisterLuaTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  int handler = ((int)  tolua_tonumber(tolua_S,2,0));
  int counterId = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterLuaTimer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->unregisterLuaTimer(handler,counterId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterLuaTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachLuaTimer of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_attachLuaTimer00
static int tolua_LuaClient_TimeManager_attachLuaTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  int handler = ((int)  tolua_tonumber(tolua_S,2,0));
  int counterId = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachLuaTimer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->attachLuaTimer(handler,counterId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachLuaTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startTimer of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_startTimer00
static int tolua_LuaClient_TimeManager_startTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  int counterId = ((int)  tolua_tonumber(tolua_S,2,0));
  long endTime = ((long)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startTimer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->startTimer(counterId,endTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopTimer of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_stopTimer00
static int tolua_LuaClient_TimeManager_stopTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  int counterId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopTimer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->stopTimer(counterId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: renewTimer of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_renewTimer00
static int tolua_LuaClient_TimeManager_renewTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  int counterId = ((int)  tolua_tonumber(tolua_S,2,0));
  long endTime = ((long)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'renewTimer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->renewTimer(counterId,endTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'renewTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasTimer of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_hasTimer00
static int tolua_LuaClient_TimeManager_hasTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  int counterId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasTimer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasTimer(counterId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasLuaObserver of class  TimeManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TimeManager_hasLuaObserver00
static int tolua_LuaClient_TimeManager_hasLuaObserver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeManager* self = (TimeManager*)  tolua_tousertype(tolua_S,1,0);
  int handler = ((int)  tolua_tonumber(tolua_S,2,0));
  int counterId = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasLuaObserver'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasLuaObserver(handler,counterId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasLuaObserver'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  GemStonesFromLua */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GemStonesFromLua_getInstance00
static int tolua_LuaClient_GemStonesFromLua_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GemStonesFromLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GemStonesFromLua* tolua_ret = (GemStonesFromLua*)  GemStonesFromLua::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GemStonesFromLua");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EquipInlayGemReq of class  GemStonesFromLua */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GemStonesFromLua_EquipInlayGemReq00
static int tolua_LuaClient_GemStonesFromLua_EquipInlayGemReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GemStonesFromLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GemStonesFromLua* self = (GemStonesFromLua*)  tolua_tousertype(tolua_S,1,0);
  unsigned int equip = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int hole = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int gemId = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EquipInlayGemReq'", NULL);
#endif
  {
   self->EquipInlayGemReq(equip,hole,gemId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EquipInlayGemReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GemRecastReq of class  GemStonesFromLua */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GemStonesFromLua_GemRecastReq00
static int tolua_LuaClient_GemStonesFromLua_GemRecastReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GemStonesFromLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GemStonesFromLua* self = (GemStonesFromLua*)  tolua_tousertype(tolua_S,1,0);
  unsigned int equipPos = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int hole1 = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int hole2 = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int hole3 = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
  unsigned int hole4 = ((unsigned int)  tolua_tonumber(tolua_S,6,0));
  unsigned int currencyKey = ((unsigned int)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GemRecastReq'", NULL);
#endif
  {
   self->GemRecastReq(equipPos,hole1,hole2,hole3,hole4,currencyKey);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GemRecastReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GemAnimaExchangeReq of class  GemStonesFromLua */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GemStonesFromLua_GemAnimaExchangeReq00
static int tolua_LuaClient_GemStonesFromLua_GemAnimaExchangeReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GemStonesFromLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GemStonesFromLua* self = (GemStonesFromLua*)  tolua_tousertype(tolua_S,1,0);
  unsigned int gemId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int multi = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GemAnimaExchangeReq'", NULL);
#endif
  {
   self->GemAnimaExchangeReq(gemId,multi);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GemAnimaExchangeReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GemHoleUnlockReq of class  GemStonesFromLua */
#ifndef TOLUA_DISABLE_tolua_LuaClient_GemStonesFromLua_GemHoleUnlockReq00
static int tolua_LuaClient_GemStonesFromLua_GemHoleUnlockReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GemStonesFromLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GemStonesFromLua* self = (GemStonesFromLua*)  tolua_tousertype(tolua_S,1,0);
  unsigned int exchangeId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int equipPos = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GemHoleUnlockReq'", NULL);
#endif
  {
   self->GemHoleUnlockReq(exchangeId,equipPos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GemHoleUnlockReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  PvAIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_PvAIManager_Get00
static int tolua_LuaClient_PvAIManager_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PvAIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PvAIManager* tolua_ret = (PvAIManager*)  PvAIManager::Get();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PvAIManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendPvAIReq of class  PvAIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_PvAIManager_sendPvAIReq00
static int tolua_LuaClient_PvAIManager_sendPvAIReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PvAIManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PvAIManager* self = (PvAIManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int userId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendPvAIReq'", NULL);
#endif
  {
   self->sendPvAIReq(userId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendPvAIReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendPvAIInfoReq of class  PvAIManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_PvAIManager_sendPvAIInfoReq00
static int tolua_LuaClient_PvAIManager_sendPvAIInfoReq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PvAIManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PvAIManager* self = (PvAIManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendPvAIInfoReq'", NULL);
#endif
  {
   self->sendPvAIInfoReq();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendPvAIInfoReq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  TutorialsManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TutorialsManager_Get00
static int tolua_LuaClient_TutorialsManager_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TutorialsManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TutorialsManager* tolua_ret = (TutorialsManager*)  TutorialsManager::Get();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TutorialsManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartOneTutorial of class  TutorialsManager */
#ifndef TOLUA_DISABLE_tolua_LuaClient_TutorialsManager_StartOneTutorial00
static int tolua_LuaClient_TutorialsManager_StartOneTutorial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TutorialsManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TutorialsManager* self = (TutorialsManager*)  tolua_tousertype(tolua_S,1,0);
  unsigned int id = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartOneTutorial'", NULL);
#endif
  {
   self->StartOneTutorial(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartOneTutorial'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaClient_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"SpriteFactory","SpriteFactory","",NULL);
  tolua_beginmodule(tolua_S,"SpriteFactory");
   tolua_function(tolua_S,"PrintLog",tolua_LuaClient_SpriteFactory_PrintLog00);
   tolua_function(tolua_S,"sharedFactory",tolua_LuaClient_SpriteFactory_sharedFactory00);
   tolua_function(tolua_S,"GetValue",tolua_LuaClient_SpriteFactory_GetValue00);
   tolua_function(tolua_S,"ShowElfOnLayerAtPoint",tolua_LuaClient_SpriteFactory_ShowElfOnLayerAtPoint00);
   tolua_function(tolua_S,"RemoveElfFromHero",tolua_LuaClient_SpriteFactory_RemoveElfFromHero00);
   tolua_function(tolua_S,"AttachElfToOneHero",tolua_LuaClient_SpriteFactory_AttachElfToOneHero00);
   tolua_function(tolua_S,"GetMainMenuLayerNode",tolua_LuaClient_SpriteFactory_GetMainMenuLayerNode00);
   tolua_function(tolua_S,"ResetValue",tolua_LuaClient_SpriteFactory_ResetValue00);
   tolua_function(tolua_S,"ShowElfPanelWithBackPackLayer",tolua_LuaClient_SpriteFactory_ShowElfPanelWithBackPackLayer00);
   tolua_function(tolua_S,"SendElfAwakeMessage",tolua_LuaClient_SpriteFactory_SendElfAwakeMessage00);
   tolua_function(tolua_S,"SendAwakeConfigMessage",tolua_LuaClient_SpriteFactory_SendAwakeConfigMessage00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SpriteElfDataCenter","SpriteElfDataCenter","",tolua_collect_SpriteElfDataCenter);
  #else
  tolua_cclass(tolua_S,"SpriteElfDataCenter","SpriteElfDataCenter","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SpriteElfDataCenter");
   tolua_function(tolua_S,"new",tolua_LuaClient_SpriteElfDataCenter_new00);
   tolua_function(tolua_S,"new_local",tolua_LuaClient_SpriteElfDataCenter_new00_local);
   tolua_function(tolua_S,".call",tolua_LuaClient_SpriteElfDataCenter_new00_local);
   tolua_function(tolua_S,"delete",tolua_LuaClient_SpriteElfDataCenter_delete00);
   tolua_function(tolua_S,"Get",tolua_LuaClient_SpriteElfDataCenter_Get00);
   tolua_function(tolua_S,"Destroy",tolua_LuaClient_SpriteElfDataCenter_Destroy00);
   tolua_function(tolua_S,"EquipOneElf",tolua_LuaClient_SpriteElfDataCenter_EquipOneElf00);
   tolua_function(tolua_S,"SendGetElfListMessage",tolua_LuaClient_SpriteElfDataCenter_SendGetElfListMessage00);
   tolua_function(tolua_S,"SendSetElfStateMessage",tolua_LuaClient_SpriteElfDataCenter_SendSetElfStateMessage00);
   tolua_function(tolua_S,"GetHeroUserId",tolua_LuaClient_SpriteElfDataCenter_GetHeroUserId00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"LevelManager","LevelManager","",NULL);
  tolua_beginmodule(tolua_S,"LevelManager");
   tolua_function(tolua_S,"sShareInstance",tolua_LuaClient_LevelManager_sShareInstance00);
   tolua_function(tolua_S,"isCurrentPPVELevel",tolua_LuaClient_LevelManager_isCurrentPPVELevel00);
   tolua_function(tolua_S,"isCurrentPVELevel",tolua_LuaClient_LevelManager_isCurrentPVELevel00);
   tolua_function(tolua_S,"isCurrentPVPLevel",tolua_LuaClient_LevelManager_isCurrentPVPLevel00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"GM_ATTR_COIN_UPDATE",GM_ATTR_COIN_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_SP_UPDATE",GM_ATTR_SP_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_SP_CHIP_UPDATE",GM_ATTR_SP_CHIP_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_SP_DIAMOND_UPDATE",GM_ATTR_SP_DIAMOND_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_HERO_LEVEL_UPDATE",GM_ATTR_HERO_LEVEL_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_PHYSICAL_ATTACK_UPDATE",GM_ATTR_PHYSICAL_ATTACK_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_MAGIC_ATTACK_UPDATE",GM_ATTR_MAGIC_ATTACK_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_SKILL_ATTACK_UPDATE",GM_ATTR_SKILL_ATTACK_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_PHYSICAL_DEFENCE_UPDATE",GM_ATTR_PHYSICAL_DEFENCE_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_MAGIC_DEFENCE_UPDATE",GM_ATTR_MAGIC_DEFENCE_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_SKILL_DEFENCE_UPDATE",GM_ATTR_SKILL_DEFENCE_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_HEALTH_POINT_UPDATE",GM_ATTR_HEALTH_POINT_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_ACCURATE_UPDATE",GM_ATTR_ACCURATE_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_DODGE_UPDATE",GM_ATTR_DODGE_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_WRECK_UPDATE",GM_ATTR_WRECK_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_PARRY_UPDATE",GM_ATTR_PARRY_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_CRITICAL_STRIKE_UPDATE",GM_ATTR_CRITICAL_STRIKE_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_TENACITY_UPDATE",GM_ATTR_TENACITY_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_SLAY_UPDATE",GM_ATTR_SLAY_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_SPEED_UPDATE",GM_ATTR_SPEED_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_PROFICIENCY_UPDATE",GM_ATTR_PROFICIENCY_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_ABILITY_ALL_UPDATE",GM_ATTR_ABILITY_ALL_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_COURAGE_UPDATE",GM_ATTR_COURAGE_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_CHARM_UPDATE",GM_ATTR_CHARM_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_TRICK_UPDATE",GM_ATTR_TRICK_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_STAMINA_UPDATE",GM_ATTR_STAMINA_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_REPUTATION_UPDATE",GM_ATTR_REPUTATION_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_EXP_UPDATE",GM_ATTR_EXP_UPDATE);
  tolua_constant(tolua_S,"GM_ATTR_EQUIP_LVUP_UESED_TIMES",GM_ATTR_EQUIP_LVUP_UESED_TIMES);
  tolua_constant(tolua_S,"GM_ATTR_EQUIP_LVUP_MAX_TIMES",GM_ATTR_EQUIP_LVUP_MAX_TIMES);
  tolua_constant(tolua_S,"GM_NETWORK_DISCONNCT",GM_NETWORK_DISCONNCT);
  tolua_constant(tolua_S,"GM_CLOSE_TALENTLAYER",GM_CLOSE_TALENTLAYER);
  tolua_constant(tolua_S,"GM_CLOSE_AUTOONHOOK",GM_CLOSE_AUTOONHOOK);
  tolua_constant(tolua_S,"GM_ATTR_PLAYER_EXPOLIT",GM_ATTR_PLAYER_EXPOLIT);
  tolua_constant(tolua_S,"GM_LUA_LAYER_CLOSE",GM_LUA_LAYER_CLOSE);
  tolua_constant(tolua_S,"GM_ATTR_PLAYER_EXPLOER_EXP",GM_ATTR_PLAYER_EXPLOER_EXP);
  tolua_constant(tolua_S,"GM_ATTR_GEM_RECAST",GM_ATTR_GEM_RECAST);
  tolua_constant(tolua_S,"GM_ATTR_PLAYER_GEM_ANIMA",GM_ATTR_PLAYER_GEM_ANIMA);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"USERINFO","USERINFO","",tolua_collect_USERINFO);
  #else
  tolua_cclass(tolua_S,"USERINFO","USERINFO","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"USERINFO");
   tolua_function(tolua_S,"new",tolua_LuaClient_USERINFO_new00);
   tolua_function(tolua_S,"new_local",tolua_LuaClient_USERINFO_new00_local);
   tolua_function(tolua_S,".call",tolua_LuaClient_USERINFO_new00_local);
   tolua_variable(tolua_S,"id",tolua_get_USERINFO_unsigned_id,tolua_set_USERINFO_unsigned_id);
   tolua_variable(tolua_S,"userSession",tolua_get_USERINFO_userSession,tolua_set_USERINFO_userSession);
   tolua_variable(tolua_S,"szName",tolua_get_USERINFO_szName,tolua_set_USERINFO_szName);
   tolua_variable(tolua_S,"ip",tolua_get_USERINFO_ip,tolua_set_USERINFO_ip);
   tolua_variable(tolua_S,"lastServerName",tolua_get_USERINFO_lastServerName,tolua_set_USERINFO_lastServerName);
   tolua_variable(tolua_S,"port",tolua_get_USERINFO_unsigned_port,tolua_set_USERINFO_unsigned_port);
   tolua_variable(tolua_S,"createdTime",tolua_get_USERINFO_createdTime,tolua_set_USERINFO_createdTime);
   tolua_variable(tolua_S,"tokenId",tolua_get_USERINFO_unsigned_tokenId,tolua_set_USERINFO_unsigned_tokenId);
   tolua_variable(tolua_S,"level",tolua_get_USERINFO_unsigned_level,tolua_set_USERINFO_unsigned_level);
   tolua_variable(tolua_S,"exp",tolua_get_USERINFO_unsigned_exp,tolua_set_USERINFO_unsigned_exp);
   tolua_variable(tolua_S,"mapId",tolua_get_USERINFO_unsigned_mapId,tolua_set_USERINFO_unsigned_mapId);
   tolua_variable(tolua_S,"xPos",tolua_get_USERINFO_unsigned_xPos,tolua_set_USERINFO_unsigned_xPos);
   tolua_variable(tolua_S,"yPos",tolua_get_USERINFO_unsigned_yPos,tolua_set_USERINFO_unsigned_yPos);
   tolua_variable(tolua_S,"orient",tolua_get_USERINFO_unsigned_orient,tolua_set_USERINFO_unsigned_orient);
   tolua_variable(tolua_S,"type",tolua_get_USERINFO_unsigned_type,tolua_set_USERINFO_unsigned_type);
   tolua_variable(tolua_S,"battleId",tolua_get_USERINFO_unsigned_battleId,tolua_set_USERINFO_unsigned_battleId);
   tolua_variable(tolua_S,"battleSide",tolua_get_USERINFO_unsigned_battleSide,tolua_set_USERINFO_unsigned_battleSide);
   tolua_variable(tolua_S,"m_spriteEnergy",tolua_get_USERINFO_unsigned_m_spriteEnergy,tolua_set_USERINFO_unsigned_m_spriteEnergy);
   tolua_variable(tolua_S,"m_gold",tolua_get_USERINFO_unsigned_m_gold,tolua_set_USERINFO_unsigned_m_gold);
   tolua_variable(tolua_S,"m_diamond",tolua_get_USERINFO_unsigned_m_diamond,tolua_set_USERINFO_unsigned_m_diamond);
   tolua_variable(tolua_S,"m_spriteChip",tolua_get_USERINFO_unsigned_m_spriteChip,tolua_set_USERINFO_unsigned_m_spriteChip);
   tolua_variable(tolua_S,"m_alchemyBagUnlockPos",tolua_get_USERINFO_unsigned_m_alchemyBagUnlockPos,tolua_set_USERINFO_unsigned_m_alchemyBagUnlockPos);
   tolua_variable(tolua_S,"m_alchemyStorageUnlockPos",tolua_get_USERINFO_unsigned_m_alchemyStorageUnlockPos,tolua_set_USERINFO_unsigned_m_alchemyStorageUnlockPos);
   tolua_variable(tolua_S,"m_gemRecastTimes",tolua_get_USERINFO_unsigned_m_gemRecastTimes,tolua_set_USERINFO_unsigned_m_gemRecastTimes);
   tolua_variable(tolua_S,"physical_attack",tolua_get_USERINFO_unsigned_physical_attack,tolua_set_USERINFO_unsigned_physical_attack);
   tolua_variable(tolua_S,"magic_attack",tolua_get_USERINFO_unsigned_magic_attack,tolua_set_USERINFO_unsigned_magic_attack);
   tolua_variable(tolua_S,"skill_attack",tolua_get_USERINFO_unsigned_skill_attack,tolua_set_USERINFO_unsigned_skill_attack);
   tolua_variable(tolua_S,"physical_defence",tolua_get_USERINFO_unsigned_physical_defence,tolua_set_USERINFO_unsigned_physical_defence);
   tolua_variable(tolua_S,"magic_defence",tolua_get_USERINFO_unsigned_magic_defence,tolua_set_USERINFO_unsigned_magic_defence);
   tolua_variable(tolua_S,"skill_defence",tolua_get_USERINFO_unsigned_skill_defence,tolua_set_USERINFO_unsigned_skill_defence);
   tolua_variable(tolua_S,"health_point",tolua_get_USERINFO_unsigned_health_point,tolua_set_USERINFO_unsigned_health_point);
   tolua_variable(tolua_S,"accurate",tolua_get_USERINFO_unsigned_accurate,tolua_set_USERINFO_unsigned_accurate);
   tolua_variable(tolua_S,"dodge",tolua_get_USERINFO_unsigned_dodge,tolua_set_USERINFO_unsigned_dodge);
   tolua_variable(tolua_S,"wreck",tolua_get_USERINFO_unsigned_wreck,tolua_set_USERINFO_unsigned_wreck);
   tolua_variable(tolua_S,"parry",tolua_get_USERINFO_unsigned_parry,tolua_set_USERINFO_unsigned_parry);
   tolua_variable(tolua_S,"critical_strike",tolua_get_USERINFO_unsigned_critical_strike,tolua_set_USERINFO_unsigned_critical_strike);
   tolua_variable(tolua_S,"tenacity",tolua_get_USERINFO_unsigned_tenacity,tolua_set_USERINFO_unsigned_tenacity);
   tolua_variable(tolua_S,"slay",tolua_get_USERINFO_unsigned_slay,tolua_set_USERINFO_unsigned_slay);
   tolua_variable(tolua_S,"proficiency",tolua_get_USERINFO_unsigned_proficiency,tolua_set_USERINFO_unsigned_proficiency);
   tolua_variable(tolua_S,"speed",tolua_get_USERINFO_unsigned_speed,tolua_set_USERINFO_unsigned_speed);
   tolua_variable(tolua_S,"total_hp",tolua_get_USERINFO_unsigned_total_hp,tolua_set_USERINFO_unsigned_total_hp);
   tolua_variable(tolua_S,"courage",tolua_get_USERINFO_unsigned_courage,tolua_set_USERINFO_unsigned_courage);
   tolua_variable(tolua_S,"charm",tolua_get_USERINFO_unsigned_charm,tolua_set_USERINFO_unsigned_charm);
   tolua_variable(tolua_S,"trick",tolua_get_USERINFO_unsigned_trick,tolua_set_USERINFO_unsigned_trick);
   tolua_variable(tolua_S,"effectiveness",tolua_get_USERINFO_unsigned_effectiveness,tolua_set_USERINFO_unsigned_effectiveness);
   tolua_variable(tolua_S,"m_player_exploit",tolua_get_USERINFO_unsigned_m_player_exploit,tolua_set_USERINFO_unsigned_m_player_exploit);
   tolua_variable(tolua_S,"m_playerExploerExperience",tolua_get_USERINFO_unsigned_m_playerExploerExperience,tolua_set_USERINFO_unsigned_m_playerExploerExperience);
   tolua_variable(tolua_S,"m_playerGemAnima",tolua_get_USERINFO_unsigned_m_playerGemAnima,tolua_set_USERINFO_unsigned_m_playerGemAnima);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UserData","UserData","",NULL);
  tolua_beginmodule(tolua_S,"UserData");
   tolua_function(tolua_S,"Get",tolua_LuaClient_UserData_Get00);
   tolua_function(tolua_S,"getUserId",tolua_LuaClient_UserData_getUserId00);
   tolua_function(tolua_S,"getHeroHp",tolua_LuaClient_UserData_getHeroHp00);
   tolua_function(tolua_S,"getHeroTotalHp",tolua_LuaClient_UserData_getHeroTotalHp00);
   tolua_function(tolua_S,"GetUserType",tolua_LuaClient_UserData_GetUserType00);
   tolua_function(tolua_S,"GetUserInfo",tolua_LuaClient_UserData_GetUserInfo00);
   tolua_function(tolua_S,"GetUserLevel",tolua_LuaClient_UserData_GetUserLevel00);
   tolua_function(tolua_S,"GetUserInfo",tolua_LuaClient_UserData_GetUserInfo01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"NotificationCenter","NotificationCenter","",NULL);
  tolua_beginmodule(tolua_S,"NotificationCenter");
   tolua_function(tolua_S,"defaultCenter",tolua_LuaClient_NotificationCenter_defaultCenter00);
   tolua_function(tolua_S,"registerScriptObserver",tolua_LuaClient_NotificationCenter_registerScriptObserver00);
   tolua_function(tolua_S,"unregisterScriptObserver",tolua_LuaClient_NotificationCenter_unregisterScriptObserver00);
   tolua_function(tolua_S,"unregisterAllScriptObservers",tolua_LuaClient_NotificationCenter_unregisterAllScriptObservers00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameManager","GameManager","",NULL);
  tolua_beginmodule(tolua_S,"GameManager");
   tolua_function(tolua_S,"Get",tolua_LuaClient_GameManager_Get00);
   tolua_function(tolua_S,"GetSceneLayer",tolua_LuaClient_GameManager_GetSceneLayer00);
   tolua_function(tolua_S,"getHero",tolua_LuaClient_GameManager_getHero00);
   tolua_function(tolua_S,"setHero",tolua_LuaClient_GameManager_setHero00);
   tolua_function(tolua_S,"getHeroTypeId",tolua_LuaClient_GameManager_getHeroTypeId00);
   tolua_function(tolua_S,"setHeroTypeId",tolua_LuaClient_GameManager_setHeroTypeId00);
   tolua_function(tolua_S,"changeMap",tolua_LuaClient_GameManager_changeMap00);
   tolua_function(tolua_S,"goToSplash",tolua_LuaClient_GameManager_goToSplash00);
   tolua_function(tolua_S,"goToFrontend",tolua_LuaClient_GameManager_goToFrontend00);
   tolua_function(tolua_S,"startGame",tolua_LuaClient_GameManager_startGame00);
   tolua_function(tolua_S,"exitGame",tolua_LuaClient_GameManager_exitGame00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"SkillUIManager","SkillUIManager","",NULL);
  tolua_beginmodule(tolua_S,"SkillUIManager");
   tolua_function(tolua_S,"getInstance",tolua_LuaClient_SkillUIManager_getInstance00);
   tolua_function(tolua_S,"ResetValue",tolua_LuaClient_SkillUIManager_ResetValue00);
   tolua_function(tolua_S,"sendGetUserSkillReqMessage",tolua_LuaClient_SkillUIManager_sendGetUserSkillReqMessage00);
   tolua_function(tolua_S,"sendAddUserSkillReqMessage",tolua_LuaClient_SkillUIManager_sendAddUserSkillReqMessage00);
   tolua_function(tolua_S,"sendUserSkillDiffReqMessage",tolua_LuaClient_SkillUIManager_sendUserSkillDiffReqMessage00);
   tolua_function(tolua_S,"sendSetSlotAttributeMessage",tolua_LuaClient_SkillUIManager_sendSetSlotAttributeMessage00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ElfExploreManger","ElfExploreManger","",tolua_collect_ElfExploreManger);
  #else
  tolua_cclass(tolua_S,"ElfExploreManger","ElfExploreManger","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ElfExploreManger");
   tolua_function(tolua_S,"new",tolua_LuaClient_ElfExploreManger_new00);
   tolua_function(tolua_S,"new_local",tolua_LuaClient_ElfExploreManger_new00_local);
   tolua_function(tolua_S,".call",tolua_LuaClient_ElfExploreManger_new00_local);
   tolua_function(tolua_S,"Get",tolua_LuaClient_ElfExploreManger_Get00);
   tolua_function(tolua_S,"Destroy",tolua_LuaClient_ElfExploreManger_Destroy00);
   tolua_function(tolua_S,"ResetValue",tolua_LuaClient_ElfExploreManger_ResetValue00);
   tolua_function(tolua_S,"SendExchangeElfReq",tolua_LuaClient_ElfExploreManger_SendExchangeElfReq00);
   tolua_function(tolua_S,"SendExploreReq",tolua_LuaClient_ElfExploreManger_SendExploreReq00);
   tolua_function(tolua_S,"SendExploreDetermineReq",tolua_LuaClient_ElfExploreManger_SendExploreDetermineReq00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MainMenuLayer","MainMenuLayer","",NULL);
  tolua_beginmodule(tolua_S,"MainMenuLayer");
   tolua_function(tolua_S,"setChatToolbar",tolua_LuaClient_MainMenuLayer_setChatToolbar00);
   tolua_function(tolua_S,"getMainMenuLayer",tolua_LuaClient_MainMenuLayer_getMainMenuLayer00);
   tolua_function(tolua_S,"GetNumByFormat",tolua_LuaClient_MainMenuLayer_GetNumByFormat00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameAudioManager","GameAudioManager","",NULL);
  tolua_beginmodule(tolua_S,"GameAudioManager");
   tolua_function(tolua_S,"sharedManager",tolua_LuaClient_GameAudioManager_sharedManager00);
   tolua_function(tolua_S,"playEffect",tolua_LuaClient_GameAudioManager_playEffect00);
   tolua_function(tolua_S,"stopAllEffect",tolua_LuaClient_GameAudioManager_stopAllEffect00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ParticleManagerX","ParticleManagerX","",NULL);
  tolua_beginmodule(tolua_S,"ParticleManagerX");
   tolua_function(tolua_S,"sharedManager",tolua_LuaClient_ParticleManagerX_sharedManager00);
   tolua_function(tolua_S,"getParticles",tolua_LuaClient_ParticleManagerX_getParticles00);
   tolua_function(tolua_S,"getParticles_uieffect",tolua_LuaClient_ParticleManagerX_getParticles_uieffect00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ITEMATTR","ITEMATTR","",NULL);
  tolua_beginmodule(tolua_S,"ITEMATTR");
   tolua_variable(tolua_S,"attr_key",tolua_get_ITEMATTR_unsigned_attr_key,tolua_set_ITEMATTR_unsigned_attr_key);
   tolua_variable(tolua_S,"attr_basic_value",tolua_get_ITEMATTR_unsigned_attr_basic_value,tolua_set_ITEMATTR_unsigned_attr_basic_value);
   tolua_variable(tolua_S,"attr_intensify_value",tolua_get_ITEMATTR_unsigned_attr_intensify_value,tolua_set_ITEMATTR_unsigned_attr_intensify_value);
   tolua_variable(tolua_S,"attr_gem_value",tolua_get_ITEMATTR_unsigned_attr_gem_value,tolua_set_ITEMATTR_unsigned_attr_gem_value);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"kItemBag",kItemBag);
  tolua_constant(tolua_S,"kItemStorage",kItemStorage);
  tolua_constant(tolua_S,"kItemHeroEquip",kItemHeroEquip);
  tolua_constant(tolua_S,"kItemFairyEquip",kItemFairyEquip);
  tolua_constant(tolua_S,"kAlchemyBag",kAlchemyBag);
  tolua_constant(tolua_S,"kAlchemyStorage",kAlchemyStorage);
  tolua_constant(tolua_S,"kAlchemyHeroEquip",kAlchemyHeroEquip);
  tolua_constant(tolua_S,"kAlchemyFairyEquip",kAlchemyFairyEquip);
  tolua_cclass(tolua_S,"BackPackItem","BackPackItem","",NULL);
  tolua_beginmodule(tolua_S,"BackPackItem");
   tolua_function(tolua_S,"getItemInfo",tolua_LuaClient_BackPackItem_getItemInfo00);
   tolua_function(tolua_S,"getItemId",tolua_LuaClient_BackPackItem_getItemId00);
   tolua_variable(tolua_S,"isLocked",tolua_get_BackPackItem_isLocked,tolua_set_BackPackItem_isLocked);
   tolua_variable(tolua_S,"isEmpty",tolua_get_BackPackItem_isEmpty,tolua_set_BackPackItem_isEmpty);
   tolua_variable(tolua_S,"position",tolua_get_BackPackItem_unsigned_position,tolua_set_BackPackItem_unsigned_position);
   tolua_variable(tolua_S,"amount",tolua_get_BackPackItem_unsigned_amount,tolua_set_BackPackItem_unsigned_amount);
   tolua_variable(tolua_S,"itemLevel",tolua_get_BackPackItem_unsigned_itemLevel,tolua_set_BackPackItem_unsigned_itemLevel);
   tolua_variable(tolua_S,"m_equipInfo",tolua_get_BackPackItem_m_equipInfo_ptr,tolua_set_BackPackItem_m_equipInfo_ptr);
   tolua_variable(tolua_S,"packType",tolua_get_BackPackItem_unsigned_packType,tolua_set_BackPackItem_unsigned_packType);
   tolua_variable(tolua_S,"m_spriteInfo",tolua_get_BackPackItem_m_spriteInfo_ptr,tolua_set_BackPackItem_m_spriteInfo_ptr);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ItemManager","ItemManager","",NULL);
  tolua_beginmodule(tolua_S,"ItemManager");
   tolua_function(tolua_S,"Get",tolua_LuaClient_ItemManager_Get00);
   tolua_function(tolua_S,"findItemByPos",tolua_LuaClient_ItemManager_findItemByPos00);
   tolua_function(tolua_S,"getIconSpriteById",tolua_LuaClient_ItemManager_getIconSpriteById00);
   tolua_function(tolua_S,"getIconFrame",tolua_LuaClient_ItemManager_getIconFrame00);
   tolua_function(tolua_S,"getLabelColorByQuality",tolua_LuaClient_ItemManager_getLabelColorByQuality00);
   tolua_function(tolua_S,"getItemNumberById",tolua_LuaClient_ItemManager_getItemNumberById00);
   tolua_function(tolua_S,"getAttributionText",tolua_LuaClient_ItemManager_getAttributionText00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ItemBase","ItemBase","",NULL);
  tolua_beginmodule(tolua_S,"ItemBase");
   tolua_function(tolua_S,"getEquipLevel",tolua_LuaClient_ItemBase_getEquipLevel00);
   tolua_variable(tolua_S,"m_id",tolua_get_ItemBase_unsigned_m_id,tolua_set_ItemBase_unsigned_m_id);
   tolua_variable(tolua_S,"m_name",tolua_get_ItemBase_m_name,tolua_set_ItemBase_m_name);
   tolua_variable(tolua_S,"b_isPiledUp",tolua_get_ItemBase_b_isPiledUp,tolua_set_ItemBase_b_isPiledUp);
   tolua_variable(tolua_S,"m_maxPiledNum",tolua_get_ItemBase_unsigned_m_maxPiledNum,tolua_set_ItemBase_unsigned_m_maxPiledNum);
   tolua_array(tolua_S,"m_source",tolua_get_LuaClient_ItemBase_m_source,tolua_set_LuaClient_ItemBase_m_source);
   tolua_variable(tolua_S,"m_byeprice",tolua_get_ItemBase_unsigned_m_byeprice,tolua_set_ItemBase_unsigned_m_byeprice);
   tolua_variable(tolua_S,"m_sellprice",tolua_get_ItemBase_unsigned_m_sellprice,tolua_set_ItemBase_unsigned_m_sellprice);
   tolua_variable(tolua_S,"m_requiredLevel",tolua_get_ItemBase_unsigned_m_requiredLevel,tolua_set_ItemBase_unsigned_m_requiredLevel);
   tolua_variable(tolua_S,"m_type",tolua_get_ItemBase_unsigned_m_type,tolua_set_ItemBase_unsigned_m_type);
   tolua_variable(tolua_S,"b_Destroyed",tolua_get_ItemBase_b_Destroyed,tolua_set_ItemBase_b_Destroyed);
   tolua_variable(tolua_S,"m_szDescription",tolua_get_ItemBase_m_szDescription,tolua_set_ItemBase_m_szDescription);
   tolua_variable(tolua_S,"m_quality",tolua_get_ItemBase_unsigned_m_quality,tolua_set_ItemBase_unsigned_m_quality);
   tolua_variable(tolua_S,"m_szInlayHole",tolua_get_ItemBase_m_szInlayHole,tolua_set_ItemBase_m_szInlayHole);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EquipmentItem","EquipmentItem","ItemBase",NULL);
  tolua_beginmodule(tolua_S,"EquipmentItem");
   tolua_variable(tolua_S,"m_ownerType",tolua_get_EquipmentItem_unsigned_m_ownerType,tolua_set_EquipmentItem_unsigned_m_ownerType);
   tolua_variable(tolua_S,"m_equipPart",tolua_get_EquipmentItem_unsigned_m_equipPart,tolua_set_EquipmentItem_unsigned_m_equipPart);
   tolua_variable(tolua_S,"m_equipLevel",tolua_get_EquipmentItem_unsigned_m_equipLevel,tolua_set_EquipmentItem_unsigned_m_equipLevel);
   tolua_variable(tolua_S,"m_attribute",tolua_get_EquipmentItem_m_attribute,tolua_set_EquipmentItem_m_attribute);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"TIMER_INSTANCE_COUNTDOWN",TIMER_INSTANCE_COUNTDOWN);
  tolua_constant(tolua_S,"TIMER_PVAI_COOLDOWN",TIMER_PVAI_COOLDOWN);
  tolua_constant(tolua_S,"TIMER_PVAI_REWARD",TIMER_PVAI_REWARD);
  tolua_cclass(tolua_S,"TimeManager","TimeManager","",NULL);
  tolua_beginmodule(tolua_S,"TimeManager");
   tolua_function(tolua_S,"Get",tolua_LuaClient_TimeManager_Get00);
   tolua_function(tolua_S,"getCurServerTime",tolua_LuaClient_TimeManager_getCurServerTime00);
   tolua_function(tolua_S,"secondsToString",tolua_LuaClient_TimeManager_secondsToString00);
   tolua_function(tolua_S,"registerLuaTimer",tolua_LuaClient_TimeManager_registerLuaTimer00);
   tolua_function(tolua_S,"unregisterLuaTimer",tolua_LuaClient_TimeManager_unregisterLuaTimer00);
   tolua_function(tolua_S,"attachLuaTimer",tolua_LuaClient_TimeManager_attachLuaTimer00);
   tolua_function(tolua_S,"startTimer",tolua_LuaClient_TimeManager_startTimer00);
   tolua_function(tolua_S,"stopTimer",tolua_LuaClient_TimeManager_stopTimer00);
   tolua_function(tolua_S,"renewTimer",tolua_LuaClient_TimeManager_renewTimer00);
   tolua_function(tolua_S,"hasTimer",tolua_LuaClient_TimeManager_hasTimer00);
   tolua_function(tolua_S,"hasLuaObserver",tolua_LuaClient_TimeManager_hasLuaObserver00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GemStonesFromLua","GemStonesFromLua","",NULL);
  tolua_beginmodule(tolua_S,"GemStonesFromLua");
   tolua_function(tolua_S,"getInstance",tolua_LuaClient_GemStonesFromLua_getInstance00);
   tolua_function(tolua_S,"EquipInlayGemReq",tolua_LuaClient_GemStonesFromLua_EquipInlayGemReq00);
   tolua_function(tolua_S,"GemRecastReq",tolua_LuaClient_GemStonesFromLua_GemRecastReq00);
   tolua_function(tolua_S,"GemAnimaExchangeReq",tolua_LuaClient_GemStonesFromLua_GemAnimaExchangeReq00);
   tolua_function(tolua_S,"GemHoleUnlockReq",tolua_LuaClient_GemStonesFromLua_GemHoleUnlockReq00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PvAIManager","PvAIManager","",NULL);
  tolua_beginmodule(tolua_S,"PvAIManager");
   tolua_function(tolua_S,"Get",tolua_LuaClient_PvAIManager_Get00);
   tolua_function(tolua_S,"sendPvAIReq",tolua_LuaClient_PvAIManager_sendPvAIReq00);
   tolua_function(tolua_S,"sendPvAIInfoReq",tolua_LuaClient_PvAIManager_sendPvAIInfoReq00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TutorialsManager","TutorialsManager","",NULL);
  tolua_beginmodule(tolua_S,"TutorialsManager");
   tolua_function(tolua_S,"Get",tolua_LuaClient_TutorialsManager_Get00);
   tolua_function(tolua_S,"StartOneTutorial",tolua_LuaClient_TutorialsManager_StartOneTutorial00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LuaClient (lua_State* tolua_S) {
 return tolua_LuaClient_open(tolua_S);
};
#endif

