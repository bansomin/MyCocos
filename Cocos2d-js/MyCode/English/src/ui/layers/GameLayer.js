/**
 * Created by Jinling on 16/11/23.
 */

var GameLayer =cc.Layer.extend({


/*
    _curTpIdx: 0,   //算式数组模板当前的索引
    _minute: 0,     //分钟数
    _second: 0,     //秒数
    _modeCount: 12,     //一次从模板产生 题数
    _tpArrIndex: 0,     //_tpArr已经使用到的下标
    _rightNum: 0,       //当前正确题数
    _totalNum: 0,  //总的做题数

    */

    /***********************触摸*****************/
    _isTouch    :   false,  //触摸标识

    /***********************数组*****************/
    _tpArr              :   [],   //存放10个单词
    _tpDict             :   [],   //存放16个地鼠
    _myArray            :   [],   //打乱顺序之后的数组（地鼠随机出现）
    _wordArray          :   [],   //存放单词单个字母数组
    _hideArray          :   [],   //隐藏字母的数组
    _lackLetterArray    :   [],   //缺少单词数组

    /***********************关卡*****************/
    _levelSpr       :   null,   //关卡层
    _curlevel       :   1,      //当前关卡数
    _countTime      :   0,      //总时间   秒计

    /***********************单词面板***************/
    _cn             :   null,   //汉字
    _en             :   null,   //英
    _titleSpr       :   null,   //英文单词展示板
    _label_cn       :   null,   //中文解释部分

    _hammer             :   null,           //锤子
    _numberofHamster    :   0,      //地鼠数量计数器
    _numLetterFinish    :   0,      //已经增写的字母数目

    /***********************动态云***************/
    _coludOne       :   null,
    _coludTwo       :   null,
    _coludeThree    :   null,

    ctor: function () {

        this._super();

        Wsize = cc.director.getWinSize();
        this._isTouch = false;

        //倒计时界面
        var countdownlayer = new CountDownLayer();
        countdownlayer.setDelegate(this);   //设置代理
        this.addChild(countdownlayer);

        return true;
    },

    //实现代理
    init: function (sender) {

        this._tpArr = [];
        this._tpDict = [];
        this._myArray = [];
        this._wordArray = [];
        this._hideArray = [];
        this._lackLetterArray = [];

        //加载背景UI
        this.initUI();

        //相关数据准备
        this.prepareTemplates();

        cc.eventManager.addListener({
			event          : cc.EventListener.TOUCH_ONE_BY_ONE,
			swallowTouches : true,
			onTouchBegan   : this.onTouchBegan.bind(this),
			onTouchEnded   : this.onTouchEnded.bind(this)
		}, this);

    },

    onTouchBegan : function (touch, event) {
        //cc.log("onTouchBegan");
        return this._isTouch;
    },

    onTouchEnded : function (touch, event) {
        //cc.log("onTouchEnded");

        var point  = touch.getLocation();
        var target = event.getCurrentTarget();
        //cc.log("point : " + point.x + " && " + point.y);

        //锤子敲打动画
        if ((this._hammer != null)) {
            if (point.y <= Wsize.height*3/4) {

                //播放音效
                SoundManager.playHitSound();

                this._hammer.setPosition(point);
                this._hammer.changeTargetAnimation(GC.ANIMATIONTYPE.HAMMER);
            }
        }

        /***********************************单词部分***********************************/
        var pointTarget = target._titleSpr.convertToNodeSpace(point);
        //cc.log("PointTarget : " + pointTarget.x + " && " + pointTarget.y);
        var len = this._wordArray.length;
        if (len != 0) {
            for (var i = 0; i < len; i++) {
                var obj = target._wordArray[i];
                if (cc.rectContainsPoint(obj.rect, pointTarget)) {  //确定点击的单词
                    if (obj.isClick && obj.target.getLetter() != '') {
                        obj.target.letterAction(GC.ANIMATIONTYPE.HIDE);
                        //obj.target.setLetter('');
                        //对应的地鼠跳出动画
                        this.hamsterOutAniamtion(obj.tag);

						//播放音效
						SoundManager.playSelectSound();
                    }
                }
            }
        }
        /***********************************单词部分***********************************/


        /***********************************地鼠部分***********************************/
        var len = this._tpDict.length;
        //cc.log("Len = " + len);
        if (len != 0) {
            for (var i = 0; i < len; i++) {
                var obj = target._tpDict[i];
                if (cc.rectContainsPoint(obj.rect, point)) {
                    cc.log("TAG : " + obj.tag + " LETTER : " + obj.letter);
                    if (obj.isSelected) {   //当前地鼠可点
                        obj.isSelected = false;
                        //设置Hammer的位置
                        this._hammer.setPosition(obj.position.x + obj.rect.width/3,
                                                    obj.position.y + obj.rect.height/3);
                        obj.hamster.changeTargetAnimation(GC.ANIMATIONTYPE.IN);

                        var wordLen = target._wordArray.length;
                        var lacklen =  target._lackLetterArray.length;

                        if (wordLen != 0) {
                            for (var j = 0; j < wordLen; j++) {

                                var targetObj = target._wordArray[j];
                                if (targetObj.isClick && targetObj.target.getLetter()=='') {    //设置空缺字母的显示
                                    targetObj.target.setLetter(obj.hamster.getLetter());    //设置字母
                                    targetObj.tag = GC.LETTER_TAG + obj.tag;    //设置tag
                                    targetObj.target.letterAction("show");

                                    this._numLetterFinish++;
                                    break;
                                }
                            }

                            if (this._numLetterFinish == lacklen) {
                                //清除
                                this._numLetterFinish = 0;
                                //this.checkResult();//检查结果是否正确

                                //0.4秒后显示结果
                                var callback = cc.callFunc(this.checkResult, this);
                                var seq = cc.sequence(cc.delayTime(0.4), callback);
                                this.runAction(seq);

                                this._isTouch = false;      //关闭触摸
                            }
                        }

                    }
                }
            }
        }
        /***********************************地鼠部分***********************************/

    },

    /**
     * 界面UI
     */
    initUI:function() {

        //加载背景图片
        var bg = new cc.Sprite(res.png_bg_game);
        bg.setPosition(Wsize.width/2, Wsize.height/2);
        this.addChild(bg, -1);

        //关卡界面
        this._levelSpr = new LevelInforModel(this._countTime);
        this._levelSpr.setPosition(Wsize.width/2, Wsize.height - 70);
        this.addChild(this._levelSpr, 10);

        //英文题目背景
        this._titleSpr = new cc.Sprite("#datiban.png");
        this._titleSpr.setPosition(Wsize.width/2, Wsize.height - 290);
        this.addChild(this._titleSpr, 10);

        //ABCLogo
        var abcSpr = new cc.Sprite("#jisuanABC.png");
        //abcSpr.setPosition(this._titleSpr.getContentSize().width - 60, this._titleSpr.getContentSize().height/5 - 10);
        abcSpr.setPosition(70, this._titleSpr.getContentSize().height + 30);
        this._titleSpr.addChild(abcSpr);

        //英文中文分隔线
        var underline = new cc.Sprite("#fenjiexian.png");
        underline.setPosition(this._titleSpr.getContentSize().width/2,
                                this._titleSpr.getContentSize().height/2 + 15);
        this._titleSpr.addChild(underline);

        //汉方解释
        this._label_cn = new cc.LabelTTF("", "Arail", 40);
        //this._label_cn.setColor(cc.color(0, 0, 0));
        this._label_cn.setPosition(this._titleSpr.getContentSize().width/2,
                                        this._titleSpr.getContentSize().height/3 + 20);
        this._titleSpr.addChild(this._label_cn);

        //云的创建
        //this._coludOne = new cc.Sprite("#could03.png");
        //this._coludTwo = new cc.Sprite("#colue01.png");
        //this._coludeThree = new cc.Sprite("#colue01.png");
        //this._coludOne.setPosition(Wsize.width/2 + 90, Wsize.height - 10);
        //this.addChild(this._coludOne, 1);
    },

    /**
     * 准备英文单词集合
     */
    prepareTemplates: function () {

        var levelfile = "res/config/Levelconfig.json";

        //清空已有模板
        this._tpArr = [];   //算式模板数组,
        this._tpDict = [];  //算式字典,已经new出来的模板实例对象

        //读取json文件   //res/config下的json配置
        cc.loader.loadJson(levelfile, function (err, ret) {
            if (err) {
                cc.log("Failed to load " + levelfile);
                return;
            }
            var tproot = ret["Words"];
            this._countTime = tproot["counttime"];//读取到总的时间

            //取出单词数组
            var itemsArray = tproot["items"];
            var itemsLen = itemsArray.length;   //数组长度
            cc.log("单词库中总共" + itemsLen + " 个单词");

            var sign = false;
            if (itemsLen != 0) {
                for (var i = 0; i < itemsLen; i++) {

                    //获取的单词数组大小
                    if (this._tpArr.length >= 10) {
                        break;
                    }

                    //随机获取单词及其解释
                    var no = parseInt(itemsLen * Math.random());
                    var word = itemsArray[no];
                    var en = word["en"];
                    var cn = word["cn"];

                    //单词长度大于8的单词忽略
                    if (en.length > 8) {
                        cc.log("单词长度大于8 ：" + en);
                        continue;
                    }

                    //检查是否已经包含该单词
                    for (var i = 0; i < this._tpArr.length; i++) {
                        if (en == this._tpArr[i].en) {
                            cc.log("相同单词 ：" + en);
                            sign = true;
                            break;
                        }
                    }

                    if (sign) {
                        sign = false;
                        continue;
                    }

                    var wordObj = new Object();
                    wordObj.en  = en;
                    wordObj.cn  = cn;

                    this._tpArr.push(wordObj);
                    cc.log("单词 * " + wordObj.en + " * 准备完毕");
                }

                //添加
                this.prepareData();       //显示单词
            }
            else {
                cc.log("Getting Information Failure...");
            }

        }.bind(this));

    },

    /**
     * 字母、单词的显示
     */
    prepareData : function () {
        cc.log("prepareData");

        this.prepareWord();  //单词操作
        this.addHamstersFunc(); //添加地鼠
    },

    /**
     * 读取本关单词
     */
    prepareWord : function () {

        //取出单词
        var wordItem = this._tpArr[this._curlevel-1];
        this._en = wordItem.en;
        this._cn = wordItem.cn;
        var len = this._en.length;

        cc.log("****************本关单词******************");
        cc.log("单词 : " + this._en + " ---- 解释 ：" + this._cn);
        cc.log("**********************************");

        //显示汉语解释
        this._label_cn.setString(this._cn);

        //得到需要隐藏字母的数组
        this._hideArray = GC.randomNeedLetterArray(this._en);

        // 摆放单词
        var y = this._titleSpr.getContentSize().height/2 + 70;
        var tempArray = this._en;
        for (var i in tempArray) {
            var letter = new LetterLabelModel(tempArray[i]);
            var x = 0;
            if (len%2==0) {     //偶数
                x = (i - parseInt(len/2) + 1)*55 + 272;
            }
            else {              //奇数
                x = (i - parseInt(len/2))*55 + 272;
            }
            //cc.log("单词坐标 ：(" + x + ", " + y + ")");

            var nowposition = cc.p(Wsize.width+100, y);//单词入场动作
            var toposition = cc.p(x, y);
            letter.setPosition(nowposition);
            letter.runAction(cc.moveTo(0.5, toposition));

            this._titleSpr.addChild(letter);

            var rect = cc.rect(x-25, y-32, 50, 64);
            var obj = new Object();
            obj.tag    = GC.LETTER_TAG;
            obj.rect   = rect;
            obj.target = letter;
            obj.isClick = false;    //当前Label是否可点
            this._wordArray.push(obj);
        }

        this.hideLetterFunc();   //对单词进行加工
    },

    /**
     * 单词的加工处理（随机隐藏一定数目的字母）
     */
    hideLetterFunc : function () {
        //cc.log("hideLetterFunc");

        var len_word = this._wordArray.length;
        var len_hide = this._hideArray.length;

        for (var i = 0; i < len_word; i++) {
            for (var j = 0; j < len_hide; j++) {
                if (i == this._hideArray[j]) {      //得到需要隐藏字母的下标
                    var obj = this._wordArray[i];
                    obj.target.setLetter('');   //设置为空
                    //obj.target.setUnderlineShow(true);
                    obj.target._underline.setVisible(true); //显示下划线
                    obj.isClick = true; //该字母可点击

                    //存储到数组
                    this._lackLetterArray.push(obj);
                }
            }
        }

    },

    /**
     * 创建地鼠
     */
    addHamstersFunc : function () {
        //cc.log("addHamsterFunc");

        //得到地鼠的数组
        this._myArray = GC.randomMyArray();
        this.schedule(this.createHamstersFunc, 0.18); //开启定时器
    },

    /**
     * 创建地鼠
     * 使用定时器控制地鼠创建的速度
     */
    createHamstersFunc : function () {
        cc.log("CREAT");

        var ww = (Wsize.width - GC.DISBWTHAMSTER*2)/8;
        if (this._numberofHamster<16) {

            var no = this._myArray[this._numberofHamster];
            var i = parseInt(no/4);
            var j = no%4;

            var code = 97, letter = '';
            if (this._numberofHamster < this._wordArray.length) {//先将单词中的字母随机添加进去
                letter = this._en.substr(this._numberofHamster, 1);
            }
            else {
                code = 97 + parseInt(26 * Math.random());   //后作用随机的字母
                letter = String.fromCharCode(code);
            }
            //地鼠的位置
            var x = GC.DISBWTHAMSTER + (ww - 2)*(i*2 + 1) + 10;
            var y = GC.DISBWTHAMSTER + (ww - 6)*(j*2 + 1) + 60;
            var rect = cc.rect(x - GC.BOXWIDTH/2, y - GC.BOXHEIGHT/3, GC.BOXWIDTH, GC.BOXHEIGHT);

            var hamster = new HamsterModel(letter);
            hamster.setPosition(x, y);
            this.addChild(hamster, (10 - j));
            hamster.changeTargetAnimation(GC.ANIMATIONTYPE.OUT);

            var obj  = new Object();
            obj.hamster = hamster;
            obj.letter = letter;
            obj.rect = rect;
            obj.tag  = ("" + i +　j)*1;
            obj.isSelected = true;
            obj.position = cc.p(x, y);

            this._tpDict.push(obj);

            this._numberofHamster++;
        }
        else {
            this._numberofHamster=0;
            this.unschedule(this.createHamstersFunc);   //停止定时器
            this.createHammerFunc();    //加载锤子
        }
    },

    /**
     * 创建图片
     */
    createHammerFunc : function () {

        if (this._hammer!=null) {
            return;
        }
        //加载锤子
        this._hammer = new HammerModel();
        this._hammer.setPosition(parseInt((600 - 100) * Math.random() + 100), 50);
        this.addChild(this._hammer, 10);

        //开启计时器
        this._levelSpr.startTimer();
        //开启触摸
        this._isTouch = true;
    },

    /**
     * 取消单词后对应的地鼠跳出
     */
    hamsterOutAniamtion : function (tag) {

        var tag = tag-GC.LETTER_TAG;
        for (var i in this._tpDict) {
            var obj = this._tpDict[i];
            if (tag == obj.tag) {   //设置地鼠可点击
                obj.isSelected = true;
                this._numLetterFinish--;
                obj.hamster.changeTargetAnimation(GC.ANIMATIONTYPE.OUT);
            }
        }

    },

    /**
     * 检查最后是否正确
     */
    checkResult : function () {
        //cc.log("checkResult.");

        var wordStr = '';
        for (var i = 0; i < this._wordArray.length; i++) {
            wordStr += this._wordArray[i].target.getLetter();
        }

        if (this._en == wordStr) {  //正确

			//播放音效
			SoundManager.playRightSound();

            var seq = cc.sequence(cc.delayTime(0.6), cc.callFunc(this.nextLevel, this));
            this.runAction(seq);
        }
        else {  //错误

            //错误层
            var resultlayer = new ResultLayer();
            resultlayer.setDelegate(this);
            this.addChild(resultlayer, 20);
        }

    },

    /**
     * 正确--进入下一关
     */
    nextLevel : function () {
        this._hideArray = [];
        this._curlevel++;

        if (this._curlevel>10) {    //10关结束
            this._levelSpr.stopTimer(); //停止定时器
            this._countTime = this._levelSpr.getTimer();
            cc.log("已经完成所有关卡，共用时 ：" + this._levelSpr.getTimer());

            //3s后跳转到开始界面
            var callfunc = cc.callFunc(this.restartFunc, this);
            var delaytime = cc.delayTime(3);
            var seq = cc.sequence(delaytime, callfunc);
            this.runAction(seq);

            return;
        }
        //重新设置关卡数
        this._levelSpr.setLevel(this._curlevel);

        //重新创建单词
        for (var i = 0; i < this._wordArray.length; i++) {
            var toposition  = cc.p(-100, this._wordArray[i].target.getPositionY());
            //单词入场动作,动作结束后移除单词对象
            var seq = cc.sequence(cc.moveTo(0.5, toposition), cc.callFunc(this.removeSelfFromParent, this));
            this._wordArray[i].target.runAction(seq);
        }

        this._wordArray = [];       //清空数组
        this._lackLetterArray = [];

        //重新准备单词
        this.prepareWord();

        //地鼠的重新动画
        this.rePlayHamsterAnimation();
    },

    rePlayHamsterAnimation : function () {

        //得到地鼠的数组
        this._myArray = [];
        this._myArray = GC.randomMyArray();
        this.schedule(this.addHamsterAnimation, 0.01); //开启定时器
    },

    addHamsterAnimation : function () {
        if (this._numberofHamster<16 && this._tpDict.length>0) {
            var obj = this._tpDict[this._numberofHamster];
            obj.isSelected = true;
            //obj.hamster.changeTargetAnimation(GC.ANIMATIONTYPE.OUT);
            obj.hamster.changeHamsterTexture();

            var code = 97, letter = '';
            if (this._numberofHamster < this._en.length) {
                letter = this._en.substr(this._numberofHamster, 1); //先使用单词
                //cc.log("L : " + letter);
            }
            else {
                code = 97 + parseInt(26 * Math.random());   //后随机
                letter = String.fromCharCode(code);
            }
            obj.hamster.setLetter(letter);

            this._numberofHamster++;
        }
        else {
            this._numberofHamster=0;
            this._isTouch = true;//开启触摸

            this.unschedule(this.addHamsterAnimation);   //停止定时器
        }

    },

    /**
     * 结果层代理实现
     * 正确--进入下一关
     */
    rePlayFunc:function(sender){
        cc.log("GameLayer_playClicked.");

        //地鼠复原
        for (var i = 0; i < this._tpDict.length; i++) {
            var hamsterObj = this._tpDict[i];
            if (!hamsterObj.isSelected) {
                hamsterObj.isSelected = true;
                //hamsterObj.hamster.changeTargetAnimation(GC.ANIMATIONTYPE.OUT);
                hamsterObj.hamster.changeHamsterTexture();
            }
        }

        //字母隐藏
        for (var i = 0; i < this._wordArray.length; i++) {
            var wordObj = this._wordArray[i];
            if (wordObj.isClick) {
                wordObj.target.setLetter('');
            }
        }

        this._isTouch = true;//开启触摸
    },

    /**
     * 动作结束之后移除字母
     */
    removeSelfFromParent : function (sender) {
        sender.removeFromParent();
    },

    //10关结束跳转到开始界面
    restartFunc : function () {
        cc.director.runScene(new cc.TransitionFade(1, new StartScene()));
    }

});