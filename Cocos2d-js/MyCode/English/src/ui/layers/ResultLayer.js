/**
 * Created by HAO on 2016/11/28.
 * Brief   :
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

		Wsize = cc.director.getWinSize();

		this._colorlayer = new cc.LayerColor(cc.color(0, 0, 0, 200), 2000, 2000);
		this.addChild(this._colorlayer);

		this.init();

		return true;
	},

	init : function () {

		//播放音效
		SoundManager.playWrongSound();

		this._bg = new cc.Sprite(res.png_bg_result);
		this._bg.setPosition(Wsize.width + this._bg.getContentSize().width, Wsize.height/2);
		this.addChild(this._bg);

		//进入动画
		this._bg.runAction(cc.moveTo(0.2, Wsize.width/2, Wsize.height/2).easing(cc.easeBackInOut()));

		var item_back = new cc.MenuItemImage("#chongxinshuru.png", "#chongxinshuru_press.png", this.backGameFunc, this);
		item_back.setPosition(this._bg.getContentSize().width/2,
								this._bg.getContentSize().height/3);

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
		SoundManager.playBtnSound();

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