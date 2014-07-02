//
//  TaomeeLogin.h
//  TaomeeLogin
//
//  Created by Delle on 12-11-12.
//  Copyright (c) 2012年 Taomee Inc. All rights reserved.
//
// Required frameworks
// 1) CoreGraphics.framework
// 2) SystemConfiguration.framework
// 3) UIKit.framework
// 4) Foundation.framework

/***
 //  Version : V 1.0.0 init 
 //  Version : V 1.0.1 
 ***/

// 0x00 HI ME LO
// 00   01 00 01
#define TAOMEE_LOGIN_VERSION 0x010000

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol TaomeeLoginDelegate <NSObject>

@optional

/**
 *  @brief     登陆成功，返回米米号
 *  @param[in] userId ，米米号
 *  @param[in] session
 *  @param[in] nickName, 用户昵称
 *  @param[in] url, 头像的url
 *  @param[in] channel, 登录的渠道
 */
- (void)didLoginWithUserId:(NSString *)userId 
                   session:(NSString *)session 
                  nickName:(NSString *)nickName 
                    picUrl:(NSString *)url 
           andLoginChannel:(NSString *)channel;

/**
 *  @brief     登陆失败
 *  @param[in] error, 错误信息
 *  @param[in] channle, 登录的渠道
 */
- (void)loginDidFailWithError:(NSError *)error withLoginChannel:(NSString *)channel;

/**
 *  @brief 腾讯微博分享成功
 */
- (void)TcShareSucc;

/**
 *  @brief 腾讯微博分享失败
 */
- (void)TcShareFailed;

/**
 *  @brief 腾讯微博分享取消
 */
- (void)TcShareCancel;

@end

@protocol sinaWeiboShareDelegate <NSObject>

@optional

/**
 *  @brief 微博分享成功
 */
- (void)shareSucc;

/**
 *  @brief 微博分享失败
 */
- (void)shareFailed;

/**
 *  @brief 取消微博分享
 */
- (void)shareCancel;

/**
 * @brief 取消登录
 */
- (void)loginCancel;

@end

@interface TaomeeLogin : NSObject{
    id<sinaWeiboShareDelegate> delegate_;
}
@property (nonatomic, assign)id<sinaWeiboShareDelegate>delegate;

+ (TaomeeLogin *)sharedInstance;

+ (void)purgeSharedInstance;

/**
 *  @brief 初始化登录渠道号和游戏id
 */
+ (void)initGameChannel:(int)gameChannel andGameId:(int)gameId;

/**
 *  @brief     初始化新浪微博
 *  @param[in] appKey, 应用的appKey
 *  @param[in] appSecrect, 应用的appSecret
 *  @param[in] redirectURL, 应用的回调页面
 */
+ (void)initSinaWeiboWithAppKey:(NSString *)appKey 
                      appSecret:(NSString *)appSecret
                 appRedirectURL:(NSString *)redirectURL;

/**
 *  @brief     初始化腾讯微博
 *  @param[in] appKey, 应用的appKey
 *  @param[in] appSecrect, 应用的appSecret
 *  @param[in] redirectURL, 应用的回调页面
 */
+ (void)initTencentWeiboWithAppKey:(NSString *)appKey 
                         appSecret:(NSString *)appSecret 
                 andAppRedirectURL:(NSString *)redirectURL;

/**
 *  @brief     登录
 *  @param[in] rvc,当前的view controller
 *  @param[in] delegate,回调所用
 */
- (void)loginWithRootViewController:(UIViewController *)rvc andDelegate:(id)delegate;

/**
 *  @brief 退出登录
 *  @param[in] rvc,当前的view controller
 *  @param[in] delegate,回调所用
 */
- (void)logoutWithRootViewController:(UIViewController *)rvc andDelegate:(id)delegate;

/**
 *  @brief     新浪微博图片分享
 *  @param[in] image, 分享的图片
 *  @param[in] desc, 图片的描述
 *  @param[in] delegate,回调所用的delegate
 */
- (void)shareImage:(UIImage *)image 
              desc:(NSString *)desc 
withRootViewController:(UIViewController *)rvc 
       andDelegate:(id)delegate;

/** 
 *  @brief 获取微博头像连接
 */
+ (NSString *)getAvartarUrl;

/**
 *  @brief  腾讯微博分享
 *  @param  image, 微博图片
 *  @param  content, 微博文字内容
 *  @param[in] delegate,回调所用的delegate
 */
- (void)tencentShareImage:(UIImage *)image 
             weiboContent:(NSString *)content 
   withRootViewController:(UIViewController *)rvc 
              andDelegate:(id)delegate;

/**
 *  @brief 打开内网测试模式(YES, 为内网，NO, 为外网。默认为外网.)
 */
+ (void)isInnerTest:(BOOL)isInner;

@end
