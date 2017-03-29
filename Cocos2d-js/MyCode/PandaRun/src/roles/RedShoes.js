/**
 * Created by HAO on 2017/2/16.
 * Brief   : 红鞋，主角使用后，可以加速
 * Version :
 */

var RedShoes = cc.Class.extend({

	_x				:	0,
	_y				:	0,

	_batchnode		:	null,
	_sprite		:	null,

	_space			:	null,
	_body			:	null,
	_shape			:	null,

	_speedUp		:	1000,	//速度
	_unavailable	:	false,
	_continuedTime	:	1000,	//可持续时间

	//动作
	_rotatingAction	:	null,

	ctor : function (x, y, speedUp, continuedTime) {

		this._x = x;
		this._y = y;
		if (continuedTime) {
			this._continuedTime = continuedTime;
		}
		if (speedUp) {
			this._speedUp = speedUp;
		}

		this._batchnode = new cc.SpriteBatchNode(res.redshoes.png);

		//红鞋动作
		this._rotatingAction = new cc.RepeatForever(
			new cc.Animate(
				new cc.Animation([0, 1, 2, 3, 4].map(function (i) {
					return cc.spriteFrameCache.getSpriteFrame("redshoes_0" + i + ".png");
				}), 0.15)
			)
		);
		this._rotatingAction.retain();

		//对象
		this._sprite = new cc.PhysicsSprite("#redshoes_00.png");
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
		cc.log("** RedShoes");

		this.removeFromLayer();
		hero._body.applyImpulse(cp.v(GC.HEROSPEEDUP, 0), cp.v(0, 0));
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

		return GC.ITEMS.DOUBLEJUMP;
	},

	update : function (dt, hero, index) {

	}

});