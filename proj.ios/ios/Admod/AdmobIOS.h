//
//  AdmobIOS.h
//  Combine Number
//
//  Created by Harry Nguyen on 15/7/23.
//

#ifndef AdmobIOS_h
#define AdmobIOS_h

#import <Foundation/Foundation.h>

@interface AdmobIOS: NSObject
@property (nonatomic, strong) NSString* bannerId;
@property (nonatomic, strong) NSString* interstitialId;
@property (nonatomic, copy) void (^completionHandler)(BOOL finished);

+ (AdmobIOS*)sharedAdmob;

- (void)showBanner;
- (void)loadInterstitial :(void (^)(BOOL finished))completionHandler;
- (void)showInterstitial :(void (^)(BOOL finished))completionHandler;
@end


#endif /* AdmobIOS_h */
