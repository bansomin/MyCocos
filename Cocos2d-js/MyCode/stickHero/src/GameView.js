/**
 * Created by HAO on 2016/8/25.
 */

var Wsize = null;

var stickSize   = null;
var npcNormal   =null;

/**背景层**/
var Score       = 0;    //分数
var ScoreText   = null; //分数字体
var guideTextPic = null;//黑块

/**游戏层**/
var gameViewXoffset = 0;    //游戏背景层偏移量
var preBlackXoffset = 0;    //前一个黑块信息
var curBlackXoffset = 0;    //生成黑块信息
var betweenXoffset  = 0;    //两个黑块之间的距离
var upBlackObject = null;   //增长黑块对象


//GameViewLayer
var GameView = cc.Layer.extend({

    _this   :   null,
    _start  :   false,

    ctor : function () {
        this._super();

        _this = this;
        _this._start = false;

        var stickBlack = new cc.Sprite(res.StickBlack_png);
        stickSize = stickBlack.getContentSize();
        stickBlack.attr({
            x   :   Wsize.width/2,
            y   :   stickSize.height/2- 50
        });
        stickBlack.setScale(180/stickSize.width, 387/stickSize.height);
        this.addChild(stickBlack);

        //初始动作
        npcController.initNPC(this);
        npcController.yao();

        //测试
        //npcController.walk(0.1);
        //npcController.shake();
        //npcController.kick();

        cc.eventManager.addListener({
            event   :   cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            onTouchBegan : this.onTouchBegan,
            onTouchEnded : this.onTouchEnded
        }, this);

      return true;
    },

    startGame : function () {
        cc.log("GameView_startGame.");

        Score = 0;
        ScoreText.setString(Score);

        var _width = 180;
        gameViewXoffset = -_width/2 + Wsize.width/2;
        preBlackXoffset = _width;
        this.runAction(cc.sequence(cc.moveBy(GC.screenTime, cc.p(-gameViewXoffset, 100))));
        this.npc_Run(0.1);

        /*
        * 注 ： 英雄加到了gameView层上
        */
        npcNormal.runAction(
            cc.sequence(
                cc.moveBy(0.2, cc.p(_width/2 - 28, 0)),
                cc.callFunc(this.npc_Yao, this),
                cc.callFunc(this.addBlock, this)
            )
        );

        //显示提示图片
        if (guideTextPic != null){
            guideTextPic.setVisible(true);
        }
    },

    //移动
    npc_Run : function (flag) {
        npcController.walk(flag);
    },

    //踢
    npc_Kick : function () {
        npcController.kick();
    },

    //抖
    npc_Shake : function () {
        npcController.shake();
    },

    //摇
    npc_Yao : function () {
        npcController.yao();
    },


    addBlock : function () {
        cc.log("GView_addBlock");

        upBlackObject = new cc.Sprite(res.StickBlack_png);
        upBlackObject.setAnchorPoint(cc.p(0.5, 0));
        upBlackObject.attr({
            x   :   gameViewXoffset + preBlackXoffset - 2.5,
            y   :   stickSize.height
        });
        upBlackObject.setScaleY(0);
        this.addChild(upBlackObject);

        /*
         * 黑条变长的方法
         *随机生成宽度加载到屏幕的右侧
         * 动作结束可以触发手指按下动作
         */

        var flag = cc.random0To1() * 120 + 10;
        var newstickBlack = new cc.Sprite(res.StickBlack_png);
        var newSize = newstickBlack.getContentSize();
        newstickBlack.setScale(flag/stickSize.width, 387/stickSize.height);
        newstickBlack.attr({
            x   :   gameViewXoffset + Wsize.width + flag/2,
            y   :   newSize.height/2 - 50
        })
        this.addChild(newstickBlack);

        var offset = Wsize.width - preBlackXoffset;
        var flag1  = (cc.random0To1() + 0.6)/2;

        curBlackXoffset = flag;
        betweenXoffset = flag1 * offset;

        newstickBlack.runAction(
            cc.sequence(
                cc.moveBy(GC.newBlackTime, cc.p(-betweenXoffset, 0)),
                cc.callFunc(this.setFlagFunc, this)
            )
        );
    },

    setFlagFunc : function () {
        _this._start = true;
    },

    onTouchBegan : function (touch, event) {
        cc.log("GmView_onTouchBegan");

        //开始游戏时隐藏提示图片
        if (guideTextPic != null){
            guideTextPic.setVisible(false);
        }

        if (_this._start){
            _this.startSchedule();
            return true;
        }
        return false;
    },

    onTouchEnded : function (touch, event) {
        cc.log("GmView_onTouchEnded");

        _this.stopSchedule();
    },

    startSchedule : function () {
        this.schedule(this.upBlackFunc, 0.02);
        this.npc_Shake();
    },

    upBlackFunc : function (dt) {
        cc.log("upBlackFunc");
        var scaleY = upBlackObject.getScaleY() + GC.scaleSpeed;
        upBlackObject.setScaleY(scaleY);
    },

    stopSchedule : function () {
        this.unschedule(this.upBlackFunc);
        this.npc_Kick();

        //关闭触摸
        _this._start = false;

        upBlackObject.runAction(
            cc.sequence(
                cc.delayTime(0.5),
                cc.rotateBy(0.1, 90),
                cc.callFunc(this.rotateEnd, this)
            )
        );
    },

    rotateEnd : function () {
        cc.log("rotateEnd.");

        var size = upBlackObject.getContentSize();
        var finalHeight = upBlackObject.getScaleY() * size.height;

        //判断是否可以通过
        var offset = (betweenXoffset + preBlackXoffset);
        var result = Wsize.width - offset;

        if (result+5 <= finalHeight && (result+curBlackXoffset >= finalHeight)){
            cc.log("成功！");
            this.gameNext(result + curBlackXoffset);
        }
        else {
            cc.log("失败！");
            if (result+curBlackXoffset < finalHeight){
                this.gameOver(result + curBlackXoffset + 50);
            }
            else {
                this.gameOver(finalHeight + 30);
            }
        }
    },

    gameNext : function (offset) {

        var flag = offset/500;
        this.npc_Run(flag/30);

        npcNormal.runAction(
            cc.sequence(
                cc.moveBy(flag, cc.p(offset, 0)),
                cc.callFunc(this.nextBlack, this)
            )
        );
    },

    nextBlack : function () {
        cc.log("nextBlack");

        Score ++;
        GC.CUR_SCORE = Score;
        ScoreText.setString(Score);

        //Score = 100000;

        //调整速度
        GC.scaleSpeed = 0.01 + Score * 0.0002;
        GC.newBlackTime = 1.5 - Score*0.1;
        //限制scaleSpeed速度
        if (GC.scaleSpeed>=0.06){
            GC.scaleSpeed = 0.06;
        }
        //限制newBlackTime速度
        if (GC.newBlackTime<0.15){
            GC.newBlackTime = 0.15;
        }

        //刷新最高名次
        if (Score >= cc.sys.localStorage.getItem("bestScore")){ //调处
            cc.sys.localStorage.setItem("bestScore", Score);
            cc.sys.localStorage.setItem("superMan", GC.CUR_USER);
        }

        this.npc_Yao();

        //准备屏幕的移动
        preBlackXoffset = curBlackXoffset + 40;

        var result = Wsize.width - betweenXoffset - 40;
        gameViewXoffset += result;

        this.runAction(
            cc.sequence(
                cc.moveBy(0.3, cc.p(-result, 0)),
                cc.callFunc(this.addBlock, this)
            )
        );
    },

    gameOver : function (offset) {

        var flag = offset/500;
        this.npc_Run(flag/30);

        npcNormal.runAction(
            cc.sequence(
                cc.moveBy(flag, cc.p(offset, 0)),
                cc.callFunc(this.gameFaile, this)
            )
        );
    },

    gameFaile : function () {
        cc.log("gameFaile");

        this.npc_Yao();
        npcNormal.runAction(
            cc.sequence(
                cc.moveTo(0.3, cc.p(npcNormal.getPositionX(), -200)),
                cc.callFunc(this.addGameOverFunc, this)
            )
        );

        upBlackObject.runAction(
            cc.sequence(
                cc.rotateBy(0.1, 90)
            )
        );
    },

    addGameOverFunc : function () {
        cc.log("addGameOverFunc");

        var gameoverlayer = new GameOver();
        gameoverlayer.attr({
            x   :   gameViewXoffset,
            y   :   -100
        });
        this.addChild(gameoverlayer, 2000);
    }
});

