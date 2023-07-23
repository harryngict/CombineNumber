//
//  NativeSystemSound.m
//  CombineNumber
//
//  Created by Hoang Nguyen on 23/7/23.
//

#import <Foundation/Foundation.h>
#import "NativeSystemSound.h"

@interface NativeSystemSound()
@end

@implementation NativeSystemSound

+ (NativeSystemSound*)sharedInstance {
  static NativeSystemSound* sManager = nil;
  @synchronized (self) {
    if (sManager == nil) {
      sManager = [[self alloc] init];
    }
  }
  return sManager;
}

- (void)playHaptic {
  if (@available(iOS 10.0, *)) {
    UIImpactFeedbackGenerator* generator = [[UIImpactFeedbackGenerator alloc] initWithStyle:UIImpactFeedbackStyleMedium];
    [generator impactOccurred];
  }
}

@end
