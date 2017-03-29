/**
 * Created by Jinling on 16/11/23.
 */

var StartLayer =cc.Layer.extend({

    _bg         :   null,
    _item_start :   null,
    _item_rule  :   null,

    _item_start_re  :   null,
    _item_rule_re   :   null,

    _couldOne       :   null,   //白云
    _isDone         :   false,  //白云是否到位

	_soundSpr       :   null,   //音乐图板

    ctor : function () {

        this._super();

        this._isDone = false;
        Wsize = cc.director.getWinSize();

        this.init();

        return true;
    },

    init : function () {

        //播放背景音乐
		//cc.audioEngine.setMusicVolume(0.2);
        //SoundManager.playBGMSound();

        //背景
        this._bg = new cc.Sprite(res.png_bg_start);
        this._bg.setPosition(Wsize.width/2, Wsize.height/2);
        this._bg.setScale(RCCommon.scaleXRatio, 1);
        this.addChild(this._bg, -1);

        var scaleTo = cc.scaleTo(0.3, 1);
        //this._bg.runAction(scaleTo);

        //加载白云
        var couldName = "#could0" + parseInt((4 - 1) * Math.random() + 1) + ".png";
        //cc.log("couldName = " + couldName);
        this._couldOne = new cc.Sprite(couldName);
        this._couldOne.setPosition(Wsize.width/2 - 50, Wsize.height + 200);
        this._couldOne.setScale(0.5);
        this._couldOne.setOpacity(parseInt(240 - 80) * Math.random() + 80);
        this._bg.addChild(this._couldOne);

        var callback = cc.callFunc(this.isDone, this);
		var spa = cc.spawn(cc.scaleTo(0.4, parseInt((4-2)*Math.random() + 2)),
			                            cc.moveTo(0.4, Wsize.width/2-50, Wsize.height-50));
		var seq = cc.sequence(spa, callback);
		this._couldOne.runAction(seq);

        //logo
        var logo = new cc.Sprite("#logo.png");
        logo.setPosition(Wsize.width/2, Wsize.height*3/4 - 30);
        this.addChild(logo);

        //家教logo
        var logo2 = new cc.Sprite("#sjj.png");
        logo2.setPosition(logo.getPositionX() + 150,
                            logo.getPositionY() - 80);
        this.addChild(logo2);

        //公司logo
        var logo3 = new cc.Sprite("#gs.png");
        logo3.setPosition(cc.p(Wsize.width/2, 30));
        this.addChild(logo3);

        //方法一
		// var item_toggle = new SoundButtonUI();
		// item_toggle.attr({
			// x	:	60,
			// y	:	Wsize.height - 60
		// });
		// item_toggle.setScale(2);

/*
        //方法二
        //音乐图板
        this._soundSpr = new cc.Sprite("#soundOn0000.png");
        var item_On = new cc.MenuItemSprite(this._soundSpr, null, null);
        var item_Off = new cc.MenuItemImage("#soundOff.png", null, null);
        var item_toggle = new cc.MenuItemToggle(item_On, item_Off, this.soundOnOffFunc, this);
        item_toggle.attr({
            x   :   60,
            y   :   Wsize.height - 60
        });
        item_toggle.setScale(2);
        // //音乐图标动画
		this.changeTargetAnimation(GC.ANIMATIONTYPE.SOUND);
*/

		//开始按钮
        this._item_start = new cc.MenuItemImage("#kaishi.png", "#kaishi_presss.png", this.startGameFunc, this);
		this._item_start.attr({
            x   :   -this._item_start.getContentSize().width,
            y   :   Wsize.height/2 + 80
        });
		var action = cc.moveTo(0.5, cc.p(Wsize.width/2, Wsize.height/2 + 60)).easing(cc.easeBackInOut());
		this._item_start.runAction(action);
        this._item_start_re = cc.moveTo(0.5, cc.p(-this._item_start.getContentSize().width, Wsize.height/2 + 80)).easing(cc.easeBackInOut());

        //规则按钮
        this._item_rule = new cc.MenuItemImage("#guize.png", "#guize_press.png", this.ruleGameFunc, this);
		this._item_rule.attr({
            x   :   Wsize.width + this._item_rule.getContentSize().width,
            y   :   Wsize.height/2 - 60
        });
		var action2 = cc.moveTo(0.5, cc.p(Wsize.width/2, Wsize.height/2 -100)).easing(cc.easeBackInOut());
		this._item_rule.runAction(action2);
        this._item_rule_re = cc.moveTo(0.5, cc.p(Wsize.width + this._item_rule.getContentSize().width,  Wsize.height/2 - 60)).easing(cc.easeBackInOut());

        var menu = new cc.Menu(this._item_start, this._item_rule);
        menu.attr({
            x   :   0,
            y   :   0,
            anchorx :   0,
            anchory :   0
        });
        this.addChild(menu);

        //机会剩余
        var text = "您还剩余 " + RCCommon.Lives + " 次机会";
        var liveLabel = new cc.LabelBMFont(text, res.font_fnt_cnt);
        liveLabel.setPosition(Wsize.width/2, Wsize.height/2 - 160);
        this.addChild(liveLabel);

		this.scheduleUpdate();
    },

	changeTargetAnimation : function (type) {

		//未静音并且有背景音乐播放
		if (RCCommon.IsMusicOn && cc.audioEngine.isMusicPlaying()) {

			var anima = cc.animationCache.getAnimation("sound");
			if (anima==null) {
				anima = GC.prepareAnimation(type);
				cc.animationCache.addAnimation(anima, "sound");
			}

			this._soundSpr.runAction(anima.repeatForever());
		}
	},

	soundOnOffFunc : function () {
		//cc.log("soundOnOffFunc");

		//SoundManager
		SoundManager.toggleOnOff();
	},

	isDone : function () {
        cc.log("isDone.");
        this._isDone = true;
	},

    startGameFunc : function () {
        //cc.log("startGameFunc");

		//播放音效
		SoundManager.playBtnSound();

        var callback1 = cc.callFunc(this.startOut, this);
        var callback2 = cc.callFunc(this.ruleOut, this);
		var callback4 = cc.callFunc(this.scaleThisScenebgFunc, this);

		var callback3 = cc.callFunc(this.gotoGameSceneFunc, this);
        var spa = cc.spawn(callback1, callback2, callback4);
        var seq = cc.sequence(spa, cc.delayTime(1), callback3);
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

    //场景跳转
    gotoGameSceneFunc : function () {
        cc.director.runScene(new cc.TransitionFade(0.5, new GameScene()));
    },

    //规则界面
    ruleGameFunc : function () {
        //cc.log("ruleGameFunc");

		//播放音效
		SoundManager.playBtnSound();

        var rulelayer = new RuleLayer();
        //rulelayer.setScale(1, 0);
        this.addChild(rulelayer);

        var scale = cc.scaleTo(0.2, 1, 1).easing(cc.easeBackInOut());
        rulelayer.runAction(scale);
    },

    update : function (dt) {
        var currentDate = new Date();
        this._item_start.y  = Wsize.height/2 + 80 + (Math.cos(currentDate.getTime() * 0.002)) * 5;
        this._item_rule.y   = Wsize.height/2 - 60 + (Math.cos(currentDate.getTime() * 0.003)) * 2;

		if (this._isDone) {
            this._couldOne.y = Wsize.height - 50 + (Math.cos(currentDate.getTime() * 0.003)) * 2;
		}
    }

});