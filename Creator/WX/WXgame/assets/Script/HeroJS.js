/**
 * Created by changhao on 4/14/2018.
 * Brief   :	英雄
 */

var GC = require('GameConfig');
cc.Class({
	extends: cc.Component,

	properties: {
		heroSpr	:	cc.Sprite
	},

	// use this for initialization
	onLoad: function () {
		this._animation = this.getComponent(cc.Animation);
	},

	playAnimationByName: function (_name) {

		var mode = (_name==GC.HERO_ANIMA_NAME.shake || _name==GC.HERO_ANIMA_NAME.walk || _name==GC.HERO_ANIMA_NAME.yao) ? cc.WrapMode.Loop : cc.WrapMode.Normal;

		var state = this._animation.play(_name);
		state.wrapMode = mode;
	},

	getHeroContentSize: function () {
		return this.heroSpr.node.getContentSize();
	}
});