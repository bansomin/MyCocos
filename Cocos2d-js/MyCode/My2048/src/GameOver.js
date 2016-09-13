/**
 * Created by Bansomin on 5/26/2016.
 */

var GameOverLayer = cc.LayerColor.extend({

    ctor : function () {
        this._super(cc.color(158, 158, 158, 255));
        Wsize = cc.winSize;
        this.init();
        return true;
    },

    init : function () {
        printf("GameOver.");

        var label = new cc.LabelTTF("游戏结束", "Arial", 80);
        label.setPosition(Wsize.width/2, Wsize.height/2+200);
        this.addChild(label);

        var label_rest = new cc.LabelTTF("重新开始", "Arial", 60);
        var item_rest = new cc.MenuItemLabel(label_rest, this.restartGameFunc, this);
        item_rest.setPosition(Wsize.width/2, Wsize.height/2);

        var label_exit = new cc.LabelTTF("退出游戏", "Arial", 60);
        var item_exit = new cc.MenuItemLabel(label_exit, this.exitGameFunc, this);
        item_exit.setPosition(Wsize.width/2, Wsize.height/3);

        var menu = new cc.Menu(item_rest, item_exit);
        menu.attr({
            x   :   0,
            y   :   0,
            anchorX :   0,
            anchorY :   0
        });
        this.addChild(menu);
    },

    restartGameFunc : function () {
        printf("restartGameFunc");
        cc.director.runScene(new HelloWorldScene());
    },

    exitGameFunc : function () {
        printf("exitGameFunc.");
        cc.director.runScene(new HelloWorldScene());
    }
});

var GameOver = cc.Scene.extend({

    onEnter : function () {
        this._super();

        var layer = new GameOverLayer();
        this.addChild(layer);
    }
});



















