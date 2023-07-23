//
//  NativeSystemSound.h
//  CombineNumber
//
//  Created by Hoang Nguyen on 23/7/23.
//

#ifndef NativeSystemSound_h
#define NativeSystemSound_h

#import <Foundation/Foundation.h>

@interface NativeSystemSound: NSObject
+ (NativeSystemSound*)sharedInstance;
- (void)playHaptic;
@end

#endif /* NativeSystemSound_h */
