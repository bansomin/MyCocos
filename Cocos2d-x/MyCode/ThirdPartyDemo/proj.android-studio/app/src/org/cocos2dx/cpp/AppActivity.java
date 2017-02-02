/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
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
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.umeng.social.CCUMSocialController;
import com.umeng.socialize.Config;
import com.umeng.socialize.UMShareAPI;

public class AppActivity extends Cocos2dxActivity {

    /**
     * 保存当前Activity实例， 静态变量
     */
    private Activity mActivity = null;

    /*
	 * (non-Javadoc)
	 *
	 * @see org.cocos2dx.lib.Cocos2dxActivity#onCreate(android.os.Bundle)
	 */
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        mActivity = this;

        //对cocos2dx的一个初始化
        UMShareAPI.get(this);
        CCUMSocialController.initSocialSDK(mActivity, "com.umeng.social");
        Config.shareType = "cocos2dx";
        Log.d("", "####  UmengGame onCreate");
    }

    @Override
    protected void onResume() {
        super.onResume();

        Log.d("", "####  UmengGame onResume");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        Log.d("", "####  UmengGame onDestroy");
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        // 授权回调
        CCUMSocialController.onActivityResult(requestCode, resultCode, data);

        super.onActivityResult(requestCode, resultCode, data);
    }

    /**
     * load lib
     */
    static {
        System.loadLibrary("cocos2dcpp");
    }

}
