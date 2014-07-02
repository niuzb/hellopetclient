@echo off

cls
rem current path
set DIR=%cd%

cd ..
set COCOS2DX_ROOT=%cd%
set APP_ANDROID_ROOT=%DIR%
cd %DIR%
set COCOS2DX_ROOT=%COCOS2DX_ROOT:\=/% 
set COCOS2DX_ROOT=%COCOS2DX_ROOT: =%

set APP_ANDROID_ROOT=%APP_ANDROID_ROOT:\=/% 
echo %1

%1 -C %APP_ANDROID_ROOT% NDK_MODULE_PATH=%COCOS2DX_ROOT%