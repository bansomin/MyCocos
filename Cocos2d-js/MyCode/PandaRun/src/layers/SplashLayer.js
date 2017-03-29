/**
 * Created by HAO on 2017/2/2.
 * Brief   : 加载开场logo,场景跳转
 * Version :
 */

var SplashLayer = cc.Layer.extend({

	ctor : function () {
		this._super();

		//加载背景及其预加载资源
		var open = new GameOpeningLayer();
		this.addChild(open);

		//3s后进入到欢迎界面
		setTimeout(function () {
			cc.director.runScene(new cc.TransitionFade(0.5, new WelecomeScene()));
		}.bind(this), 3000);

		return true;
	}
});