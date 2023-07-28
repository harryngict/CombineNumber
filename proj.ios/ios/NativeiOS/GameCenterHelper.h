//
//  GameCenterHelper.h
//  CombineNumber
//
//  Created by Hoang Nguyen on 28/7/23.
//

#ifndef GameCenterHelper_h
#define GameCenterHelper_h

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
#import "GameCenterHelper.h"

@interface GameCenterHelper: NSObject<GKGameCenterControllerDelegate>
+ (GameCenterHelper*)sharedInstance;
- (void)authenticatePlayerWithCompletionHandler:(void (^)(BOOL success, NSError *error))completionHandler;
- (void)showLeaderboard;
- (void)reportScore:(int64_t)score;
@end

#endif /* GameCenterHelper_h */
