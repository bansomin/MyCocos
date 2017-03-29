/**
 * Created by HAO on 2016/8/25.
 */

var bglayer = null;          //背景层
var gameviewlayer = null;   //游戏层

var MenuViewLayer = cc.Layer.extend({

    ctor : function () {
        this._super();

        Wsize = cc.director.getWinSize();

        this.init();

        return true;
    },

    init : function () {

        var start_item = new cc.MenuItemSprite(
            new cc.Sprite(res.Btnn_png),
            new cc.Sprite(res.Btns_png),
            this.startFunc,
            this
        );
        start_item.attr({
            x   :   Wsize.width/2,
            y   :   Wsize.height/2
        });

        var menu = new cc.Menu(start_item);
        menu.attr({
            x   :   0,
            y   :   0
        });
        this.addChild(menu);

    },

    startFunc : function () {
        cc.log("click StartBtn.");

        this.removeFromParent(true);
        //加载分数提示
        bglayer.addscoreBg();
        //加载玩法提示图片
        bglayer.adddrawGuidtext();

        //开始游戏
        gameviewlayer.startGame();
    }

});

var MenuViewScene = cc.Scene.extend({

	//返回键
	isExitBol       :   false,  //退出标识
	exitLogo        :   null,   //退出图片

    onEnter : function () {
        this._super();

        cc.audioEngine.playMusic(res.bg_music, true);

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

        //加载背景层
        bglayer = new GameViewBackground();
        this.addChild(bglayer, -1);

        //加载游戏层
        gameviewlayer = new GameView();
        this.addChild(gameviewlayer, 5);

        //加工菜单层
        var layer = new MenuViewLayer();
        this.addChild(layer, 10);
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








