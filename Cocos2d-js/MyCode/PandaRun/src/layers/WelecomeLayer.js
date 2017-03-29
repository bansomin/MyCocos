/**
 * Created by HAO on 2017/2/2.
 * Brief   :	欢迎界面的实现
 * Version :
 */

var WelecomeLayer = cc.Layer.extend({

	_nickNameLabel	:	null,	//昵称标签
	_nickName		:	null,	//昵称

	ctor : function () {
		this._super();

		Wsize = cc.director.getWinSize();
		this._nickName = cc.sys.localStorage.getItem(GC.KEY.USERNAME);
		cc.log("nickName : " + this._nickName);

		//背景
		var bg = new cc.Sprite(res.menu.bg);
		bg.setPosition(Wsize.width/2, Wsize.height);
		bg.setScale(1.0);
		this.addChild(bg);
		//背景的动画
		var move = cc.moveTo(1.5, cc.p(Wsize.width/2, Wsize.height/2)).easing(cc.easeElasticOut());
		bg.runAction(move);

		this.init();

		return true;
	},

	init : function () {

		//初始logo以及动画
		var logo = new cc.Sprite("#game-logo.png");
		logo.setPosition(cc.p(-200, Wsize.height - 150));
		logo.setScale(0.8);
		this.addChild(logo, 10);
		var seq_log =   cc.sequence(cc.moveTo(1, cc.p(250, Wsize.height - 150)).easing(cc.easeElasticOut()),
									cc.delayTime(0.1),
									cc.callFunc(this.myActionFunc, logo, "logo"));
		logo.runAction(seq_log);

		//开始按钮以及动画
		var btn_start = new cc.MenuItemImage("#start-btn-selected.png",
											 "#start-btn-selected-s.png",
											 this.startFunc,this);
		btn_start.setPosition(cc.p(-200, 150));
		btn_start.setScale(0.6);
		btn_start.runAction(
			cc.sequence(
				cc.moveTo(1, cc.p(200, 150)).easing(cc.easeElasticInOut(0.8)),
				cc.delayTime(0.1),
				cc.callFunc(this.myActionFunc, btn_start, "start")
			)
		);

		//******************************************************************************//
		//商场按钮以及动画
		var btn_store = new cc.MenuItemImage("#store-btn.png",
											 "#store-btn-s.png",
											 this.storeFunc,this);
		btn_store.setPosition(cc.p(Wsize.width+200, Wsize.height/2 - 50 + GC.HIGH));
		btn_store.setScale(0.8);
		btn_store.runAction(
			cc.sequence(
				cc.delayTime(0.1),
				cc.moveTo(2, cc.p(Wsize.width-200, Wsize.height/2 - 50 + GC.HIGH)).easing(cc.easeElasticOut()),
				cc.delayTime(0.5),
				cc.callFunc(this.myActionFunc, btn_store, "store")
			)
		);

		//设置按钮以及动画
		var btn_set = new cc.MenuItemImage("#set-btn.png",
										   "#set-btn-s.png",
										   this.setFunc,this);
		btn_set.setPosition(cc.p(Wsize.width+200, Wsize.height/2 - 120 + GC.HIGH));
		btn_set.setScale(0.8);
		btn_set.runAction(
			cc.sequence(
				cc.delayTime(0.2),
				cc.moveTo(2, cc.p(Wsize.width-200, Wsize.height/2 - 120 + GC.HIGH)).easing(cc.easeElasticOut()),
				cc.delayTime(0.5),
				cc.callFunc(this.myActionFunc, btn_store, "set")
			)
		);

		//关于按钮以及动画
		var btn_about = new cc.MenuItemImage("#about-btn.png",
										     "#about-btn-s.png",
											 this.aboutFunc,this);
		btn_about.setPosition(cc.p(Wsize.width+200, Wsize.height/2 - 190 + GC.HIGH));
		btn_about.setScale(0.8);
		btn_about.runAction(
			cc.sequence(
				cc.delayTime(0.3),
				cc.moveTo(2, cc.p(Wsize.width-200, Wsize.height/2 - 190 + GC.HIGH)).easing(cc.easeElasticOut()),
				cc.delayTime(0.5),
				cc.callFunc(this.myActionFunc, btn_about, "about")
			)
		);

		//排行按钮以及动画
		var btn_rank = new cc.MenuItemImage("#rank-btn.png",
											"#rank-btn-s.png",
											this.rankFunc,this);
		btn_rank.setPosition(cc.p(Wsize.width+200, Wsize.height/2 - 260 + GC.HIGH));
		btn_rank.setScale(0.8);
		btn_rank.runAction(
			cc.sequence(
				cc.delayTime(0.4),
				cc.moveTo(2, cc.p(Wsize.width-200, Wsize.height/2 - 260 + GC.HIGH)).easing(cc.easeElasticOut()),
				cc.delayTime(0.5),
				cc.callFunc(this.myActionFunc, btn_rank, "rank")
			)
		);

		//欢迎字体
		var welcome = new cc.LabelTTF("Welcome", "Helvetica", 60);
		welcome.setColor(cc.color(255, 255, 255));
		welcome.attr({
			x    :   Wsize.width - 210,
			y   :    Wsize.height - 50
		});
		welcome.setScale(0.3);
		this.addChild(welcome);

		var tempname = "";
		if (this._nickName==null || this._nickName=="") {	//新用户
			cc.log("if");

			tempname = "Player";
			cc.sys.localStorage.setItem(GC.KEY.USERNAME, tempname);
			this.addUserInforLayer();
		}
		else {
			cc.log("else");

			tempname = this._nickName;
		}
		cc.log("nickName : " + this._nickName);
		cc.log("tempname : " + tempname);

		//用户名按钮
		this._nickNameLabel =  new cc.LabelTTF(tempname, "Arial", 20);
		this._nickNameLabel.setColor(cc.color(0, 0, 0));
		var item_name = new cc.MenuItemLabel(this._nickNameLabel, this.changeNickNameFunc, this);
		item_name.attr({
			x	:	welcome.getPositionX() + this._nickNameLabel.getContentSize().width * 1.5,
			y	:	welcome.getPositionY()
		});

		var menu = new cc.Menu(item_name, btn_start, btn_store, btn_set, btn_about, btn_rank);
		menu.attr({
			x	:	0,
			y	:	0
		});
		this.addChild(menu);
	},

	myActionFunc : function(target, name){

		var shaking 	= null;
		var shakingBack = null;
		var delayTime	= null;
		var shakingSeq	= null;

		switch (name){

			case "logo" :
				cc.log("logo.");
				shaking     = cc.moveTo(1, cc.p(250, Wsize.height - 170)).easing(cc.easeElasticIn());
				shakingBack = cc.moveTo(1, cc.p(250, Wsize.height - 130)).easing(cc.easeElasticOut());
				delayTime   = new cc.DelayTime(Math.random() * 3);
				break;

			case "start" :
				cc.log("start.");
				shaking     = cc.moveTo(1, cc.p(200, 150)).easing(cc.easeIn(2.0));
				shakingBack = cc.moveTo(1, cc.p(200, 140)).easing(cc.easeOut(2.0));
				delayTime   = new cc.DelayTime(Math.random());
				break;

			case "store" :
				cc.log("store.");
				shaking     = cc.moveTo(1, cc.p(Wsize.width-205, Wsize.height/2 - 50 + GC.HIGH)).easing(cc.easeBackInOut());
				shakingBack = cc.moveTo(1, cc.p(Wsize.width-195, Wsize.height/2 - 50 + GC.HIGH)).easing(cc.easeBackInOut());
				delayTime   = new cc.DelayTime(0.5);
				break;

			case "set" :
				cc.log("set.");
				shaking     = cc.moveTo(1, cc.p(Wsize.width-205, Wsize.height/2 - 120 + GC.HIGH)).easing(cc.easeBackInOut());
				shakingBack = cc.moveTo(1, cc.p(Wsize.width-195, Wsize.height/2 - 120 + GC.HIGH)).easing(cc.easeBackInOut());
				delayTime   = new cc.DelayTime(0.5);
				break;

			case "about" :
				cc.log("about.");
				shaking     = cc.moveTo(1, cc.p(Wsize.width-205, Wsize.height/2 - 190 + GC.HIGH)).easing(cc.easeBackInOut());
				shakingBack = cc.moveTo(1, cc.p(Wsize.width-195, Wsize.height/2 - 190 + GC.HIGH)).easing(cc.easeBackInOut());
				delayTime   = new cc.DelayTime(0.5);
				break;

			case "rank" :
				cc.log("rank.");
				shaking     = cc.moveTo(1, cc.p(Wsize.width-205, Wsize.height/2 - 260 + GC.HIGH)).easing(cc.easeBackInOut());
				shakingBack = cc.moveTo(1, cc.p(Wsize.width-195, Wsize.height/2 - 260 + GC.HIGH)).easing(cc.easeBackInOut());
				delayTime   = new cc.DelayTime(0.5);
				break;

			default:
				break;
		}
		shakingSeq  = cc.sequence(delayTime, shaking, shakingBack);
		target.runAction(shakingSeq.repeatForever());
	},

	//开始游戏
	startFunc : function(){
		cc.log("startFunc");
		Sound.playEffectBtn();

		var layer = new SelectModelLayer();
		this.addChild(layer, 10);
	},

	storeFunc : function(){
		cc.log("storeFunc.");

		Sound.playEffectBtn();
		var layer = new StoreLayer();
		this.addChild(layer, 10);
	},

	setFunc : function(){
		cc.log("setFunc.");

		Sound.playEffectBtn();
		var layer = new SetLayer();
		this.addChild(layer, 10);
	},

	aboutFunc : function(){
		cc.log("aboutFunc.");

		Sound.playEffectBtn();
		var layer = new AboutLayer();
		this.addChild(layer, 10);
	},

	rankFunc : function(){
		cc.log("rank.");

		Sound.playEffectBtn();
		var layer = new RankLayer();
		this.addChild(layer, 10);
	},

	//切换账号（修改昵称）
	changeNickNameFunc : function () {
		cc.log("Switch Account.");
		Sound.playEffectBtn();

		this.addUserInforLayer();
	},

	//新用户,需要输入昵称
	addUserInforLayer : function () {

		var userInfo = new UserInforLayer();
		userInfo.setDelegate(this);		//设置代理，回调updateNickNameLabel
		this.addChild(userInfo, 1000);
	},

	//使用代理的方法更新昵称标签
	updateNickNameLabel : function (sender) {
		cc.log("WelecomeLayer_updateNickNameLabel");

		this._nickNameLabel.setString(cc.sys.localStorage.getItem(GC.KEY.USERNAME));
	}

});
























