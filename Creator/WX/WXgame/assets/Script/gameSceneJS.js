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

var ANIMATION_TYPE = cc.Enum({
	KICK 	:　	"Hero_kick",
	SHAKE 	: 	"Hero_shake",
	WALK 	: 	"Hero_walk",
	YAO		:	"Hero_yao"
});

var GC = require("GameConfig");
cc.Class({
    extends: cc.Component,

    properties: {

		startBtn		:	cc.Button,
    	hero			:	cc.Node,	//英雄
		stickBlack		:	cc.Node,	//棍子
		newStickBlack	:	cc.Sprite,	//棍子

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

		var scaleX = 30;
		var scaleY = 2;
		this.stickBlack.setScale(scaleX, scaleY);
		stickSize = this.stickBlack.getContentSize();
		stickSize.width = stickSize.width * scaleX;
		stickSize.height = stickSize.height * scaleY;
		cc.log("Wsize : " + Wsize.width + " ** " + Wsize.height);
		cc.log("heroSize : " + heroSize.width + " ** " + heroSize.height);
		cc.log("stickSize : " + stickSize.width + " ** " + stickSize.height);
		this.stickBlack.setPosition(cc.p(0, -Wsize.height/2 + stickSize.height/2 - 100));

		var herx = this.stickBlack.getPositionX();
		var hery = this.stickBlack.getPositionY() + stickSize.height/2 + heroSize.height/2;
		cc.log('herx : ' + herx + " ** " + hery);
		this.hero.setPosition(cc.p(herx, hery));
	},

	onClickStartBtn: function (evn, type) {

    	var _width = stickSize.width/2;
    	gameViewXoffset =  -_width + Wsize.width/2;
    	preBlackXoffset = _width;
    	cc.log("gameViewXoffset : " + gameViewXoffset);

    	//节点的移动
    	this.node.runAction(
			cc.moveBy(GC.GC.screenTime, cc.p(-gameViewXoffset, 100))
		);
    	//英雄的移动
		var self = this;
		this.hero.runAction(
			cc.sequence(
				cc.moveBy(GC.GC.screenTime, cc.p(stickSize.width/2 - 50, 0)),
				cc.callFunc(self.addBlock, self)
			)
		);

		this.startBtn.node.runAction(
			cc.spawn(
				cc.sequence(
					cc.scaleTo(0.1, 1.1, 1.1),
					cc.scaleTo(0.1, 1, 1)
				),
				cc.fadeOut(0.5),
				cc.callFunc(function () {
					self.startBtn.node.active = false;
				})
			)
		)
	},

	heroAnimation: function (_animaName) {
		this.HeroJS.playAnimationByName(_animaName);
	},

	//创建黑块
	addBlock: function () {

    	var node = new cc.Node('Sprite');
    	upBlackObject = node.addComponent(cc.Sprite);
    	upBlackObject.spriteFrame = new cc.SpriteFrame(cc.url.raw("resources/textures/gameImg/stick_black.png"));
    	node.setPosition(cc.p(gameViewXoffset + preBlackXoffset, 0));
    	node.setScaleY(0);
    	this.node.addChild(upBlackObject.node);

		/*
		 * 黑条变长的方法
		 *随机生成宽度加载到屏幕的右侧
		 * 动作结束可以触发手指按下动作
		 */
		var node1 = new cc.Node('Sprite1');
		var newstickBlack = node1.addComponent(cc.Sprite);
		newstickBlack.spriteFrame = new cc.SpriteFrame(cc.url.raw("resources/textures/gameImg/stick_black.png"));
		var newSize = newstickBlack.node.getContentSize();
		var scalex = GC.GC.scaleData[0];
		/*newSize.width = newSize.width * scalex;
		newSize.height = newSize.height * scalex;*/
		cc.log("scalex:" + scalex + " | size:" + newSize.width + " && " + newSize.height);
		newstickBlack.node.setScale(scalex, 2);
		this.node.addChild(node1);
	}
});




























