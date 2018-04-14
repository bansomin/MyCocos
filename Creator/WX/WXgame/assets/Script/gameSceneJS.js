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

var animaList = [
	'Hero_kick',
	'Hero_shake',
	"Hero_walk",
	"Hero_yao"
];

cc.Class({
    extends: cc.Component,

    properties: {

    	hero	:	cc.Node,
		_animIndex	:	0
    },

    onload: function () {

    	this._animIndex = 0;
	},

	playAnimation: function (_name) {

		var anim = this.hero.getComponent(cc.Animation);
		var state = anim.play(_name);
		state.wrapMode = cc.WrapMode.Loop;
	},
	
	onClickStartBtn: function (evn, type) {

	},

	onClickTestBtn: function (evn, type) {

		var animaName = animaList[this._animIndex];
		cc.log("index : " + this._animIndex + "animaName : " + animaName);
		this.playAnimation(animaName);
		this._animIndex++;
		this._animIndex = this._animIndex > 3 ? 0 : this._animIndex;
	}
});




























