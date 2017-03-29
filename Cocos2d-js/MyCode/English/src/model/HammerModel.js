/**
 * Created by HAO on 2016/11/25.
 * Brief   :	锤子
 * Version :
 */

var HammerModel = cc.Sprite.extend({

	_hammer		:	null,

	ctor : function () {
		this._super();

		this._hammer = new cc.Sprite("#01.png");
		this.addChild(this._hammer);

		//this.changeTargetAnimation(GC.ANIMATIONTYPE.HAMMER);

		return true;
	},

	//执行动画
	changeTargetAnimation : function (type) {

		var animationName = null;
		var anima = null;

		switch (type){
			case "out" :
				animationName = "animationOut";
				break;
			case "in" :
				animationName = "animationIn";
				break;
			case "hammer" :
				animationName = "animationHammer";
				break;
		}

		//停止所有动作
		this._hammer.stopAllActions();

		anima = cc.animationCache.getAnimation(animationName);
		if (anima==null) {
			anima = GC.prepareAnimation(type);
			cc.animationCache.addAnimation(anima, animationName);
		}

		this._hammer.runAction(anima);
	}

});