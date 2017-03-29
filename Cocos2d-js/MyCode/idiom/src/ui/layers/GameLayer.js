/**
 * Created by HAO on 2016/12/8.
 * Brief   : 游戏界面
 * Version :
 */

var GameLayer =cc.Layer.extend({

	_allIdiomsArray		:	[],	//存放所有成语的数组(10个成语)
	_wordsArray			:	[],	//存放16个字
	_answerWordArray	:	[], //存放答案成语数组
	_reshuffleArray		:	[], //16个候选字打乱顺序后

	_finishedWord		:	0,	//已经添写好的字数
	_curlevel       	:   0,      //当前关卡
	_answerBoard		:	null,	//答题板

	_idiom				:	"",		//本关的成语
	_idiomExp			:	"",		//本关成语的解释
	_idiomFrom			:	"",		//本关成语出处
	_idiomFromLabel		:	null,	//

	_answerWordArrayCount	:	0,
	_wordArrayCount			:	0,
	_showWordArrayCount		:	0,
	_countTime				:	0,

	_candidateString		:	"",	//候选成语组成的字符串

	_touchSpr				:	null,

	_detaillayer			:	null,

	_isTouch			:	false,	//触摸控制

	ctor : function () {
		this._super();

		Wsize = cc.director.getVisibleSize();

		//倒计时界面
		var countdownlayer = new CountDownLayer();
		countdownlayer.setDelegate(this);   //设置代理
		this.addChild(countdownlayer);

		cc.eventManager.addListener({
			event          : cc.EventListener.TOUCH_ONE_BY_ONE,
			swallowTouches : true,
			onTouchBegan   : this.onTouchBegan.bind(this),
			onTouchEnded   : this.onTouchEnded.bind(this)
		}, this);

		return true;
	},
	
	init : function (sender) {

		this._isTouch = false;

		this._curlevel = 0;
		//this._countTime = 3589;
		this._countTime = 0;
		this._finishedWord = 0;

		//清空相关数组
		this._wordsArray		=	[];	//存放16个汉字选项
		this._allIdiomsArray	=	[];	//存放全部成语
		this._answerWordArray	=	[]; //存放答案成语
		this._reshuffleArray	=	[]; //16个候选字打乱顺序后

		//游戏开始操作
		//加载基础UI
		this.addUI();
		//准备数据
		this.prepareTemplates();
	},

	onTouchBegan : function (touch, event) {
		//cc.log("onTouchBegan");
		return this._isTouch;
	},

	onTouchEnded : function (touch, event) {
		//cc.log("onTouchEnded");

		var point = touch.getLocation();
		var target = event.getCurrentTarget();

		//播放音效
		SoundManager.playHitSound(1);

		//触摸点的动画
		this.touchAnimation(point);

		/***************************************答案汉字部分***************************************/
		var pointTarget = target._answerBoard.convertToNodeSpace(point);
		var answerWordLen = target._answerWordArray.length;
		if (answerWordLen>0) {
			for (var i = 0; i < answerWordLen; i++) {
				var answerWordObj = target._answerWordArray[i];
				if (cc.rectContainsPoint(answerWordObj.rect, pointTarget)) {
					if (answerWordObj.obj.getWord() != "") {
						cc.log("I'm in : " + answerWordObj.tag);
						answerWordObj.obj.changeAction(GC.ACTIONTYPE.TOTOP);

						this.resetCandidateWordFunc(answerWordObj.tag);

						//播放音效
						SoundManager.playSelectSound(1);
					}
				}
			}
		}

		/***************************************答案汉字部分***************************************/

		/***************************************汉字候选部分***************************************/
		var len = target._wordsArray.length;
		//cc.log("wordArray : " + len);
		if (len>0) {

			for (var i = 0; i < len; i++) {
				var wordObj = target._wordsArray[i];
				if (cc.rectContainsPoint(wordObj.rect, point)) {
					//cc.log("Word : " + wordObj.word + " TAG : " + wordObj.tag);
					if (!wordObj.isSelected) {
						wordObj.isSelected = true;
						wordObj.obj.changeWordBG(wordObj.isSelected);
						wordObj.obj.changeAction(false);

						for (var j = 0; j < answerWordLen; j++) {
							var answerWordObj = target._answerWordArray[j];
							if (answerWordObj.obj.getWord() == "") {
								answerWordObj.obj.setWord(wordObj.obj.getWord());
								answerWordObj.tag = GC.TAG_ANSWERWORD + wordObj.tag;
								//cc.log("TTTag : " + answerWordObj.tag);

								//答题上汉字的动作
								answerWordObj.obj.changeAction(GC.ACTIONTYPE.TOMID);

								//已经添写好的字数加1
								target._finishedWord++;
								break;
							}
						}

						//实时检测已经填写的汉字个数
						//cc.log("已经填写 ：" + this._finishedWord);
						if (target._finishedWord==answerWordLen) {

							target._isTouch = false;	//禁用触摸
							target._finishedWord = 0;

							//0.4秒后显示结果
							var callback = cc.callFunc(target.checkResultFunc, target);
							var seq = cc.sequence(cc.delayTime(0.4), callback);
							target.runAction(seq);
						}
					}
				}
			}

		}
		/***************************************汉字候选部分***************************************/

	},

	/**
	 * 界面UI
	 */
	addUI : function () {

		//背景
		var bg = new cc.Sprite(res.png_gameBg);
		bg.setPosition(cc.p(Wsize.width/2, Wsize.height/2));
		bg.setScaleX(RCCommon.scaleXRatio);
		this.addChild(bg, -1);

		//答题板
		this._answerBoard = new cc.Sprite(res.png_answer);
		this._answerBoard.setPosition(cc.p(Wsize.width/2, Wsize.height - this._answerBoard.getContentSize().height/2 - 50));
		this.addChild(this._answerBoard);

		//关卡界面
		this._levelSpr = new LevelInforModel(this._countTime);
		this._levelSpr.setPosition(Wsize.width/2, Wsize.height - this._levelSpr.getContentSize().height/3);
		this.addChild(this._levelSpr);

		//创建4个答案汉字
		//创建16个汉字选项
		this.createWordCell();

		//解释层、出处层
		this._detaillayer = new DetailLayer();
		this._detaillayer.setPosition(this._answerBoard.getContentSize().width/2 - 10, this._detaillayer.getHeightFunc()/2 + 10);
		this._answerBoard.addChild(this._detaillayer);

		this._touchSpr = new cc.Sprite();
		this._touchSpr.setScale(0.5);
		this.addChild(this._touchSpr, 100);
	},

	/**
	 *  创建4个答案汉字并存放到_answerWordArray中
	 * 	创建16个汉字选项并存放到_wordArray中
	 */
	createWordCell : function () {

		//创建4个汉字CELL
		var y = this._answerBoard.getContentSize().height/2 + 20;
		for (var i = 0; i < GC.IDIOM_CANDIDATENUMBERS; i++) {

			var x = this._answerBoard.getContentSize().width/2 + (i-1.5)*GC.DIS_BETANSWERWORD;

			var answerCell = new CCUModel();
			answerCell.setScale(1);
			answerCell.setPosition(cc.p(x, y));
			this._answerBoard.addChild(answerCell);

			var answerWordObj = new Object();
			answerWordObj.obj = answerCell;
			answerWordObj.rect = cc.rect(x-70, y-70, 140, 140);
			answerWordObj.tag  = GC.TAG_ANSWERWORD;

			this._answerWordArray.push(answerWordObj);
		}
		cc.log("AnswerArray : " + this._answerWordArray.length);

		//创建16个汉字CELL
		var len = GC.IDIOM_CANDIDATENUMBERS*4;
		for (var i = 0; i < 4; i++) {
			for (var j = 0; j < 4; j++) {
				var x = Wsize.width/2 + (i*2 - 3)*65;
				var y = (j*2 + 1)*60 + GC.DIS_BETEDGE;

				var wordCell = new WordCellModel();
				wordCell.setPosition(cc.p(x, y));
				this.addChild(wordCell);

				var W = wordCell.getBoxWidth();
				//cc.log("W : " + W);

				var wordObj = new Object();
				wordObj.obj = wordCell;
				wordObj.rect = cc.rect(x-W/2, y-W/2, W, W);
				wordObj.tag  = ("" + i + j)*1;
				wordObj.isSelected = false;
				this._wordsArray.push(wordObj);
			}
			cc.log("WordArray : " + this._wordsArray.length);
		}

	},

	/**
	 * 准备数据然后开始关卡
	 */
	prepareTemplates : function () {

		//读取json中所有的成语并存放到
		cc.loader.loadJson(res.json_idiom_01, function (err, ret) {
			if (err) {
				cc.log("Failed to load " + res.json_idiom_01);
				return;
			}

			var rootIdiomAry = ret["idioms"];
			var rootIdiomLen = rootIdiomAry.length;
			cc.log("rootIdiomLen : " + rootIdiomLen);

			// for (var i in rootIdiomAry) {
			// 	cc.log("rootIdiomAry[" + i + "] : " + rootIdiomAry[i]["idiom"]);
			// }

			var reshuffleArray = GC.reshuffleArray(rootIdiomLen);
			if (!reshuffleArray) {//检测打乱顺序之后的数组的有效性
				cc.log("ArrayError!");
				return;
			}

			for (var i = 0; i < GC.LVL_TOTALNUMBERS; i++) {
				var no = reshuffleArray[i];
				cc.log("no : " + no);
				var idiom = rootIdiomAry[no]["idiom"];
				var exp = rootIdiomAry[no]["exp"];
				var from = rootIdiomAry[no]["from"];
				cc.log("idiom : " + idiom);
				// cc.log("exp : " + exp);
				// cc.log("from : " + from);

				var idiomObj = new Object();
				idiomObj.idiom = idiom;
				idiomObj.exp = exp;
				idiomObj.from = from;

				//随机选择出的指定数目的成语
				this._allIdiomsArray.push(idiomObj);	//存放10个成语
			}
			cc.log(this._allIdiomsArray.length);

			//进入选择关卡函数
			this.changeLevel();

		}.bind(this));

	},

	/**
	 * 选择关卡（获取本关成语并显示本关16个候选汉字）
	 */
	changeLevel : function (sender) {
		cc.log("changeLevel");
		cc.log("Curlevel : " + this._curlevel);

		this._curlevel++;
		if (this._curlevel > 10) {

			this._levelSpr.stopTimer(); //停止定时器
			this._countTime = this._levelSpr.getTimer();
			cc.log("已经完成所有关卡，共用时 ：" + this._levelSpr.getTimer());

			//0.5后返回开始界面
			cc.director.runScene(new cc.TransitionFade(0.5, new StartScene()));

			return;
		}

		//重新设置关卡数
		this._levelSpr.setLevel(this._curlevel);

		//本关成语对象
		var idiomObj = this._allIdiomsArray[this._curlevel-1];	//取出相应关卡的成语对象

		var idiom = idiomObj.idiom;	//成语
		var exp = idiomObj.exp;		//解释
		var from = idiomObj.from;	//出处
		this._idiom = idiom;
		this._idiomExp = exp;
		this._idiomFrom = from;
		cc.log("***************************************************");
		cc.log("第 " + this._curlevel + " 关");
		cc.log("idiom : " + idiom);
		cc.log("exp : " + exp);
		cc.log("from : " + from);
		cc.log("***************************************************");

		//设置本关解释文字
		this._detaillayer.setExp(exp);

		//16个汉字处理
		var tempIdiomStr = "";
		var fourArray = GC.reshuffleArray(this._allIdiomsArray.length);//打乱所有成语的顺序（从所有成语数组中随机取出四个成语）
		for (var i = 0; i < GC.IDIOM_CANDIDATENUMBERS; i++) {//取出前几个
			var no = fourArray[i];
			cc.log("no : " + no);
			var selectedIdiom = this._allIdiomsArray[no]["idiom"];
			cc.log("selectedIdiom : " + selectedIdiom);

			if (i == 0) {
				tempIdiomStr += idiom;	//先拼接第一个成语
			}
			else {
				tempIdiomStr += selectedIdiom;	//后拼接其他三个成语
			}
		}

		cc.log("tempIdiomStr : " + tempIdiomStr);
		cc.log("tempIdiomLen : " + tempIdiomStr.length);
		this._candidateString = tempIdiomStr;

		this._reshuffleArray = [];
		this._reshuffleArray = GC.reshuffleArray(tempIdiomStr.length);	//打乱16字的顺序

		this.showCandidateWordsByOrder();
	},

	/**
	 * 候选汉字的显示
	 */
	showCandidateWordsByOrder : function () {

		this.schedule(this.showCandidateWords, 0.05);
	},

	showCandidateWords : function () {

		if (this._showWordArrayCount < 16) {
			var word = this._candidateString.charAt(this._reshuffleArray[this._showWordArrayCount]);
			var wordObj = this._wordsArray[this._showWordArrayCount];
			wordObj.obj.setWord(word);

			this._showWordArrayCount++;
		}
		else {
			this._showWordArrayCount = 0;
			this.unschedule(this.showCandidateWords);

			//开启计时器
			this._levelSpr.startTimer();
			//开启触摸
			this._isTouch = true;

			//显示成语解释
			this._detaillayer.changeAction(true);
		}
	},

	/**
	 * 候选汉字的恢复
	 */
	resetCandidateWordFunc : function (tag) {

		var tag = tag - GC.TAG_ANSWERWORD;
		//cc.log("resetCandidateWordFunc_tag : " + tag);

		for (var i in this._wordsArray) {
			var wordObj = this._wordsArray[i];
			if (tag == wordObj.tag) {
				wordObj.isSelected = false;

				this._finishedWord--;
				wordObj.obj.changeWordBG(wordObj.isSelected);
				wordObj.obj.changeAction(false);
			}
		}

	},

	/**
	 * 候选汉字的恢复
	 */
	checkResultFunc : function () {
		cc.log("checkResultFunc");

		var wordSpr = "";
		for (var i = 0; i < this._answerWordArray.length; i++) {
			wordSpr += this._answerWordArray[i].obj.getWord();
		}
		cc.log("填写的成语 : " + wordSpr);

		if (this._idiom == wordSpr) {
			cc.log("回答正确");

			//播放音效
			SoundManager.playRightSound(1);

			this.rightTipFunc();
			//this.resetAllData();
		}
		else {
			cc.log("回答错误");

			//错误层
			var resultlayer = new ResultLayer();
			resultlayer.setDelegate(this);
			this.addChild(resultlayer, 20);
		}
	},

	/**
	 * 回答正确显示“nice/right”
	 */
	rightTipFunc : function () {

		var niceSpr = null;
		var rand = parseInt(2 * Math.random());
		if (rand==0) {
			niceSpr = new cc.Sprite("#zi_tz_bangjile.png");
		}
		else {
			niceSpr = new cc.Sprite("#zi_tz_zhengque.png");
		}
		var x = this._answerBoard.getPositionX() + parseInt(200*Math.random() - 100);
		var y = this._answerBoard.getPositionY() + parseInt(100*Math.random() - 300);
		niceSpr.setPosition(cc.p(x, y));
		this.addChild(niceSpr, 15);
		var blink = cc.blink(0.7, 3);
		var callback = cc.callFunc(this.showNextLevelLayer, this);
		var seq = cc.sequence(blink, cc.fadeOut(0.4), callback);
		niceSpr.runAction(seq);
	},

	showNextLevelLayer : function () {

		if (this._idiomFrom!=null) {	//有出处，显示出处层
			var nextlayer = new NextLevelLayer();
			nextlayer.setDelegate(this);
			nextlayer.setFrom(this._idiomFrom);
			this.addChild(nextlayer);
		}
		else {
			//无出处，直接进入下一关
			this.resetAllData();
		}

	},

	/**
	 * 实现代理
	 */
	nextLevelFunc : function (sender) {
		cc.log("nextLevelFunc");

		//清除相关数据
		this.resetAllData();
	},

	/**
	 * 回答错误重新填写
	 */
	 rePlayFunc : function () {
		//Erase
		this.eraseAnswerWordArray(0.15);

		for (var i in this._wordsArray) {
			var wordObj = this._wordsArray[i];
			if (wordObj.isSelected) {
				wordObj.isSelected = false;
				wordObj.obj.changeWordBG(false);
			}
		}
		this._isTouch = true;
	},

	/**
	 * 清除上关数据信息
	 */
	resetAllData : function () {
		cc.log("resetAllData");

		//隐藏解释
		this._detaillayer.changeAction(false);

		this.eraseAnswerWordArray(0.2);
		this.eraseWordArray(0.05);
	},

	eraseAnswerWordArray : function (time) {
		this.schedule(this.resetAnswerWordArrayFunc, time);
	},

	eraseWordArray : function (time) {
		this.schedule(this.resetWordArrayFunc, time);
	},

	resetAnswerWordArrayFunc : function () {

		if (this._answerWordArrayCount < 4) {
			//播放音效
			SoundManager.playSelectSound(1);

			var answerWordObj = this._answerWordArray[this._answerWordArrayCount];
			answerWordObj.obj.changeAction(GC.ACTIONTYPE.TOTOP);
			this._answerWordArrayCount++;
		}
		else {
			this._answerWordArrayCount = 0;
			this.unschedule(this.resetAnswerWordArrayFunc);
		}
	},

	resetWordArrayFunc : function () {

		if (this._wordArrayCount < 16) {
			var wordObj = this._wordsArray[this._wordArrayCount];
			wordObj.obj.setWord("");	//设置为空串
			wordObj.obj.changeAction(false);	//动作
			wordObj.isSelected = false;
			wordObj.obj.changeWordBG(false);			//改变字体颜色

			this._wordArrayCount++;
		}
		else {
			this._wordArrayCount = 0;
			this.unschedule(this.resetWordArrayFunc);

			//进入下一关
			this.changeLevel();
		}
	},

	/**
	 * 触摸点的动画
	 */
	touchAnimation : function (position) {
		//cc.log("touchAnimation");

		if (this._touchSpr) {
			this._touchSpr.setVisible(true);
			this._touchSpr.setPosition(position);

			var anima = null;
			this._touchSpr.stopAllActions();
			anima = cc.animationCache.getAnimation(GC.ANIMATIONTYPE.CLICK);
			if (anima==null) {
				anima = GC.prepareAnimation(GC.ANIMATIONTYPE.CLICK);
				cc.animationCache.addAnimation(anima, GC.ANIMATIONTYPE.CLICK);
			}
			var callback1 = cc.callFunc(function () {
				this._touchSpr.setVisible(false);
			}, this);
			this._touchSpr.runAction(cc.sequence(anima, callback1));
		}
	}


});