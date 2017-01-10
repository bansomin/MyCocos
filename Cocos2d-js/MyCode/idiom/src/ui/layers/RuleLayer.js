/**
 * Created by HAO on 2016/12/12.
 * Brief   : 规则界面
 * Version :
 */

var RuleLayer = cc.LayerColor.extend({

	_bg		:	null,
	_menu	:	null,

	ctor : function () {
		this._super(cc.color(0, 0, 0, 200));

		Wsize = cc.director.getWinSize();

		this.init();

		return true;
	},

	init : function () {

		this._bg = new cc.Sprite(res.png_bg_rule);
		this._bg.setPosition(Wsize.width/2, Wsize.height/2);
		this._bg.setScale(1, 0);
		this.addChild(this._bg);

		var scale = cc.scaleTo(0.2, 0.8, 0.8).easing(cc.easeBackInOut());
		this._bg.runAction(scale);

		var item_back = new cc.MenuItemImage("#back.png", "#back_[ress.png", this.backGameFunc, this);
		item_back.attr({
			x   :   this._bg.getContentSize().width/2,
			y   :   this._bg.getContentSize().height/12
		});

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

	backGameFunc : function () {
		cc.log("backGameFunc");

		//播放音效
		SoundManager.playBtnSound();

		this.unscheduleUpdate();

		var scale = cc.scaleTo(0.2, 1, 0).easing(cc.easeBackInOut());
		var seq = cc.sequence(scale, cc.callFunc(this.removeSelfFromParent, this));
		this._bg.runAction(seq);
	},

	removeSelfFromParent : function (sender) {
		this.removeFromParent();
	},

	//实现动画的上下移动
	update : function(){
		var currentDate = new Date();

		this._bg.y   = Wsize.height/2 + (Math.cos(currentDate.getTime() * 0.002)) * 5;
		this._menu.y = (Math.cos(currentDate.getTime() * 0.003)) * 2;
	}

});