/**********
* 英雄动作
* ********/
var npcController = {

    sfCache :   null,
    initNPC : function (layer) {

        sfCache = cc.spriteFrameCache;
        sfCache.addSpriteFrames(res.ShakePlist, res.ShakePng);
        sfCache.addSpriteFrames(res.KickPlist, res.KickPng);
        sfCache.addSpriteFrames(res.WalkPlist, res.WalkPng);
        sfCache.addSpriteFrames(res.YaoPlist, res.YaoPng);

        npcNormal = new cc.Sprite('#d0001.png');
        var npcSize = npcNormal.getContentSize();

        npcNormal.setScale(1, 1);
        npcNormal.attr({
            x   :   Wsize.width/2,
            y   :   stickSize.height + npcSize.height/2
        });

        layer.addChild(npcNormal);
    },

    walk : function (flag) {

        npcNormal.stopAllActions();

        var frame;
        var str = "";
        var animFrames = [];
        for (var i = 1; i<10; i++){
            str = "z000" + i + ".png";
            frame = sfCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var animation = new cc.Animation(animFrames, flag);
        npcNormal.runAction(cc.animate(animation).repeatForever());
    },

    shake : function () {

        npcNormal.stopAllActions();

        var frame;
        var str = "";
        var animFrames = [];
        for (var i = 1; i<10; i++){
            str = "dq000" + i + ".png";
            frame = sfCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var animation = new cc.Animation(animFrames, 0.1);
        npcNormal.runAction(cc.animate(animation).repeatForever());
    },

    kick : function () {

        npcNormal.stopAllActions();

        var frame;
        var str = "";
        var animFrames = [];
        for (var i = 1; i<10; i++){
            str = "t000" + i + ".png";
            frame = sfCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var animation = new cc.Animation(animFrames, 0.05);
        npcNormal.runAction(cc.animate(animation));
    },

    yao : function () {

        npcNormal.stopAllActions();

        var frame;
        var str = "";
        var animFrames = [];
        for (var i = 1; i<10; i++){
            str = "d00" + (i < 10 ? ("0" + i) : i) + ".png";
            frame = sfCache.getSpriteFrame(str);
            animFrames.push(frame);
        }

        var animation = new cc.Animation(animFrames, 0.1);
        npcNormal.runAction(cc.animate(animation).repeatForever());
    }
};

/********
* 背景层
********/
var GameViewBackground = cc.Layer.extend({

    ctor : function () {
        this._super();

        Wsize = cc.director.getWinSize();

        var type = parseInt(4 * Math.random());
        var resName = null;
        switch (type){
            case 0 :
                resName = res.StartBackground_png0;
                break;
            case 1 :
                resName = res.StartBackground_png1;
                break;
            case 2 :
                resName = res.StartBackground_png2;
                break;
            default :
                resName = res.StartBackground_png3;
                break;
        }

        var bg = new cc.Sprite(resName);
        bg.attr({
            x   :   Wsize.width/2,
            y   :   Wsize.height/2,
            scale       : 1,
            rotation    : 0
        });
        this.addChild(bg, -1);

        ScoreText = new cc.LabelTTF("", "宋体", 46);
        ScoreText.setPosition(cc.p(Wsize.width/2, Wsize.height/2 + 300));
        ScoreText.setColor(cc.color(255,255, 255));
        this.addChild(ScoreText, 10);

        return true;
    },

    addscoreBg : function () {

        var bg = new cc.Sprite(res.ScoreBg);
        bg.x = Wsize.width/2;
        bg.y = Wsize.height/2 + 300;
        this.addChild(bg, 5);
    },

    adddrawGuidtext : function () {

        guideTextPic = new cc.Sprite(res.guideText);
        guideTextPic.attr({
            x   :   Wsize.width/2,
            y   :   Wsize.height/2 + 220
        });
        this.addChild(guideTextPic, 5);
        guideTextPic.setVisible(false);
    }
});







