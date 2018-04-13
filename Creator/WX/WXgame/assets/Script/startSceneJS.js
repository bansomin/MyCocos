/**
 * Created by changhao on 4/13/2018.
 * Brief   :
 */

var MusicManager = require('MusicManager');
cc.Class({
	extends: cc.Component,

	properties: {

	},

	// use this for initialization
	onLoad: function () {

		var scene = cc.director.getScene().getChildByName('startScene');
		scene.getChildByName('tipsLabel').getComponent(cc.Label).string = "测试";

		this.initData();
	},

	initData: function () {

		Global.musicMgr = new MusicManager();
		Global.musicMgr.playBGM();
	},

	onClickStartBtn: function (evn, type) {
		Global.musicMgr.playClickSound();

		cc.director.preloadScene(""

		);
	}
});