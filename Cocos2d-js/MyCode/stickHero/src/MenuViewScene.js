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

    onEnter : function () {
        this._super();

        cc.audioEngine.playMusic(res.bg_music, true);

        //加载背景层
        bglayer = new GameViewBackground();
        this.addChild(bglayer, -1);

        //加载游戏层
        gameviewlayer = new GameView();
        this.addChild(gameviewlayer, 5);

        //加工菜单层
        var layer = new MenuViewLayer();
        this.addChild(layer, 10);
    }
});








