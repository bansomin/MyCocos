//
//  TestViewController.h
//  photo
//
//  Created by HAO on 17-8-25.
//  Copyright (c) 2017年 HAO. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TestViewController : UIViewController<UITextViewDelegate, UIActionSheetDelegate, UINavigationControllerDelegate, UIImagePickerControllerDelegate>{
    
    //下拉菜单
    UIActionSheet *actionSheet;
    //图片
    NSString *imgPath;
}

@end
