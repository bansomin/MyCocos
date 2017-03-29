/**
 * Created by HAO on 2017/2/8.
 * Brief   : 初始化空间、相机、加载单机游戏层、信息栏层
 * Version :
 */

var PlaySingleScene = cc.Scene.extend({

	//游戏状态
	_gameState	:	null,
	//物理空间
	_space		:	null,
	//场景相机
	_gamecamera	:	null,
	//
	_statistics	:	null,

	//返回键
	isExitBol       :   false,  //退出标识
	exitLogo        :   null,   //退出图片

	_playelayer		:	null,
	_hublayer		:	null,

	//初始化游戏状态
	initGameState : function () {

		var gameover = false;
		return {
			get gameover(){
				return gameover
			},
			set gameover(state){
				gameover = state;
			}
		};
	},

	//初始化空间
	initSpace : function () {

		this._space = new cp.Space();				//创建物理空间
		this._space.gravity= cp.v(0, -1500);		//设置空间的重力向量(二维矢量类型)
		var staticBody = this._space.staticBody;	//获得从物理空间中获得静态物体
		//设置空间边界
		// var walls = [
		// 	new cp.SegmentShape(staticBody, cp.v(0, 0), cp.v(Wsize.width, 0), 0),
		// 	new cp.SegmentShape(staticBody, cp.v(0, Wsize.height), cp.v(Wsize.width, Wsize.height), 0),
		// 	new cp.SegmentShape(staticBody, cp.v(0, 0),	cp.v(0, Wsize.height), 0),
		// 	new cp.SegmentShape(staticBody, cp.v(Wsize.width, 0), cp.v(Wsize.width, Wsize.height), 0)
		// ];
		// for (var i = 0; i < walls.length; i++) {
		// 	var shape = walls[i];
		// 	shape.setElasticity(1);				//设置弹性系数
		// 	shape.setFriction(1);				//摩擦系数
		// 	this._space.addStaticShape(shape);	//静态物体与形状关联起来
		// }

		var wallBottom = new cp.SegmentShape(
			staticBody,
			cp.v(0, GC.physics.groundHeight),
			cp.v(4294967295, GC.physics.groundHeight),
			0
		);
		wallBottom.setCollisionType(GC.SpriteTag.ground);
		this._space.addStaticShape(wallBottom);

		// this._space.addCollisionHandler(
		// 	GC.SpriteTag.ground,
		// 	GC.SpriteTag.player,
		// 	this.collisionGround.bind(this), null, null, null
		// );

	},

	//
	initStatistics : function () {
		cc.log("initStatistics");

		var coins = 0;
		var self = this;
		return{
			set coins(coin){
				coins = coin;
			},

			get coins(){
				return coins;
			},

			get score(){
				return this.coins + this.meter;
			},

			get meter(){
				return parseInt(self._gamecamera.x/100);
			}
		};
	},

	initGameCamera : function () {

		var centerPos = cc.p(-Wsize.width / 2, 0);
		var listeners = [];
		var dirty = true;
		return {
			addListener: function (listener) {
				listeners.push(listener);
			},

			set x(x) {
				centerPos.x = x;
				dirty = true;
			},
			get x() {
				return centerPos.x;
			},

			set y(y) {
				centerPos.y = y;
				dirty = true;
			},
			get y() {
				return centerPos.y;
			},

			set pos(pos) {
				centerPos.x = pos.x;
				centerPos.y = pos.y;
				dirty = true;
			},

			update:function () {
				if (dirty) {
					listeners.forEach(function (listener) {
						listener(centerPos);
					});
					dirty = false;
				}
			}
		};
	},

	update : function (dt) {
		//cc.log("Scene_update");

		this._space.step(dt);
		this._gamecamera.update();	//
		this._playelayer.update(dt);	//相机的移动
		this._hublayer.update(dt);

		var eyex = this._playelayer.getEyeX();
		var eyey = this._playelayer.getEyeY();
		// if (this._playelayer._hero._sprite.getPositionY()<800) {
		// 	this._playelayer.setPosition(cc.p(-eyex, -eyey/2.6));
		// }
		// else {
		// 	this._playelayer.setPosition(cc.p(-eyex, -eyey));
		// }

		// this.nearBgLayer.setPositionY(-eyey/5);
		// this.farBgLayer.setPositionY(-eyey/10);

	},

	heroJump : function (sender) {
		cc.log("PlaySingleScene_heroJump");

		if (this._playelayer._hero._state==GC.ROLESTATE.RUN) {
			this._playelayer._hero.heroJumpAction();
			new MessageBox().addTips("单跳", function () {});
		}
		else if ((this._playelayer._hero._state==GC.ROLESTATE.JUMPUP || this._playelayer._hero._state==GC.ROLESTATE.JUMPDOWN) && !this._playelayer._hero._doubleJumpAlready) {
			this._playelayer._hero.heroDoubleJumpAction();
			new MessageBox().addTips("连跳", function () {});
		}
	},

	collisionGround : function (arbiter, space) {

		cc.log("collisionGround");
	},

	onEnter : function () {
		this._super();

		Wsize = cc.director.getWinSize();

		//初始化数据
		this._gameState = this.initGameState();
		this.initSpace();
		this._statistics = this.initStatistics();
		this._gamecamera = this.initGameCamera();

		//背景层
		this.farBgLayer = new GameBackgroundLayer(this._gamecamera, res.bg.bg1, {
			scaleX :　2,
			scaleY : 10
		});
		this.nearBgLayer = new GameBackgroundLayer(this._gamecamera, res.bg.bg2, {
			scaleX :　3,
			scaleY : 10
		});
		this.addChild(this.farBgLayer, -1);
		this.addChild(this.nearBgLayer,-1);

		//游戏层(英雄)
		this._playelayer = new PlaySingleLayer(this._gamecamera, this._space, this._statistics);
		this.addChild(this._playelayer);

		//加载信息栏(游戏相关信息)
		this._hublayer = new HubLayer(this._playelayer._hero, this._statistics);
		this._hublayer.setDelegate(this);
		this.addChild(this._hublayer);

		/***************************碰撞检测****************************/

		//金币
		this._space.addCollisionHandler(
			GC.SpriteTag.player,
			GC.SpriteTag.gold,
			function (arbiter, space) {
				var shapes = arbiter.getShapes();
				var hero = shapes[0].body.spriteObj;
				var item = shapes[1].body.spriteObj;
				item.removeFromLayer();
				this._statistics.coins += 1;
			}.bind(this), null, null, null
		);

		//等效物品
		this._space.addCollisionHandler(
			GC.SpriteTag.player,
			GC.SpriteTag.inventory,
			function (arbiter, space) {
				var shapes = arbiter.getShapes();
				var hero = shapes[0].body.spriteObj;
				var item = shapes[1].body.spriteObj;
				item.equip(hero, this);
			}.bind(this), null, null, null
		);

		//地面碰撞
		// this._space.addCollisionHandler(
		// 	GC.SpriteTag.ground,
		// 	GC.SpriteTag.player,
		// 	this.collisionGround.bind(this), null, null, null
		// );




		var me = this;
		//Android返回键监听
		cc.eventManager.addListener({
			event : cc.EventListener.KEYBOARD,
			onKeyReleased : function (keyCode, event) {
				if (keyCode == cc.KEY.back) {
					cc.log("back.");
					me.prepareEndFunc();
				}
				else if (keyCode == cc.KEY.home) {
					cc.log("home.");
				}
			}
		}, this);

		//更新
		this.scheduleUpdate();
	},

	prepareEndFunc : function () {
		cc.log("prepareEndFunc");

		if (!this.isExitBol) {
			this.isExitBol = true;  //准备退出
			//2秒内未按下键,则启动定时器取消掉刚才执行的任务
			this.exitLogo = new cc.Sprite("#exit.png");
			this.exitLogo.setPosition(cc.p(cc.winSize.width/2, cc.winSize.height/4));
			this.addChild(this.exitLogo, 10000);

			var action = cc.sequence(cc.fadeOut(2), cc.callFunc(function () {
				this.isExitBol = false;
			}, this));
			this.exitLogo.runAction(action);
		}
		else {
			cc.director.end();
		}}
	}

);