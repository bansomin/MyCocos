/**
 * Created by HAO on 2017/2/8.
 * Brief   : 添加主角
 * Version :
 */

var PlaySingleLayer = cc.Layer.extend({

	_hero		:	null,

	_space		:	null,
	_gamecamera		:	null,

	_platformGenerator	:	null,
	_objects			: 	[],
	_invGenerators		:	[],

	_playerPosOfScene: {
		x: 230,
		y: 250
	},

	ctor : function (camera, space, statistics) {
		this._super();

		var self = this;
		this._space = space;
		this._gamecamera = camera;

		Wsize = cc.director.getWinSize();

		//相机
		this._gamecamera.addListener(function (pos) {
			self.setPosition(cc.p(-pos.x, -pos.y));
		});

		//加英雄
		this._hero = new Hero(Wsize.width/2, Wsize.height/2);
		this.addRole(this._hero);

		/**********************测试代码*************************/
		// var goldTest = new Gold(Wsize.width/2, Wsize.height/2);
		// this.addRole(goldTest);
		// var platformTest = new Platform(Wsize.width/2, Wsize.height/4, parseInt(Math.random()*4));
		// this.addRole(platformTest);
		// var blueShoeTest = new BlueShoes(Wsize.width/2, Wsize.height/2);
		// this.addRole(blueShoeTest);
		// var redShoeTest = new RedShoes(Wsize.width/2, Wsize.height/4);
		// this.addRole(redShoeTest);
		//创建蓝鞋
		//var blueShoe = new ObjectRandomGenerator(this);
		//创建磁铁
		// var magnet = new Magnet(Wsize.width/2, Wsize.height/2);
		// this.addRole(magnet);
		/**********************测试代码*************************/

		//创建金币并存储到_objects中
		var goldGenerator = new ObjectShapedGenerator(this);
		//创建平台(true:创建一个或两个)
		this._platformGenerator = new PlatformGenerator(this, true);

		//方式一
		// var redShoe = new ObjectRandomGenerator(this, function () {
		// 	return function (x, y) {
		// 		return new RedShoes(x, y, null, (1500 * 1500 * Math.random()));
		// 	}
		// }(), {height: 150, gap: 500});

		//方式二
		// var redShoe = new ObjectRandomGenerator(this, function (x, y) {
		// 	return new RedShoes(x, y, null, (1500 * 1500 * Math.random()));
		// }, {height: 150, gap: 500});

		/*
		* 	new ObjectRandomGenerator(this, function () {
		 var item = new RedShoes(-100, -100)
		 return function (x, y) {
		 item._sprite.setPosition(x, y);
		 return item;
		 }
		 }(), {height: 150, gap: 500})
		 */

		this._invGenerators = [
			//所有金币
			goldGenerator,
			//创建蓝鞋双跳跃
			new ObjectRandomGenerator(this),
			//创建红鞋的加速
			new ObjectRandomGenerator(this, function () {
				var item = new RedShoes(-100, -100);
				return function (x, y) {
					item._continuedTime = 1500*1500*Math.random();
					item._sprite.setPosition(x, y);
					return item;
				}
			}(), {height: 150, gap: 1500}),
			//创建磁铁
			new ObjectRandomGenerator(this, function () {
				var item = new Magnet(-100, -100, goldGenerator._gold, statistics);
				return function (x, y) {
					item._continuedTime = 5000 + 3000*Math.random();
					item._sprite.setPosition(x, y);
					return item;
				}
			}(), {height: 170, gap: 2800})
			// //创建红鞋的加速
			// new ObjectRandomGenerator(this, function (x, y) {
			// 	return new RedShoes(x, y, null, (1500 * 1500 * Math.random()));
			// }, {height: 150, gap: 500}),
			// //创建磁铁
			// new ObjectRandomGenerator(this, function (x, y) {
			// 	return new Magnet(x, y, goldGenerator, (5000 + 3000 * Math.random()));
			// }, {height: 170, gap: 800})
		];

		cc.eventManager.addListener({
			event          : cc.EventListener.TOUCH_ONE_BY_ONE,
			swallowTouches : true,
			onTouchBegan   : this.onTouchBegan.bind(this)
		}, this);

		return true;
	},

	onTouchBegan : function (touch, event) {
		cc.log("playSingleLayer_onTouchBegan.");

		return true;
	},

	addRole: function (role) {
		role.addToTargetLayer(this._space, this);
	},

	getEyeX : function () {
		//return this._hero._sprite.getPositionX() - this._playerPosOfScene.x;
		return this._hero._sprite.getPositionX() - Wsize.width/2;
	},

	getEyeY : function () {
		return this._hero._sprite.getPositionY() - Wsize.height/2;
	},

	update : function (dt) {

		//主角更新
		this._hero.update(dt);

		var platform = this._platformGenerator.update(dt);
		this._invGenerators.forEach(function (obj) {
			obj.generate(platform);
		});

		//相机的跟随
		var camerax = this._hero._sprite.getPositionX() - Wsize.width/2 - this._gamecamera.x;
		this._gamecamera.x += camerax;
		var cameray = Math.min(Math.max(this._hero._sprite.getPositionY() - Wsize.height/2, 0) - this._gamecamera.y, Wsize.height);
		if (cameray>0) {
			this._gamecamera.y += Math.min(cameray, 1);
		}
		else if (cameray<0) {
			this._gamecamera.y += Math.max(cameray, -2);
		}
	}

});