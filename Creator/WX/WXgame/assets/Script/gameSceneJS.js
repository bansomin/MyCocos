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

    	bgNode			:	cc.Node,
		startBtn		:	cc.Button,
    	hero			:	cc.Node,	//英雄
		stickBlack		:	cc.Node,	//棍子
		newStickBlack	:	cc.Sprite,	//棍子

        _start			:	false,	//游戏开始
    },

    onLoad: function () {

    	this.initUI();
	},

	onEnable: function () {

        this._start = false;
        this.bgNode.on(cc.Node.EventType.TOUCH_START, this.onTouchBegan.bind(this), this.node);
		this.bgNode.on(cc.Node.EventType.TOUCH_CANCEL, this.onTouchEnded.bind(this), this.node);
		this.bgNode.on(cc.Node.EventType.TOUCH_END, this.onTouchEnded.bind(this), this.node);
    },

	onDisable: function () {
        this.bgNode.off(cc.Node.EventType.TOUCH_START, this.onTouchBegan.bind(this), this.node);
        this.bgNode.off(cc.Node.EventType.TOUCH_CANCEL, this.onTouchEnded.bind(this), this.node);
        this.bgNode.off(cc.Node.EventType.TOUCH_END, this.onTouchEnded.bind(this), this.node);
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
    	//node.setPosition(cc.p(gameViewXoffset + preBlackXoffset, 0));
		node.setPosition(cc.p(this.hero.getPositionX() + heroSize.width/2, this.hero.getPositionY() - heroSize.height/2));
    	node.setAnchorPoint(cc.p(0.5, 0));
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
		var width = stickSize.width * scalex;
		cc.log("scalex:" + scalex + " | size:" + newSize.width + " && " + newSize.height + " => " + width);
        scalex = width / newSize.width;
		cc.log("scalex:" + scalex);
        newstickBlack.node.setScale(scalex, 2);
        //隐藏黑块到屏幕外
        node1.setPosition(cc.p(gameViewXoffset + Wsize.width/2 + newSize.width, -Wsize.height/2 + stickSize.height/2 - 100));
		this.node.addChild(node1);

		var offset = Wsize.width - preBlackXoffset;
        var flag = cc.random0To1() * 120 + 10;
        var flag1 = (cc.random0To1() + 0.6)/2;


		curBlackXoffset = flag;
		betweenXoffset = flag1 * offset;

		//移动到屏幕中间
		node1.runAction(
			cc.sequence(
				cc.moveBy(GC.GC.newBlackTime, cc.p(-betweenXoffset, 0)),
				cc.callFunc(this.setFlagFunc, this)
			)
		);
	},

	setFlagFunc: function () {
		this._start = true;
    },

    onTouchBegan: function(){
		cc.log("onTouchBegan");

		if(this._start==false) return;
        this.startSchedule();
	},

    onTouchEnded: function () {
        cc.log("onTouchEnded");

        if(this._start==false) return;
        this.stopSchedule();
    },

	//开启定时器
    startSchedule: function () {
		cc.log("startSchedule");

		this.schedule(this.upBlackFunc, 0.02);
		this.heroAnimation(ANIMATION_TYPE.SHAKE);
    },

    stopSchedule: function () {
        cc.log("stopSchedule");
        this._start = false;	//触摸停止

        this.unschedule(this.upBlackFunc);
        this.heroAnimation(ANIMATION_TYPE.KICK);

        upBlackObject.node.runAction(
        	cc.sequence(
        		cc.delayTime(0.5),
				cc.rotateBy(0.1, 90),
				cc.callFunc(this.rotateEnd, this)
			)
		);
    },

	//更新木棍长度
    upBlackFunc: function () {
        cc.log("upBlackFunc");

        var scaleY = upBlackObject.node.getScaleY() + GC.GC.scaleSpeed;
        upBlackObject.node.setScaleY(scaleY);
    },

	//操作结束
    rotateEnd: function () {
        cc.log("rotateEnd");

        var size = upBlackObject.node.getContentSize();
        var finalHeight = upBlackObject.node.getScaleY() * size.height;

        //判断是否可以通过
		var offset = (betweenXoffset + preBlackXoffset);
		var result = Wsize.width - offset;

        if (result+5 <= finalHeight && (result+curBlackXoffset >= finalHeight)){
            cc.log("成功！");
        }else {
            cc.log("失败！");
        }
    }
});




























