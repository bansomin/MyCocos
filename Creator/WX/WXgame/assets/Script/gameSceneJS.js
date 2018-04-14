/**
 * Created by changhao on 4/13/2018.
 * Brief   :    游戏主场景
 */

var Wsize = null;

var heroSize   	= null;	//英雄的大小
var stickSize   = null;	//棍子的大小
var npcNormal   =null;	//

var _width = 180;

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

    	hero		:	cc.Node,	//英雄
		stickBlack	:	cc.Node,	//棍子


		_animIndex	:	0
    },

    onLoad: function () {

    	this._animIndex = 0;

    	this.initUI();
	},

	initUI: function () {

    	this.HeroJS = this.hero.getComponent("HeroJS");

    	//init
		Wsize = cc.director.getVisibleSize();
		heroSize = this.HeroJS.getHeroContentSize();
		stickSize = this.stickBlack.getContentSize();
		cc.log("Wsize : " + Wsize.width + " ** " + Wsize.height);
		cc.log("heroSize : " + heroSize.width + " ** " + heroSize.height);
		cc.log("stickSize : " + stickSize.width + " ** " + stickSize.height);

		this.stickBlack.setScale(180/stickSize.width, 387/stickSize.height);
		//this.stickBlack.setPosition(cc.p(0, -Wsize.height/2 + stickSize.height/2));
		this.stickBlack.setPosition(cc.p(0, 0));
		var herx = this.stickBlack.getPositionX();
		var hery = this.stickBlack.getPositionY() + this.stickBlack.getContentSize().height/2 + heroSize.height;
		cc.log('herx : ' + herx + " ** " + hery);
		this.hero.setPosition(cc.p(herx, hery));

    	//棍子的位置

	},

	onClickStartBtn: function (evn, type) {

	},

	onClickTestBtn: function (evn, type) {

		var animaName = animaList[this._animIndex];
		cc.log("index : " + this._animIndex + "animaName : " + animaName);
		this._animIndex++;
		this._animIndex = this._animIndex > 3 ? 0 : this._animIndex;

		this.HeroJS.playAnimationByName(animaName);
	}
});




























