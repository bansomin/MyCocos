//
//  TestViewController.m
//  photo
//
//  Created by HAO on 17-8-25.
//  Copyright (c) 2017年 HAO. All rights reserved.
//

#import "TestViewController.h"

@interface TestViewController()

@end

@implementation TestViewController

-(void) viewDidLoad{
    
    [super viewDidLoad];
    
    //导航栏
    self.navigationController.title = @"PhotoTest";
    self.navigationItem.rightBarButtonItem = [[[UIBarButtonItem alloc]
                                               initWithTitle:@"发送"
                                               style:UIBarButtonItemStyleDone
                                               target:self
                                               action:@selector(sendInfo)]
                                              autorelease];
    
    
    //菜单按钮
    UIImage* image = [[UIImage alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"camera" ofType:@"png"]];
    
    UIButton* btn = [UIButton buttonWithType:UIButtonTypeCustom];
    
    btn.frame = CGRectMake(0, 120, image.size.width, image.size.height);
    
    [btn setImage:image forState:UIControlStateNormal];
    
    [btn addTarget:self action:@selector(openMenu) forControlEvents:UIControlEventTouchUpInside];
    
    [self.view addSubview:btn];    
}

-(void)viewDidUnload {
    
    [super viewDidUnload];
}

-(void) sendInfo{
    NSLog(@"sendInfo");
    
    NSLog(@"图片路径: %@", imgPath);
}

-(void) openMenu{
     NSLog(@"openMenu");
    
    actionSheet = [[UIActionSheet alloc]
                   initWithTitle:nil
                   delegate:self
                   cancelButtonTitle:@"取消"
                   destructiveButtonTitle:nil
                   otherButtonTitles:@"打开图库", @"打开相机", nil];
    [actionSheet showInView:self.view];
    [actionSheet release];
}

-(void) actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex{
    
    if (buttonIndex==actionSheet.cancelButtonIndex) {
        NSLog(@"用户取消");
    }
    
    switch (buttonIndex) {
        case 0:
            [self openGallery];
            break;
        case 1:
            [self takePhoto];
            break;
        default:
            break;
    }
}

-(void) openGallery{
    NSLog(@"openGallery");
    
    UIImagePickerController* picker = [[UIImagePickerController alloc] init];
    
    picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    
    picker.delegate = self;
    
    //设置选择图片后可被编辑
    picker.allowsEditing = YES;
    
    [self presentViewController:picker animated:YES completion:nil];
    
    [picker release];
}

-(void) takePhoto{
    NSLog(@"takePhoto");
    
    UIImagePickerControllerSourceType sourceType = UIImagePickerControllerSourceTypeCamera;
    
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
        
        UIImagePickerController* picker = [[UIImagePickerController alloc] init];
        picker.delegate = self;
        picker.allowsEditing = YES;
        picker.sourceType = sourceType;
        [picker release];
        [self presentViewController:picker animated:YES completion:nil];
    }else{
        NSLog(@"无法打开相机");
    }
}

//选择图片后的回调
-(void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    
    NSString* type = [info objectForKey:UIImagePickerControllerMediaType];
    //选择的类型是图片
    if ([type isEqualToString:@"public.image"]) {
        
        //先把图片转成NSData
        UIImage* image = [info objectForKey:@"UIImagePickerControllerEditedImage"];     //裁剪 //UIImagePickerControllerOriginalImage
        NSData* data;
        
        if (UIImagePNGRepresentation(image) == nil) {
            data = UIImageJPEGRepresentation(image, 1.0);
        }else{
            data = UIImagePNGRepresentation(image);
        }
        
        //图片保存路径
        //将图片放到沙盒的documents文件中
        NSString* documentPath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
        //获取当前时间
        NSDate* curDate = [NSDate date];
        NSDateFormatter* format = [[NSDateFormatter alloc] init];
        [format setDateFormat:@"yyyMMddHHmmss"];
        NSString* curStr = [format stringFromDate:curDate];
        NSString* fileName = [[NSString alloc]initWithFormat:@"%@%@%@", @"/", curStr, @".png"];
        NSLog(@"%@", fileName);

        
        //文件管理器
        NSFileManager* fileMgr  = [NSFileManager defaultManager];
        
        //data对象拷贝到沙盒中，保存为image.png
        [fileMgr createDirectoryAtPath:documentPath withIntermediateDirectories:YES attributes:nil error:nil];
        [fileMgr createFileAtPath:[documentPath stringByAppendingString:fileName] contents:data attributes:nil];
        
        //得到选择后沙盒中图片的完整路径
        imgPath = [[NSString alloc]initWithFormat:@"%@%@", documentPath, fileName];
        NSLog(@"%@", image);
        
        //关闭相册界面
        [picker dismissViewControllerAnimated:YES completion:nil];
        
        //创建缩略图
        UIImageView* smallView = [[[UIImageView alloc] initWithFrame:CGRectMake(50, 120, 50, 50)] autorelease];
        
        smallView.image = image;
        
        //加载视图中
        [self.view addSubview:smallView];
    }
}

//用户取消后回调
-(void) imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    
    NSLog(@"用户取消了操作...");
    //关闭相册界面
    [picker dismissViewControllerAnimated:YES completion:nil];
}


@end














