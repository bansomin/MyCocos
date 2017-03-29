/**
 * Created by HAO on 2017/2/15.
 * Brief   : 创建平台
 * Version :
 */


var Platform = cc.Class.extend({

	_batchnode		:	null,
	_platformSpr	:	null,
	_length			:	0,
	_width			:	null,	//平台宽度

	_space			:	null,
	_body			:	null,
	_shape			:	null,

	ctor : function (x, y, length) {

		this._length = length;

		this._batchnode = new cc.SpriteBatchNode(res.platform.png);

		//熊猫
		this._platformSpr = new cc.PhysicsSprite(cc.spriteFrameCache.getSpriteFrame("platform_"+ length +".png"));
		this._batchnode.addChild(this._platformSpr);
		this._platformSpr.retain();
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
		this._contentsize = this._platformSpr.getContentSize();
		x += this._contentsize.width/2;

		this._body = new cp.StaticBody();
		this._body.setPos(cc.p(x, y));	//是设置物体重心

		this._shape = new cp.BoxShape(this._body, this._contentsize.width, this._contentsize.height);
		this._shape.setCollisionType(GC.SpriteTag.platform);
		this._shape.setElasticity(0);

		this._platformSpr.setBody(this._body);
		this._platformSpr.setPosition(x, y);
	},

	addToTargetLayer : function (space, target) {

		this._space = space;
		//space.addBody(this._body);
		space.addStaticShape(this._shape);
		target.addChild(this._batchnode, 1);
	},

	removeFromLayer : function () {

		this._space.removeShape(this._shape);
		this._platformSpr.removeFromParent();
		this._batchnode.removeFromParent();
	},

	getLastX : function () {

		return this._platformSpr.getPositionX() + this._contentsize.width/2;
	},

	getX  : function () {

		return this._platformSpr.getPositionX() - this._contentsize.width/2;
	},

	getY : function () {

		return this._platformSpr.getPositionY();
	}

});