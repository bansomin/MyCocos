/**
 * Created by Bansomin on 4/9/2018.
 * Brief   :	悬浮按钮
 */

cc.Class({
	extends: cc.Component,

	properties: {
		btn :   cc.Sprite
	},

	// use this for initialization
	onLoad: function () {

		this.Wsize = cc.director.getWinSize();
		this.BtnSize = this.btn.node.getContentSize();
		this.btn.node.setPosition(cc.p(this.Wsize.width/2 - this.BtnSize.width/2, 0));
		this.lastPosition = this.btn.node.getPosition();
	},

	onEnable: function () {
		this.btn.node.on(cc.Node.EventType.TOUCH_START, this.startFun, this);
		this.btn.node.on(cc.Node.EventType.TOUCH_MOVE, this.moveFun, this);
		this.btn.node.on(cc.Node.EventType.TOUCH_CANCEL, this.cancelFun, this);
		this.btn.node.on(cc.Node.EventType.TOUCH_END, this.endFun, this);
	},

	onDisable: function () {
		this.btn.node.off(cc.Node.EventType.TOUCH_START, this.startFun, this);
		this.btn.node.off(cc.Node.EventType.TOUCH_MOVE, this.moveFun, this);
		this.btn.node.off(cc.Node.EventType.TOUCH_CANCEL, this.cancelFun, this);
		this.btn.node.off(cc.Node.EventType.TOUCH_END, this.endFun, this);
	},

	startFun: function (_evn) {

		this._isMoving = false;
		this.m_LastPos = _evn.touch.getLocation();
		if(cc.rectContainsPoint(this.btn.node.getBoundingBoxToWorld(), this.m_LastPos)){
			this._isMoving = true;
		}
	},

	moveFun: function (_evn) {

		var pos = _evn.touch.getLocation();
		var x = pos.x - this.m_LastPos.x + this.btn.node.getPositionX();
		var y = pos.y - this.m_LastPos.y + this.btn.node.getPositionY();
		this.btn.node.setPosition(cc.p(x, y));
		this.m_LastPos = pos;
	},

	cancelFun: function (_evn) {
		this.adjustPosition();
	},

	endFun: function (_evn) {

		if(this._isMoving==true){
			this._isMoving = false;
			this.adjustPosition();
		}
	},

	adjustPosition: function () {

		var x = this.btn.node.getPositionX();
		var y = this.btn.node.getPositionY();

		if(Math.abs(this.lastPosition.x)-Math.abs(x)<10 && Math.abs(this.lastPosition.y)-Math.abs(y)<10){	//点击
			cc.log("点击");
			/*
			* to do sm
			* */
		}else {
			cc.log("移动");
			this.lastPosition = cc.p(x, y);
		}

		//按x，按y
		var absX = Math.abs(this.Wsize.width/2 - Math.abs(x));
		var absY = Math.abs(this.Wsize.height/2 - Math.abs(y));
		var isW = absX<absY ? true : false;
		if(x>0 && y>0){
			if(isW==true) {
				x = this.Wsize.width/2 - this.BtnSize.width/2;
				y = y;
			}else {
				x = x;
				y = this.Wsize.height/2 - this.BtnSize.width/2;
			}
		}else if(x>0 && y<=0){
			if(isW==true) {
				x = this.Wsize.width/2 - this.BtnSize.width/2;
				y = y;
			}else {
				x = x;
				y = -this.Wsize.height/2 + this.BtnSize.width/2;
			}
		}else if(x<=0 && y>0){
			if(isW==true) {
				x = -this.Wsize.width/2 + this.BtnSize.width/2;
				y = y;
			}else {
				x = x;
				y = this.Wsize.height/2 - this.BtnSize.width/2;
			}
		}else {
			if(isW==true) {
				x = -this.Wsize.width/2 + this.BtnSize.width/2;
				y = y;
			}else {
				x = x;
				y = -this.Wsize.height/2 + this.BtnSize.width/2;
			}
		}

		this.lastPosition = cc.p(x, y);
		this.btn.node.runAction(
			cc.moveTo(0.3, x, y)
		);
	}
});
