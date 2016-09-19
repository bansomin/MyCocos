
var HelloWorldLayer = cc.Layer.extend({

    //返回键
    isExitBol       :   false,  //退出标识
    exitLogo        :   null,   //退出图片

    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        var helloLabel = new cc.LabelTTF("Hello World", "Arial", 38);
        // position the label on the center of the screen
        helloLabel.x = size.width / 2;
        helloLabel.y = size.height / 2 + 200;
        // add the label as a child to this layer
        this.addChild(helloLabel, 5);

        // add "HelloWorld" splash screen"
        this.sprite = new cc.Sprite(res.HelloWorld_png);
        this.sprite.attr({
            x: size.width / 2,
            y: size.height / 2
        });
        this.addChild(this.sprite, 0);

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

        return true;
    },

    prepareEndFunc : function () {
        cc.log("prepareEndFunc");

        if (!this.isExitBol) {
            this.isExitBol = true;  //准备退出
            //2秒内未按下键,则启动定时器取消掉刚才执行的任务
            this.exitLogo = new cc.Sprite(res.exit);
            this.exitLogo.setPosition(cc.p(cc.winSize.width/2, cc.winSize.height/2));
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

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

