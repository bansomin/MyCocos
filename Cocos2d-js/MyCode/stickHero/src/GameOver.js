/**
 * Created by HAO on 2016/8/26.
 */

var Wsize = null;

var GameOver = cc.Layer.extend({

    ctor : function () {
        this._super();

        Wsize = cc.director.getWinSize();

        //添加有色层
        var colorlayer = new cc.LayerColor(cc.color(125, 125, 125, 125));
        colorlayer.setContentSize(Wsize.width, Wsize.height);
        colorlayer.ignoreAnchor = false;
        colorlayer.attr({
            x   :   Wsize.width/2,
            y   :   Wsize.height/2,
            anchorX :   0.5,
            anchorY :   0.5
        });
        this.addChild(colorlayer);

        var item_restart = new cc.MenuItemSprite(
            new cc.Sprite(res.Restart_png),
            new cc.Sprite(res.Restart_png),
            this.restartFunc,
            this
        );

        var item_home = new cc.MenuItemSprite(
            new cc.Sprite(res.Home_png),
            new cc.Sprite(res.Home_png),
            this.homeFunc,
            this
        );

        var item_share = new cc.MenuItemSprite(
            new cc.Sprite(res.ShareBtn),
            new cc.Sprite(res.ShareBtn),
            this.shareFunc,
            this
        );

        item_restart.setPosition(cc.p(Wsize.width/2 - 80, Wsize.height/2 + 80));
        item_home.setPosition(cc.p(Wsize.width/2 + 80, Wsize.height/2 + 80));
        item_share.setPosition(cc.p(Wsize.width/2, Wsize.height/2 - 80));

        var menu = new cc.Menu(item_restart, item_home, item_share);
        //menu.alignItemsVertically();
        menu.attr({
            x   :   0,
            y   :   0
        });
        this.addChild(menu);

        //显示分数
        this.showScore(GC.CUR_SCORE);

        return true;
    },

    restartFunc : function () {
        cc.log("GO_restartFunc");

        this.removeFromParent(true);

        //当前分数置0
        GC.CUR_SCORE = 0;
        GC.scaleSpeed = 0.01;
        GC.newBlackTime = 1.5;

        var scene       = new cc.Scene();
        var gameview    = new GameView();
        var bg          = new GameViewBackground();

        scene.addChild(bg);
        scene.addChild(gameview);

        cc.director.runScene(scene);
        bg.addscoreBg();
        bg.adddrawGuidtext();
        gameview.startGame();
    },

    homeFunc : function () {
        cc.log("GO_homeFunc");

        //当前分数置0
        GC.CUR_SCORE = 0;
        GC.CUR_USER  = "";
        GC.scaleSpeed = 0.01;
        GC.newBlackTime = 1.5;
        cc.director.runScene(new LoginScene());
    },

    shareFunc : function () {
        cc.log("GO_shareFunc");

        var arrow = new cc.Sprite(res.arrow_png);
        arrow.setPosition(Wsize.width/2, Wsize.height/2 + 46);
        this.addChild(arrow);
    },

    showScore : function (currScore) {
        cc.log("showScore = " + currScore);

        var superMan = cc.sys.localStorage.getItem("superMan");
        cc.log("superMan = " + superMan);

        var scoreBg = new cc.Sprite(res.overScoreBg);
        var size = scoreBg.getContentSize();
        scoreBg.attr({
            x: Wsize.width / 2,
            y: Wsize.height / 2 + 300
        });
        this.addChild(scoreBg);

        //No
        var str_no = " NO." + cc.sys.localStorage.getItem("totalNumber");
        var label_no = new cc.LabelTTF("", "Arial", 30);
        label_no.setPosition(cc.p(70, size.height - 40));
        label_no.setColor(cc.color(0, 0, 0));
        scoreBg.addChild(label_no, 5);
        label_no.setString(str_no);

        //得分
        var label = new cc.LabelTTF("", "Arial", 24);
        label.setPosition(cc.p(size.width / 2, size.height - 50));
        label.setColor(cc.color(0, 0, 0));
        scoreBg.addChild(label, 5);
        label.setString("得分");
        //得分内容
        var label_curr = new cc.LabelTTF("", "Arial", 50);
        label_curr.setPosition(cc.p(size.width / 2, size.height - 100));
        label_curr.setColor(cc.color(0, 0, 0));
        scoreBg.addChild(label_curr, 2);
        label_curr.setString(currScore);

        var bestScore = 0;
        var score = cc.sys.localStorage.getItem("bestScore");

        var str = "";
        if (score) {
            bestScore = score;
            str = "最佳 BY " + superMan;
        }
        else {
            bestScore = 0;
            str = "最佳";
        }

        //最佳
        var labelTwo = new cc.LabelTTF("", "Arial", 24);
        labelTwo.setPosition(cc.p(size.width / 2, size.height - 160));
        labelTwo.setColor(cc.color(0, 0, 0));
        scoreBg.addChild(labelTwo, 5);
        labelTwo.setString(str);
        //最佳内容
        var label_best = new cc.LabelTTF("", "Arial", 50);
        label_best.setPosition(cc.p(size.width / 2, size.height - 210));
        label_best.setColor(cc.color(0, 0, 0));
        scoreBg.addChild(label_best, 5);
        label_best.setString(bestScore);
    }
});




















