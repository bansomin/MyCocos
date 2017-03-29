/**
 * Created by HAO on 2017/2/8.
 * Brief   :	信息栏
 * Version :
 */

var HubLayerDelegate = {

	heroJump : function () {

	}
};

var HubLayer = cc.Layer.extend({

	_delegate	:	null,	//代理

	_energyBg	:	null,
	_progress	:	null,

	_distanceBg	:	null,
	_disLabel	:	null,
	_distance	:	0,

	_goldBg		:	null,
	_goldLabel	:	null,
	_gold		:	0,

	_player		:	null,	//主角
	_statistics	:	null,

	ctor : function (player, statistics) {
		this._super();

		this._player = player;
		this._statistics = statistics;

		Wsize = cc.director.getWinSize();

		var bg = new cc.Sprite(res.bg.bg1);
		bg.attr({
			x	:	Wsize.width/2,
			y	:	Wsize.height/2
		});
		//this.addChild(bg, -1);

		this.init();
		
		return true;
	},

	getDelegate : function () {
		return this._delegate;
	},

	setDelegate : function (delegate){
		this._delegate = delegate;
	},
	
	init : function () {

		var btn_back = new cc.MenuItemImage("#menu.png",
											"#menu-s.png",
											this.backFunc, this);
		btn_back.attr({
			x	:	50,
			y	:	Wsize.height - 50
		});
		btn_back.setScale(0.8);

		//金币
		this._goldBg = new cc.Sprite("#gold-bar.png");
		this._goldBg.attr({
			x	:	btn_back.getContentSize().width*1.1 + this._goldBg.getContentSize().width/2,
			y	:	Wsize.height - this._goldBg.getContentSize().height
		});
		this.addChild(this._goldBg);
		//金币标签(99999)
		this._goldLabel = new cc.LabelBMFont(this._statistics.score, res.font.fnt);
		this._goldLabel.setPosition(this._goldBg.getContentSize().width/2 + 10, this._goldBg.getContentSize().height/3);
		this._goldLabel.setScale(0.5);
		this._goldBg.addChild(this._goldLabel);

		//距离
		this._distanceBg = new cc.Sprite("#distance.png");
		this._distanceBg.attr({
			x	:	this._goldBg.getPositionX() + this._distanceBg.getContentSize().width,
			y	:	this._goldBg.getPositionY()
		});
		this.addChild(this._distanceBg);
		//距离标签(9999999)
		this._disLabel = new cc.LabelBMFont(this._distance+"", res.font.fnt);
		this._disLabel.setPosition(this._distanceBg.getContentSize().width/2 + 20, this._distanceBg.getContentSize().height/3);
		this._disLabel.setScale(0.5);
		this._distanceBg.addChild(this._disLabel);

		//能量背景
		this._energyBg = new cc.Sprite("#energy-bar.png");
		this._energyBg.attr({
			x	:	this._distanceBg.getPositionX() + this._goldBg.getContentSize().width + 5,
			y	:	this._goldBg.getPositionY()
		});
		this.addChild(this._energyBg);
		//进度条
		this._progress = new cc.Sprite("#progress.png");
		this._progress.attr({
			x	:	this._energyBg.getContentSize().width/4 - 1,
			y	:	this._energyBg.getContentSize().height/2 - 3,
			anchorX	:	0,
			anchorY	:	0.5
		});
		this._progress.setScale(0.00001, 0.7);
		this._energyBg.addChild(this._progress);

		//三个技能按钮
		//电磁
		var btn_magnet = new cc.MenuItemImage("#magnet-prop.png",
											 "#magnet-prop.png",
											 this.clickMagent,this);
		btn_magnet.setPosition(Wsize.width - 184 - 10, 76);
		btn_magnet.setScale(1.2);

		//加速
		var btn_blue = new cc.MenuItemImage("#shoes-prop.png",
											"#shoes-prop.png",
											this.clickBlueShoes,this);
		btn_blue.setPosition(Wsize.width - 128 - 50, 154);
		btn_blue.setScale(1.2);

		//减速
		var btn_red = new cc.MenuItemImage("#redshoes-prop.png",
										   "#redshoes-prop.png",
										   this.clickRedShoes,this);
		btn_red.setPosition(Wsize.width - 60 - 50, 190);
		btn_red.setScale(1.2);

		//跳跃
		var btn_jump = new cc.MenuItemImage("#Joystick.png",
										   "#Joystick-s.png",
										   this.clickJump,this);
		btn_jump.setPosition(Wsize.width - btn_jump.getContentSize().width, btn_jump.getContentSize().height);
		btn_jump.setScale(1.2);

		var menu = new cc.Menu(btn_back, btn_magnet, btn_blue, btn_red, btn_jump);
		menu.attr({
			x	:	0,
			y	:	0
		});
		this.addChild(menu);
	},

	backFunc : function () {

		Sound.playEffectBtn();
		cc.director.runScene(new WelecomeScene());
	},

	clickMagent : function (sender) {

		Sound.playEffectBtn();
		sender.runAction(
			cc.sequence(
				cc.scaleTo(0.1, 1.4, 1.4),
				cc.scaleTo(0.1, 1.2, 1.2)
			)
		);
		new MessageBox().addTips("释放电磁技能", function () {});
	},

	clickBlueShoes : function (sender) {

		Sound.playEffectBtn();
		sender.runAction(
			cc.sequence(
				cc.scaleTo(0.1, 1.4, 1.4),
				cc.scaleTo(0.1, 1.2, 1.2)
			)
		);
		new MessageBox().addTips("释放加速技能", function () {});
	},

	clickRedShoes : function (sender) {

		Sound.playEffectBtn();
		sender.runAction(
			cc.sequence(
				cc.scaleTo(0.1, 1.4, 1.4),
				cc.scaleTo(0.1, 1.2, 1.2)
			)
		);
		new MessageBox().addTips("释放减速技能", function () {});
	},

	clickJump : function (sender) {

		Sound.playEffectJump();
		if (this._delegate && this._delegate.heroJump) {
			this._delegate.heroJump(sender);
		}
		sender.runAction(
			cc.sequence(
				cc.scaleTo(0.1, 1.4, 1.4),
				cc.scaleTo(0.1, 1.2, 1.2)
			)
		);
		//new MessageBox().addTips("跳跃", function () {});
	},

	update : function (dt) {

		this._goldLabel.setString(this._statistics.coins);
		this._disLabel.setString(this._statistics.meter);
	}

});