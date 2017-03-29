/**
 * Created by HAO on 2017/2/2.
 * Brief   : 新用户,创建名称层
 * Version :
 */

var UserInforLayerDelegate = cc.Class.extend({

	updateNickNameLabel : function(){

	}
});

var UserInforLayer = cc.LayerColor.extend({

	_bg			:	null,		//背景面板
	_itemBack	:	null,		//确定按钮
	_nickName	:	"",			//用户昵称
	_editBox	:	null,		//输入框

	_delegate : null,

	ctor : function () {
		this._super(cc.color(0, 0, 0, 100));

		Wsize = cc.director.getWinSize();

		this._bg = new cc.Sprite(res.info.board);
		this._bg.setPosition(Wsize.width/2, Wsize.height/2);
		this.addChild(this._bg);

		this._bg.setScaleY(0);

		this._bg.runAction(
			cc.scaleTo(0.2, 1, 1)
		);

		this.init();

		return true;
	},

	init : function () {

		this._itemBack = new cc.MenuItemImage("#done.png", "#done.png", this.backGameFunc, this);
		this._itemBack.attr({
			x   :   this._bg.getContentSize().width/2,
			y   :   0
		});

		var menu = new cc.Menu(this._itemBack);
		menu.attr({
			x   :   0,
			y   :   0,
			anchorx :   0,
			anchory :   0
		});

		this._bg.addChild(menu);

		cc.eventManager.addListener({
			event          : cc.EventListener.TOUCH_ONE_BY_ONE,
			swallowTouches : true,
			onTouchBegan   : function (touch, event) {
				cc.log("onTouchBegan");
				return true;
			}
		}, this);

		this.initEditBox();

		this.scheduleUpdate();
	},

	initEditBox : function () {

		var spr = new cc.Scale9Sprite();
		this._editBox = new cc.EditBox(cc.size(350, 75), spr);
		this._editBox.setFontColor(cc.color(0, 0, 0));
		this._editBox.setPlaceHolder("请输入昵称");
		this._editBox.setPlaceholderFontSize(25);
		this._editBox.setFontSize(30);
		this._editBox.setMaxLength(6);
		this._editBox.setPosition(this._bg.getContentSize().width*5/6, this._bg.getContentSize().height/2);

		var oldUser = cc.sys.localStorage.getItem(GC.KEY.USERNAME);
		cc.log("oldUser : " + oldUser);

		if (oldUser!=null) {
			this._editBox.setString(oldUser);
		}

		this._bg.addChild(this._editBox);
		this._editBox.setDelegate(this);
	},

	editBoxEditingDidBegin : function (editBox) {
	},

	editBoxTextChanged: function (editBox, text) {
		cc.log("昵称 ：" + text);
	},

	editBoxEditingDidEnd: function (editBox) {
	},

	backGameFunc : function (sender) {
		cc.log("backGameFunc");

		Sound.playEffectBtn();

		this.unscheduleUpdate();

		//保存用户信息
		var info = this._editBox.getString();
		cc.log("NICKNAME : " + info + " : " + info.length);

		if (info=="" || !GC.CheckUserName(info)) {
			new MessageBox().addTips(GC.INFO.NICKNAMEERROR, function () {});
		}
		else {
			new MessageBox().addTips(GC.INFO.NICKNAMERIGHT, function () {});
			cc.sys.localStorage.setItem(GC.KEY.USERNAME, info);
		}

		var scale = cc.scaleTo(0.2, 1, 0).easing(cc.easeBackInOut());
		var seq = cc.sequence(scale, cc.callFunc(this.removeSelfFromParent, this));
		this.runAction(seq);

		//调WelecomeLayer的
		if (this._delegate && this._delegate.updateNickNameLabel){
			this._delegate.updateNickNameLabel(sender);
		}
	},

	removeSelfFromParent : function (sender) {
		this.removeFromParent();
	},

	//实现动画的上下移动
	update : function(){
		var currentDate = new Date();
		this._bg.y   = Wsize.height/2 + (Math.cos(currentDate.getTime() * 0.002)) * 5;
		this._itemBack.y = (Math.cos(currentDate.getTime() * 0.003)) * 2;
	},

	getDelegate : function () {

		return this._delegate;
	},

	setDelegate : function (delegate){

		this._delegate = delegate;
	}

});