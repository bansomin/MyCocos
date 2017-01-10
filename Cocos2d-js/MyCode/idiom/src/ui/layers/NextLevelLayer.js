/**
 * Created by HAO on 2016/12/14.
 * Brief   : 下一关界面
 * Version :
 */

var NextLevelLayerDelegate = cc.Class.extend({

	nextLevelFunc : function(){
	}
});

var NextLevelLayer = cc.Layer.extend({

	_bg			:	null,
	_menu		:	null,

	_from		:	"",
	_fromLabel	:	null,

	_delegate 	: 	null,

	ctor : function (from) {
		this._super();

		if (from) {
			this._from = from;
		}

		Wsize = cc.director.getWinSize();

		var colorlayer = new cc.LayerColor(cc.color(0, 0, 0, 100));
		this.addChild(colorlayer);

		this._bg = new cc.Sprite(res.png_bg_from);
		this._bg.setPositionX(Wsize.width/2);
		this._bg.setScale(0);
		this.addChild(this._bg);

		this._fromLabel = new cc.LabelTTF(this._from, "arail", 23);
		this._fromLabel.setPosition(this._bg.getContentSize().width/2, this._bg.getContentSize().height - 190);
		this._fromLabel.setColor(cc.color(0, 0, 0));
		this._fromLabel.setDimensions(350, 250);
		this._bg.addChild(this._fromLabel);

		//下一关按钮
		var item_next = new cc.MenuItemImage("#button.next.selected-hd.png", "#button.next.selected-hd_press.png", this.nextFunc, this);
		item_next.setPosition(this._bg.getContentSize().width/2, 10);

		this._menu = new cc.Menu(item_next);
		this._menu.attr({
			x   :   0,
			y   :   0,
			anchorx :   0,
			anchory :   0
		});
		this._bg.addChild(this._menu);

		this.showFunc();
		this.scheduleUpdate();

		return true;
	},

	setDelegate : function (delegate) {
		this._delegate = delegate;
	},

	getDelegate : function () {
		return this._delegate;
	},

	setFrom : function (from) {
		this._from = from;
		this._fromLabel.setString(this._from);
	},

	showFunc : function () {
		var scale = cc.scaleTo(0.2, 1, 1).easing(cc.easeBackInOut());
		this._bg.runAction(scale);
	},

	nextFunc : function (sender) {

		//播放音效
		SoundManager.playBtnSound(1);

		this.unscheduleUpdate();

		//退出动画
		var scale = cc.scaleTo(0.2, 0, 0).easing(cc.easeBackInOut());
		var seq = cc.sequence(scale, cc.callFunc(this.removeFunc, this));
		this._bg.runAction(seq);

		if (this._delegate && this._delegate.nextLevelFunc){
			this._delegate.nextLevelFunc(sender);
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