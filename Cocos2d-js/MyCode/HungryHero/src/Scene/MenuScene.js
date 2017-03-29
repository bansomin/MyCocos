/**
 * Created by HAO on 2016/3/31.
 */

var MenuLayer = cc.Layer.extend({

    _hero     :   null,
    _playBtn  :   null,
    _aboutBtn :   null,

    ctor : function(){
        this._super();

        var Wsize = cc.director.getWinSize();

        //创建层
        var layer = new cc.Layer();
        this.addChild(layer, -1);

        //背景
        var bg = new cc.Sprite(res.bgWelcome_jpg);
        bg.attr({
            x   :   Wsize.width/2,
            y   :   Wsize.height/2
        });
        layer.addChild(bg, -1);

        //标题
        var title = new cc.Sprite("#welcome_title.png");
        title.attr({
            x   :   800,
            y   :   555
        });
        layer.addChild(title, 1);

        //英雄
        this._hero = new cc.Sprite("#welcome_hero.png");
        this._hero.attr({
            x   :   -this._hero.width/2,
            y   :   400
        });
        layer.addChild(this._hero, 1);
        var action  = cc.moveTo(2, cc.p(this._hero.width/2 + 100, this._hero.y)).easing(cc.easeOut(2));
        this._hero.runAction(action);

        this._playBtn = new cc.MenuItemImage("#welcome_playButton.png","#welcome_playButton.png", this.playFunc);
        this._playBtn.attr({
            x   :   700,
            y   :   350
        });
        this._aboutBtn = new cc.MenuItemImage("#welcome_aboutButton.png","#welcome_aboutButton.png", this.aboutFunc);
        this._aboutBtn.attr({
            x   :   500,
            y   :   350
        });

        //Ui--音乐图标（动画--切换）
        var soundButton = new SoundButton();
        soundButton.attr({
            x   :   45,
            y   :   Wsize.height-45
        });

        var menu = new cc.Menu(this._playBtn, this._aboutBtn, soundButton);
        menu.attr({     //不设置menu位置，则自动屏幕居中
            x   :   0,
            y   :   0
        });
        layer.addChild(menu, 1);

        //加载音乐图标和播放音乐
        Sound.playMenuBgMusic();
        this.scheduleUpdate();

        return true;
    },

    //点击开始按钮
    playFunc : function(){
        cc.log("playFunc.");
        Sound.playCoffee();
        cc.director.pushScene(new GameScene());
        //cc.director.runScene(new GameScene());
    },

    //点击关于按钮
    aboutFunc : function(){
        cc.log("aboutFunc.");
        Sound.playMushroom();
        //进入about场景
        cc.director.pushScene(new AboutScene());
    },

    //实现动画的上下移动
    update : function(){
        var currentDate = new Date();
        this._hero.y     = 400 + (Math.cos(currentDate.getTime() * 0.002)) * 25;
        this._playBtn.y  = 350 + (Math.cos(currentDate.getTime() * 0.002)) * 10;
        this._aboutBtn.y = 250 + (Math.cos(currentDate.getTime() * 0.003)) * 10;
    }
});

var MenuScene = cc.Scene.extend({

	//返回键
	isExitBol       :   false,  //退出标识
	exitLogo        :   null,   //退出图片

	onEnter : function () {
        this._super();

        var layer = new MenuLayer();
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




