/**
 * Created by HAO on 2017/2/15.
 * Brief   :
 * Version :
 */

var Gold = cc.Class.extend({

	_x				:	0,
	_y				:	0,

	_batchnode		:	null,
	_sprite			:	null,

	_space			:	null,
	_body			:	null,
	_shape			:	null,

	//动作
	_rotatingAction	:	null,

	ctor : function (x, y) {

		this._x = x;
		this._y = y;

		this._batchnode = new cc.SpriteBatchNode(res.gold.png);

		//金币旋转动画
		this._rotatingAction = new cc.RepeatForever(
			new cc.Animate(
				new cc.Animation([0, 1, 2, 3, 4, 5, 6, 7, 8, 9].map(function (i) {
					return cc.spriteFrameCache.getSpriteFrame("gold" + i + ".png");
				}), 0.05)
			)
		);
		this._rotatingAction.retain();

		//熊猫
		this._sprite = new cc.PhysicsSprite("#gold0.png");
		this._batchnode.addChild(this._sprite);
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
		var radius = 0.95 * contentsize.width/2;

		this._body = new cp.Body(0.1, cp.momentForBox(1, contentsize.width, contentsize.height));
		this._body.applyForce(cp.v(0, 150), cp.v(0, 0));
		//this._body.setPos(cc.p(x, y));	//设置物体重心
		this._sprite.setBody(this._body);
		this._sprite.setPosition(x, y);

		var body = this._body;
		body.spriteObj = this;

		this._shape = new cp.CircleShape(this._body, radius, cp.vzero);
		this._shape.setCollisionType(GC.SpriteTag.gold);
		this._shape.setSensor(true);	// 只是调用碰撞机回调函数,并且永远不生成真实的碰撞机

		//初始熊猫动画
		this._sprite.stopAllActions();
		this._sprite.runAction(this._rotatingAction);
	},

	addToTargetLayer : function (space, target) {

		this._space = space;
		space.addBody(this._body);
		space.addShape(this._shape);
		target.addChild(this._batchnode, 5);
	},

	initPos : function (pos) {

		this._sprite.stopAllActions();
		this._sprite.runAction(this._rotatingAction);
		this._sprite.setPosition(pos);
	},

	removeFromLayer : function () {

		//Sound.playEffectEatGold();
		var x = this._sprite.getPositionX();
		var y = this._sprite.getPositionY();
		this._sprite.runAction(
			cc.moveTo(0.8, cc.p(x-200, y+350)).easing(cc.easeBackIn())
		);
	},

	getX  : function () {

		return this._sprite.getPositionX();
	},

	getName : function () {

		return GC.ITEMS.GOLD;
	},

	update : function (dt) {

	}

});