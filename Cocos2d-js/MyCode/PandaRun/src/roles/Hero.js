/**
 * Created by HAO on 2017/2/9.
 * Brief   : 主角角色的相关操作
 * Version :
 */

var Hero = cc.Class.extend({

	_x				:	0,
	_y				:	0,

	_batchnode		:	null,
	_sprite			:	null,

	_space			:	null,
	_body			:	null,
	_shape			:	null,

	_speedX			:	0,
	_heroRunSpeed	:	500,

	_inventory		:	[],

	//动作
	_runningAction	:	null,
	_jumpUpAction	:	null,
	_jumpDownAction	:	null,

	_state	:	GC.ROLESTATE.RUN,
	_isJump	:	false,		//主角是否跳起
	_doubleJumpAlready	:	false,

	ctor : function (x, y) {

		this._x = x;
		this._y = y;

		this._batchnode = new cc.SpriteBatchNode(res.panda.png);

		//英雄相关动作
		//跑
		this._runningAction = new cc.RepeatForever(
			new cc.Animate(
				new cc.Animation([1, 2, 3, 4, 5, 6, 7, 8].map(function (i) {
					return cc.spriteFrameCache.getSpriteFrame("panda_run_0" + i + ".png");
				}), 0.05)
			)
		);
		this._runningAction.retain();

		//英雄相关动作
		//上跳
		this._jumpUpAction = new cc.RepeatForever(
			new cc.Animate(
				new cc.Animation([1, 2, 3, 4, 5, 6, 7, 8].map(function (i) {
					return cc.spriteFrameCache.getSpriteFrame("panda_jump_0" + i + ".png");
				}), 0.08)
			)
		);
		this._jumpUpAction.retain();

		//下跳
		this._jumpDownAction = new cc.RepeatForever(
			new cc.Animate(
				new cc.Animation([1, 2, 3, 4, 5, 6, 7, 8].map(function (i) {
					return cc.spriteFrameCache.getSpriteFrame("panda_roll_0" + i + ".png");
				}), 0.08)
			)
		);
		this._jumpDownAction.retain();

		//熊猫
		this._sprite = new cc.PhysicsSprite("#panda_run_01.png");
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

		var body = new cp.Body(1, cp.momentForBox(1, contentsize.width, contentsize.height));
		body.applyImpulse(cp.v(this._heroRunSpeed, 0), cp.v(0, 0));
		//body.setPos(cc.p(x, y)); //设置物体重心
		this._sprite.setBody(body);
		this._sprite.setPosition(x, y);
		body.spriteObj = this;
		this._body = body;

		this._shape = new cp.BoxShape(body, contentsize.width - 14, contentsize.height-10);
		this._shape.setCollisionType(GC.SpriteTag.player);
		this._shape.setElasticity(0.1);
		this._shape.setFriction(0.1);

		//初始熊猫动画
		this._sprite.stopAllActions();
		this._sprite.runAction(this._runningAction);
		this._state = GC.ROLESTATE.RUN;
	},

	addToTargetLayer : function (space, target) {

		this._space = space;
		space.addBody(this._body);
		space.addShape(this._shape);
		target.addChild(this._batchnode, 15);
	},
	
	//主角单跳
	heroJumpAction : function () {
		cc.log("heroJumpAction");

		this._isJump = true;
		if (this._state == GC.ROLESTATE.RUN) {					//跳跃（向上时）
			this._body.applyImpulse(cp.v(0, 800), cp.v(0, 0));
			this._sprite.stopAllActions();
			this._sprite.runAction(this._jumpUpAction);
			this._state = GC.ROLESTATE.JUMPUP;
		}
	},

	//主角双连跳
	heroDoubleJumpAction : function () {

		//双跳准备好
		if (this._state == GC.ROLESTATE.JUMPUP) {
			this._doubleJumpAlready = true;
			this._body.applyImpulse(cp.v(0, 500), cp.v(0, 0));
			this._sprite.stopAllActions();
			this._sprite.runAction(this._jumpUpAction);
		}
		else if (this._state == GC.ROLESTATE.JUMPDOWN) {
			this._doubleJumpAlready = true;
			this._body.applyImpulse(cp.v(0, 800), cp.v(0, 0));
			this._sprite.stopAllActions();
			this._sprite.runAction(this._jumpUpAction);
		}
	},

	speedUp : function () {
		this._speedX = 5;
		this._body.applyImpulse(cp.v(this._speedX, 0), cp.v(0, 0));
	},

	addToInventory : function (obj) {
		this._inventory.push(obj);
	},

	removeFromInventory : function (obj) {

		for (var i = 0; i < this._inventory.length; i++) {
			if (this._inventory[i]==obj) {
				this._inventory.splice(i, 1);
				break;
			}
		}
	},

	getX : function () {

		return this._sprite.getPositionX();
	},

	getY : function () {

		return this._sprite.getPositionY();
	},

	update : function (dt) {
		//cc.log("Hero_update");

		var vel = this._body.getVel();
		if (this._state.startsWith(GC.ROLESTATE.JUMPUP)) {	//向上升的过程
			if (vel.y < 0.1) {								//到达最高点，开始下降
				this._state = GC.ROLESTATE.JUMPDOWN;		//转换状态
				this._sprite.stopAllActions();
				this._sprite.runAction(this._jumpDownAction);	//下落动作
			}
		}
		else if (this._state == GC.ROLESTATE.JUMPDOWN) {	//下落过程中
			if (vel.y == 0) {								//到达地面时转换动作
				this._isJump = false;
				this._doubleJumpAlready =false;
				this._state = GC.ROLESTATE.RUN;
				this._sprite.stopAllActions();
				this._sprite.runAction(this._runningAction);	//奔跑动作
			}
		}
	}

});