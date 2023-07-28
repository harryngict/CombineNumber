//
//  GameCenterHelper.m
//  CombineNumber
//
//  Created by Hoang Nguyen on 28/7/23.
//

#import <Foundation/Foundation.h>
#import "GameCenterHelper.h"

#define LEADERBOARD_ID          @"com.boring.combinenumber.leaderboard"

@interface GameCenterHelper()
@end

@implementation GameCenterHelper

+ (GameCenterHelper*)sharedInstance {
  static GameCenterHelper* sManager = nil;
  @synchronized (self) {
    if (sManager == nil) { sManager = [[self alloc] init]; }
  }
  return sManager;
}

- (void)authenticatePlayerWithCompletionHandler:(void (^)(BOOL success, NSError *error))completionHandler {
  GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
  [localPlayer setAuthenticateHandler:^(UIViewController * _Nullable viewController, NSError * _Nullable error) {
    if (viewController) {
      [[[[UIApplication sharedApplication] keyWindow] rootViewController] presentViewController:viewController animated:YES completion:nil];
      completionHandler(NO, nil);
    } else if (localPlayer.isAuthenticated) {
      completionHandler(YES, nil);
    } else {
      completionHandler(NO, error);
    }
  }];
}

-(void)displayLeaderboard {
  GKGameCenterViewController *viewController = [[GKGameCenterViewController alloc] init];
  if (viewController) {
    viewController.gameCenterDelegate = self;
    viewController.leaderboardIdentifier = LEADERBOARD_ID;
    viewController.viewState = GKGameCenterViewControllerStateLeaderboards;
    [[[[UIApplication sharedApplication] keyWindow] rootViewController] presentViewController:viewController animated:YES completion:nil];
  }
}

- (void)showLeaderboard {
  GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
  if (localPlayer.isAuthenticated) {
    [self displayLeaderboard];
  } else {
    [self authenticatePlayerWithCompletionHandler:^(BOOL success, NSError *error) {
      if (success) {
        [self displayLeaderboard];
      }
    }];
  }
}

-(void)sumitScoreToLeaderboard:(int64_t)score {
  GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier: LEADERBOARD_ID];
  scoreReporter.value = score;
  [GKScore reportScores:@[scoreReporter] withCompletionHandler:^(NSError * _Nullable error) {}];
}

- (void)reportScore:(int64_t)score {
  GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
  if (localPlayer.isAuthenticated) {
    [self sumitScoreToLeaderboard:score];
  } else {
    [self authenticatePlayerWithCompletionHandler:^(BOOL success, NSError *error) {
      if(success) {
        [self sumitScoreToLeaderboard:score];
      }
    }];
  }
}

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController {
  [[[[UIApplication sharedApplication] keyWindow] rootViewController] dismissViewControllerAnimated:YES completion:nil];
}
@end
