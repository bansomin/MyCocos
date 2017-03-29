/**
 * Created by HAO on 2016/12/5.
 * Brief   : 音乐图标及其动画
 * Version :
 */

var SoundButtonUI = cc.MenuItemToggle.extend({

	_soundSpr	:	null,

	ctor : function () {
		this._super();

		this._soundSpr = new cc.Sprite("#soundOn0000.png");
		this._super(new cc.MenuItemSprite(this._soundSpr, null, null), new cc.MenuItemImage("#soundOff.png", null, null));
		this.setCallback(this.soundOnOffFunc, this);

		this.changeTargetAnimation(GC.ANIMATIONTYPE.SOUND);
	},

	changeTargetAnimation : function (type) {

		//未静音并且有背景音乐播放
		if (RCCommon.IsMusicOn && cc.audioEngine.isMusicPlaying()) {

			var anima = cc.animationCache.getAnimation("sound");
			if (anima==null) {
				anima = GC.prepareAnimation(type);
				cc.animationCache.addAnimation(anima, "sound");
			}

			this._soundSpr.runAction(anima.repeatForever());
		}
	},

	soundOnOffFunc : function () {
		//SoundManager
		SoundManager.toggleOnOff();
	}

});