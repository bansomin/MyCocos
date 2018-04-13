/**
 * Created by changhao on 4/13/2018.
 * Brief   :    游戏主场景
 */

var Wsize = null;

var stickSize   = null;
var npcNormal   =null;

/**背景层**/
var Score       = 0;    //分数
var ScoreText   = null; //分数字体
var guideTextPic = null;//黑块

/**游戏层**/
var gameViewXoffset = 0;    //游戏背景层偏移量
var preBlackXoffset = 0;    //前一个黑块信息
var curBlackXoffset = 0;    //生成黑块信息
var betweenXoffset  = 0;    //两个黑块之间的距离
var upBlackObject = null;   //增长黑块对象

cc.Class({
    extends: cc.Component,

    properties: {

    },

    onload: function () {

		//初始动作
		npcController.initNPC(this);
		npcController.yao();
	}
});




























