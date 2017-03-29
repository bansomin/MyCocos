/**
 * Created by HAO on 2016/11/25.
 * Brief   :	地鼠
 * Version :
 */

var HamsterModel = cc.Sprite.extend({

	_hamster		:	null,		//地鼠
	_holeFront		:	null,		//洞的前部分
	_holeBehind		:	null,		//洞的后部分

	_letter			:	"a",
	_letterLabel	:	null,
	_type			:	"out",

	ctor : function (letter) {
		this._super();

		this._letter = letter;

		//地鼠洞后
		this._holeBehind = new cc.Sprite("#keng_behind.png");
		this.addChild(this._holeBehind, -1);

		//地鼠
		this._hamster = new cc.Sprite("#dishu04.png");
		//this._hamster.setScale(0.8);
		this._hamster.setPositionY(45);
		this.addChild(this._hamster);

		//地鼠洞前
		this._holeFront = new cc.Sprite("#keng_front.png");
		this.addChild(this._holeFront);

		this._letterLabel = new cc.LabelBMFont(this._letter, res.font_fnt_p);
		this._letterLabel.setPositionY(30);
		this._letterLabel.setScale(1.5);
		this._letterLabel.setVisible(false);
		this.addChild(this._letterLabel);

		//地鼠出洞动画
		//this.changeTargetAnimation(GC.ANIMATIONTYPE.IN);

		return true;
	},

	setLetter : function (letter) {
		this._letter = letter;
		this._letterLabel.setString(this._letter);
	},

	getLetter : function () {
		return this._letter;
	},

	//执行动画
	changeTargetAnimation : function (type) {
		//cc.log("type : " + type);

		this._type = type;

		var animationName = null, anima = null, actionOut = null, actionIn = null;

		switch (type){
			case "out" :
				this._type = GC.ANIMATIONTYPE.OUT;
				animationName = "animationOut";
				break;
			case "in" :
				this._type = GC.ANIMATIONTYPE.IN;
				animationName = "animationIn";
				break;
			case "hammer" :
				animationName = "animationHammer";
				break;
		}

		//停止所有动作
		this._hamster.stopAllActions();

		anima = cc.animationCache.getAnimation(animationName);
		if (anima==null) {
			anima = GC.prepareAnimation(type);
			cc.animationCache.addAnimation(anima, animationName);
		}

		var callback = cc.callFunc(this.callbackFunc, this);
		var seq = cc.sequence(anima, callback);

		this._hamster.runAction(seq);
	},

	callbackFunc : function () {
		//cc.log("Hamster_callbackFunc");

		this._letterLabel.setVisible(true);

		var scaleToHide = null, moveTo = null, reverse = null, seq_move = null;
		if (this._type == GC.ANIMATIONTYPE.IN) {	//进洞动作
			//cc.log("进洞");
			scaleToHide = cc.scaleTo(0.1, 0, 1.2);
			moveTo = cc.moveTo(0.08, 0, -75);
			reverse = cc.moveTo(0.08, 0, 35);
			seq_move = cc.sequence(moveTo, reverse);
		}
		else if (this._type == GC.ANIMATIONTYPE.OUT) {	//出洞动作
			//cc.log("出洞");
			scaleToHide = cc.scaleTo(0.1, 0, 1.2);
			moveTo = cc.moveTo(0.08, 0, 100);
			reverse = cc.moveTo(0.08, 0, 35);
			seq_move = cc.sequence(moveTo, reverse);
		}

		var callbackNor = cc.callFunc(this.callbackNormalFunc, this);
		var seq = cc.sequence(seq_move, scaleToHide, callbackNor);
		this._letterLabel.runAction(seq);

	},

	callbackNormalFunc : function () {
		//cc.log("callbackNormalFunc");

		if (this._type == GC.ANIMATIONTYPE.IN) {
			this._letterLabel.setFntFile(res.font_fnt);	//黄色字体
		}
		if (this._type == GC.ANIMATIONTYPE.OUT) {
			this._letterLabel.setFntFile(res.font_fnt_p);
		}

		var scaleToShow = cc.scaleTo(0.05, 1.5, 1.5);
		this._letterLabel.runAction(scaleToShow);
	},

	changeHamsterTexture : function () {
		this._type = "out";
		this.callbackFunc();
		this._hamster.setSpriteFrame(cc.spriteFrameCache.getSpriteFrame("dishu01.png"));
	}

});
