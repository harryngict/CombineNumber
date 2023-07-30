//
//  HapticEngine.h
//  CombineNumber
//
//  Created by Hoang Nguyen on 23/7/23.
//

#ifndef HapticEngine_h
#define HapticEngine_h

#import <Foundation/Foundation.h>

@interface HapticEngine: NSObject
+ (HapticEngine*)sharedInstance;
- (void)playHaptic;
@end

#endif /* HapticEngine_h */
