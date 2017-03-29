/**
 * Created by HAO on 2017/2/16.
 * Brief   : 磁铁
 * Version :
 */

var Magnet = cc.Class.extend({

	_x				:	0,
	_y				:	0,

	_batchnode		:	null,
	_sprite			:	null,

	_space			:	null,
	_body			:	null,
	_shape			:	null,

	_golds			:	null,
	_statistics		:	null,

	_unavailable	:	false,
	_continuedTime	:	1000,	//可持续时间

	//动作
	_rotatingAction	:	null,

	ctor : function (x, y, golds, statistics, continuedTime) {

		this._x = x;
		this._y = y;
		this._golds = golds;
		this._statistics = statistics;

		if (continuedTime) {
			this._continuedTime = continuedTime;
		}

		this._batchnode = new cc.SpriteBatchNode(res.magnet.png);

		//磁铁动作
		this._rotatingAction = new cc.RepeatForever(
			new cc.Animate(
				new cc.Animation([1, 2, 3, 4, 5, 6, 7, 8].map(function (i) {
					return cc.spriteFrameCache.getSpriteFrame("magnet_0" + i + ".png");
				}), 0.08)
			)
		);
		this._rotatingAction.retain();

		//对象
		this._sprite = new cc.PhysicsSprite("#magnet_01.png");
		this._batchnode.addChild(this._sprite);
		this._sprite.setScale(0.4);
		this._sprite.retain();
		this._batchnode.retain();

		/**
		 cp.Body	:	创建一个动态物体(参数质量, 惯性值)
		 cp.momentForBox : 计算多边形的惯性值(惯性力矩, 物体的宽度, 物体的高度)
		 **/
		/**
		 applyForce			:	力，循序渐进
		 applyImpulse		:	速度，叠加
		 setLinearVelocity	:	一触即发
		 */
		var contentsize = this._sprite.getContentSize();
		var radius = 0.95 * contentsize.width/4;

		var body = new cp.Body(0.1, cp.momentForBox(Number.POSITIVE_INFINITY, contentsize.width, contentsize.height));
		body.applyForce(cp.v(0, 150), cp.v(0, 0));
		//body.setPos(cc.p(x, y));	//设置物体重心
		this._sprite.setBody(body);
		this._sprite.setPosition(x, y);
		body.spriteObj = this;
		this._body = body;

		this._shape = new cp.CircleShape(body, radius, cp.vzero);
		this._shape.setCollisionType(GC.SpriteTag.inventory);
		this._shape.setSensor(true);	// 只是调用碰撞机回调函数,并且永远不生成真实的碰撞机

		//初始鞋子动画
		this._sprite.stopAllActions();
		this._sprite.runAction(this._rotatingAction);
	},

	addToTargetLayer : function (space, target) {

		this._space = space;
		space.addBody(this._body);
		space.addShape(this._shape);
		target.addChild(this._batchnode, 10);
	},

	initPos : function (pos) {

		this._sprite.stopAllActions();
		this._sprite.runAction(this._rotatingAction);
		this._sprite.setPosition(pos);
	},

	equip : function (hero) {
		cc.log("** Magnet");

		this.removeFromLayer();
		setTimeout(function () {
			hero.removeFromInventory(this);
		}.bind(this), this._continuedTime);
	},

	removeFromLayer : function () {

		var x = this._sprite.getPositionX();
		var y = this._sprite.getPositionY();
		this._sprite.runAction(
			cc.moveTo(0.5, cc.p(x+200, y+300)).easing(cc.easeBackIn())
		);
	},

	getX  : function () {

		return this._sprite.getPositionX();
	},

	getShape : function () {

		return this._shape;
	},

	getName : function () {

		return GC.ITEMS.MAGNET;
	},

	update : function (dt, hero, index) {

		var heroPos = hero._sprite.getPosition();
		heroPos.x = hero._sprite.height * Math.cos(index * Math.PI / 12);
		heroPos.y = hero._sprite.height * Math.sin(index * Math.PI / 12);
		this._sprite.setPosition(heroPos);


	}

});

