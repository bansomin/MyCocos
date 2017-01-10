/**
 * Created by HAO on 2016/12/12.
 * Brief   : 倒计时界面
 * Version :
 */


var CountDownLayerDelegate = cc.Class.extend({

	init : function(){
	}
});

var CountDownLayer = cc.Layer.extend({

	_bg		:	null,
	_time	:	0,

	ctor : function () {
		this._super();

		this._time = 0;
		this.playSound();

		Wsize = cc.director.getVisibleSize();

		this.init();

		return true;
	},

	init : function () {

		cc.eventManager.addListener({
			event          : cc.EventListener.TOUCH_ONE_BY_ONE,
			swallowTouches : true,
			onTouchBegan   : function (touch, event) {
				return true;
			}
		}, this);

		//var bg = new cc.Sprite("#bg003.png");
		var bg = new cc.Sprite(res.png_bg_action);
		bg.setPosition(Wsize.width/2, Wsize.height/2);
		bg.setScaleX(RCCommon.scaleXRatio);
		this.addChild(bg);


		var grass = new cc.Sprite("#caodi.png");
		grass.setPosition(Wsize.width/2, Wsize.height/4);
		this.addChild(grass);

		var light = new cc.Sprite("#guang.png");
		light.setScale(0, 0);
		light.setPosition(Wsize.width/2, Wsize.height/2);
		this.addChild(light);

		var scale = cc.scaleTo(3, 5, 5);
		light.runAction(scale);

		var sprite = new cc.Sprite();
		sprite.setPosition(Wsize.width/2, Wsize.height/2);
		this.addChild(sprite);

		var animationName = "countdown";
		var anima = cc.animationCache.getAnimation(animationName);
		if (anima == null) {
			anima = GC.prepareAnimation(GC.ANIMATIONTYPE.COUNTDOWN);
			cc.animationCache.addAnimation(anima, animationName);
		}

		var callback = cc.callFunc(this.callbackFunc, this);
		var seq = cc.sequence(anima, callback);

		sprite.runAction(seq);
	},

	//播放倒计时音效
	playSound : function () {

		//播放音效
		SoundManager.playCountDownSound();
		setTimeout(function () {
			if(this._time < 2){
				this.playSound();
			}
			else {
				//播放ReadyGo音效
				//SoundManager.playReadyGoSound();
			}
			this._time ++;
		}.bind(this),1000);
	},

	setDelegate : function (delegate) {
		this._delegate = delegate;
	},

	getDelegate : function () {
		return this._delegate;
	},

	callbackFunc : function (sender) {
		cc.log("CountDownLayer_callbackFunc");

		if (this._delegate && this._delegate.init){
			this._delegate.init(sender);
		}

		this.removeFromParent();
	}

});
