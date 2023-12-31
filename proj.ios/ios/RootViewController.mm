/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"


@implementation RootViewController

- (void)loadView {
  CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                       pixelFormat: (__bridge NSString *)cocos2d::GLViewImpl::_pixelFormat
                                       depthFormat: cocos2d::GLViewImpl::_depthFormat
                                preserveBackbuffer: NO
                                        sharegroup: nil
                                     multiSampling: cocos2d::GLViewImpl::_multisamplingCount > 0 ? YES : NO
                                   numberOfSamples: cocos2d::GLViewImpl::_multisamplingCount ];
  
  [eaglView setMultipleTouchEnabled:NO];
  
  self.view = eaglView;
}

- (void)viewDidLoad {
  [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated {
  [super viewWillAppear:animated];
}

- (void)viewDidDisappear:(BOOL)animated {
  [super viewDidDisappear:animated];
}

- (BOOL) shouldAutorotate { return YES; }

- (BOOL)prefersStatusBarHidden { return NO; }

- (UIStatusBarStyle)preferredStatusBarStyle { return UIStatusBarStyleLightContent; }

- (BOOL)prefersHomeIndicatorAutoHidden { return NO; }

-(UIRectEdge)preferredScreenEdgesDeferringSystemGestures { return UIRectEdgeBottom; }

- (void)didReceiveMemoryWarning { [super didReceiveMemoryWarning]; }

@end
