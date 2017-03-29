/**
 * Created by HAO on 2016/12/8.
 * Brief   : 开始场景
 * Version :
 */

var StartScene = cc.Scene.extend({

	//返回键
	isExitBol       :   false,  //退出标识
	exitLogo        :   null,   //退出图片

	onEnter:function () {
		this._super();

		cc.spriteFrameCache.addSpriteFrames("res/pic/graph.plist");

		var layer = new StartLayer();
		this.addChild(layer);

		var me = this;
		//Android返回键监听
		cc.eventManager.addListener({
			event : cc.EventListener.KEYBOARD,
			onKeyReleased : function (keyCode, event) {
				if (keyCode == cc.KEY.back) {
					cc.log("back.");
					me.prepareEndFunc();
				}
				else if (keyCode == cc.KEY.home) {
					cc.log("home.");
				}
			}
		}, this);

	},

	prepareEndFunc : function () {
		cc.log("prepareEndFunc");

		if (!this.isExitBol) {
			this.isExitBol = true;  //准备退出
			//2秒内未按下键,则启动定时器取消掉刚才执行的任务
			this.exitLogo = new cc.Sprite(res.png_exit);
			this.exitLogo.setPosition(cc.p(cc.winSize.width/2, cc.winSize.height/4));
			this.addChild(this.exitLogo, 10000);

			var action = cc.sequence(cc.fadeOut(2), cc.callFunc(function () {
				this.isExitBol = false;
			}, this));
			this.exitLogo.runAction(action);
		}
		else {
			cc.director.end();
		}
	}

});