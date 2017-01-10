/**
 * Created by HAO on 2016/12/8.
 * Brief   : 开始界面
 * Version :
 */

var StartLayer =cc.Layer.extend({

	_bg         :   null,
	_item_start :   null,
	_item_rule  :   null,

	_item_start_re  :   null,
	_item_rule_re   :   null,

	ctor : function () {
		this._super();

		Wsize = cc.director.getVisibleSize();

		this.init();

		return true;
	},

	init : function () {

		this.getScaleYRation();

		//背景
		this._bg = new cc.Sprite(res.png_startBg);
		this._bg.setPosition(cc.p(Wsize.width/2, Wsize.height/2));
		this.addChild(this._bg, -1);

		this._bg.setScale(RCCommon.scaleXRatio, 1);

		//applogo
		var applogo = new cc.Sprite(res.png_applogo);
		applogo.setPosition(Wsize.width/2, Wsize.height - applogo.getContentSize().height/2 - 208);
		this.addChild(applogo);

		//家教logo
		var logo2 = new cc.Sprite("#sjj.png");
		logo2.setPosition(applogo.getPositionX() + logo2.getContentSize().width,
								applogo.getPositionY() - applogo.getContentSize().height/2 - 36);
		this.addChild(logo2);

		//公司logo
		var logo3 = new cc.Sprite("#gs.png");
		logo3.setPosition(Wsize.width/2, logo3.getContentSize().height/2 + 24);
		this.addChild(logo3);

		//开始按钮
		this._item_start = new cc.MenuItemImage("#kaishi.png", "#kaishi_presss.png", this.startGameFunc, this);
		this._item_start.attr({
			x   :   -this._item_start.getContentSize().width,
			y   :   applogo.getPositionY() - applogo.getContentSize().height/2 - this._item_start.getContentSize().height/2 - 72
		});
		var action = cc.moveTo(1, cc.p(Wsize.width/2, applogo.getPositionY() - applogo.getContentSize().height/2 - this._item_start.getContentSize().height/2 - 72)).easing(cc.easeBackInOut());
		this._item_start_re = cc.moveTo(0.5, cc.p(-this._item_start.getContentSize().width, applogo.getPositionY() - applogo.getContentSize().height/2 - this._item_start.getContentSize().height/2 - 72)).easing(cc.easeBackInOut());
		this._item_start.runAction(action);

		//规则按钮
		this._item_rule = new cc.MenuItemImage("#guize.png", "#guize_press.png", this.ruleGameFunc, this);
		this._item_rule.attr({
			x   :   Wsize.width + this._item_rule.getContentSize().width,
			y   :   this._item_start.getPositionY() - this._item_start.getContentSize().height/2 - this._item_rule.getContentSize().height/2 - 42
		});
		var action2 = cc.moveTo(1, cc.p(Wsize.width/2,
											this._item_start.getPositionY() - this._item_start.getContentSize().height/2 - this._item_rule.getContentSize().height/2 - 42)).easing(cc.easeBackInOut());
		this._item_rule.runAction(action2);
		this._item_rule_re = cc.moveTo(0.5, cc.p(Wsize.width + this._item_rule.getContentSize().width,
													this._item_start.getPositionY() - this._item_start.getContentSize().height/2 - this._item_rule.getContentSize().height/2 - 42)).easing(cc.easeBackInOut());

		var menu = new cc.Menu(this._item_start, this._item_rule);
		menu.attr({
			x   :   0,
			y   :   0,
			anchorx :   0,
			anchory :   0
		});
		this.addChild(menu);

		var remainBg = new cc.Sprite("#remainder.png");
		remainBg.setPosition(Wsize.width/2,
								this._item_rule.getPositionY() - this._item_rule.getContentSize().height/2 - remainBg.getContentSize().height/2 - 28);
		remainBg.setScale(1, 0);
		this.addChild(remainBg);

		//机会剩余标签
		var liveLabel = new cc.LabelTTF(RCCommon.Lives, "Arial", 35);
		liveLabel.setFontFillColor(cc.color(0, 0, 0));
		liveLabel.setPosition(remainBg.getContentSize().width*5/9, remainBg.getContentSize().height/2);
		remainBg.addChild(liveLabel);

		remainBg.runAction(
			cc.scaleTo(0.6, 1, 1).easing(cc.easeBackInOut())
		);

		this.scheduleUpdate();
	},

	startGameFunc : function () {
		cc.log("startGameFunc");

		//播放音效
		SoundManager.playBtnSound(1);

		var callback1 = cc.callFunc(this.startOut, this);
		var callback2 = cc.callFunc(this.ruleOut, this);
		var callback3 = cc.callFunc(this.gotoGameSceneFunc, this);
		var callback4 = cc.callFunc(this.scaleThisScenebgFunc, this);
		var spa = cc.spawn(callback1, callback2);
		var seq = cc.sequence(spa, cc.delayTime(0.5), callback3);

		this.runAction(seq);
	},

	//开始按钮的退出动作
	startOut : function () {
		this._item_start.runAction(this._item_start_re);
	},

	//规则按钮的退出动作
	ruleOut : function () {
		this._item_rule.runAction(this._item_rule_re);
	},

	//背景的缩放
	scaleThisScenebgFunc : function () {
		var scaleTo = cc.scaleTo(1, 2);
		this._bg.runAction(scaleTo);
	},

	gotoGameSceneFunc : function () {
		cc.director.runScene(new cc.TransitionFade(0.5, new GameScene()));
	},

	ruleGameFunc : function () {
		cc.log("ruleGameFunc");

		//播放音效
		SoundManager.playBtnSound(1);

		var rulelayer = new RuleLayer();
		this.addChild(rulelayer);
	},

	getScaleYRation : function () {
		var Fsize = cc.view.getFrameSize();
		cc.log("Fsize : " + Fsize.width + " * " + Fsize.height);

		var designRate = cc.winSize.height/cc.winSize.width;
		var devicRate = Fsize.height/Fsize.width;
		cc.log("designRate : " + designRate);
		cc.log("devicRate : " + devicRate);

		var scaleYRate = Number(designRate/devicRate).toFixed(4);
		cc.log("scaleYRate : + " + scaleYRate);

		if (Fsize.height > Fsize.width) {
			RCCommon.scaleYRatio = scaleYRate;
		}
	},

	update : function (dt) {
		var currentDate = new Date();

		this._item_start.y  = Wsize.height/2 + 80 + (Math.cos(currentDate.getTime() * 0.002)) * 5;
		this._item_rule.y   = Wsize.height/2 - 60 + (Math.cos(currentDate.getTime() * 0.003)) * 2;
	}
});