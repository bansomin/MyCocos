/**
 * Created by Jinling on 16/11/23.
 */

var RCCommon = RCCommon || {};

//版本号
RCCommon.VERSION_NO = "V20161123";

//背景音乐开关
RCCommon.IsMusicOn = true;

//系统音效开关
RCCommon.IsEffectOn = true;

//Y轴方向缩放比例-特别针对圆形在4:3的屏幕上被拉伸变形的情况,在splashscene中会重新进行计算和赋值
RCCommon.scaleYRatio = 1.0;

RCCommon.ENVIRONMENTS = {
    "DEV":0,    //开发
    "UAT":1,    //测试
    "PRD":2     //生产
};

//当前所使用的运行环境
RCCommon.CURENV = RCCommon.ENVIRONMENTS.PRD;

RCCommon.scaleYRatio = 1.0;
RCCommon.scaleXRatio = 1.0;

//生命值
RCCommon.Lives = 0;

//通用函数供外部调用
RCCommon.UpdateLives = function(val){
    RCCommon.Lives = val;
    runMathGame();
};


























