/**
 * Created by HAO on 2016/12/12.
 * Brief   : 结果层
 * Version :
 */

var ResultLayerDelegate = cc.Class.extend({

	rePlayFunc : function(){
	}
});

var ResultLayer = cc.Layer.extend({

	_bg			:	null,
	_menu		:	null,
	_delegate 	: 	null,
	_colorlayer	:	null,

	ctor : function () {
		this._super();

		Wsize = cc.director.getVisibleSize();

		this._colorlayer = new cc.LayerColor(cc.color(0, 0, 0, 100));
		this.addChild(this._colorlayer);

		this.init();

		return true;
	},

	init : function () {

		//播放音效
		SoundManager.playWrongSound(1);

		this._bg = new cc.Sprite(res.png_wrongbg);
		this._bg.setPosition(Wsize.width + this._bg.getContentSize().width, Wsize.height/2);
		this.addChild(this._bg);

		// var wronglogo = new cc.Sprite("#wronglogo.png");
		// wronglogo.setPosition(this._bg.getContentSize().width/2, this._bg.getContentSize().height - wronglogo.getContentSize().height/2 - 20);
		// this._bg.addChild(wronglogo);
		//
		// var wronglabelSpr = new cc.Sprite("#answererror.png");
		// wronglabelSpr.setPosition(this._bg.getContentSize().width/2, this._bg.getContentSize().height/2);
		// wronglabelSpr.setScale(1.5);
		// this._bg.addChild(wronglabelSpr);

		//进入动画
		this._bg.runAction(cc.moveTo(0.2, Wsize.width/2, Wsize.height/2).easing(cc.easeBackInOut()));

		//var item_back = new cc.MenuItemImage("#chongxinshuru.png", "#chongxinshuru_press.png", this.backGameFunc, this);
		var item_back = new cc.MenuItemImage(res.png_replay, res.png_replay_pre, this.backGameFunc, this);
		item_back.setPosition(this._bg.getContentSize().width/2, 0);

		this._menu = new cc.Menu(item_back);
		this._menu.attr({
			x   :   0,
			y   :   0,
			anchorx :   0,
			anchory :   0
		});
		this._bg.addChild(this._menu);

		cc.eventManager.addListener({
			event          : cc.EventListener.TOUCH_ONE_BY_ONE,
			swallowTouches : true,
			onTouchBegan   : function (touch, event) {

				return true;
			}
		}, this);

		this.scheduleUpdate();
	},

	setDelegate : function (delegate) {
		this._delegate = delegate;
	},

	getDelegate : function () {
		return this._delegate;
	},

	backGameFunc : function (sender) {
		cc.log("backGameFunc");

		//播放音效
		SoundManager.playBtnSound(1);

		this.unscheduleUpdate();
		//退出动画
		var action = cc.moveTo(0.2, -this._bg.getContentSize().width, Wsize.height/2).easing(cc.easeBackInOut());
		var seq = cc.sequence(action, cc.callFunc(this.removeFunc, this));
		this._bg.runAction(seq);

		if (this._delegate && this._delegate.rePlayFunc){
			this._delegate.rePlayFunc(sender);
		}
	},

	removeFunc : function () {
		this.removeFromParent();
	},

	//实现动画的上下移动
	update : function(){
		var currentDate = new Date();
		this._bg.y   = Wsize.height/2 + (Math.cos(currentDate.getTime() * 0.002)) * 5;
		this._menu.y = (Math.cos(currentDate.getTime() * 0.003)) * 2;
	}

});