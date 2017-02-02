package com.hao.ThirdPartyDemo;

/**
 * Created by HAO on 2016/12/28.
 *
 * 配置各个平台的appkey
 */

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;

import com.umeng.socialize.Config;
import com.umeng.socialize.PlatformConfig;
import com.umeng.socialize.UMShareAPI;

public class App extends Application{

    @Override
    public void onCreate() {
        super.onCreate();
        //开启debug模式，方便定位错误，具体错误检查方式可以查看http://dev.umeng.com/social/android/quick-integration的报错必看，正式发布，请关闭该模式
        Config.DEBUG = true;
        UMShareAPI.get(this);
    }

    //各个平台的配置，建议放在全局Application或者程序入口
    {
        //QQ
        //PlatformConfig.setQQZone("100424468", "c7394704798a158208a74ab60104f0ba");    //友盟社会化组件
        PlatformConfig.setQQZone("1105918566", "o1LUYlTS4MLrpTV3");   //我的腾讯平台
        //微信
        PlatformConfig.setWeixin("wx1942b0160dfb7f9f", "4fdc75440368df49430368166f24487a"); //我的微信
        //微博
        //PlatformConfig.setSinaWeibo("3921700954", "04b48b094faeb16683c32669824ebdad");
        PlatformConfig.setSinaWeibo("19218166", "726dfe6a1aa33d30026c5660246fd756");
        //Twitter
        PlatformConfig.setTwitter("3aIN7fuF685MuZ7jtXkQxalyi", "MK6FEYG63eWcpDFgRYw4w9puJhzDl0tyuqWjZ3M7XJuuG7mMbO");
    }
}












