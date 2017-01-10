/**
 * Created by HAO on 2016/12/10.
 * Brief   : 答题板上的汉字单元模板
 * Version :
 */

var CCUModel = cc.Sprite.extend({

	_bg			:	null,	//背景
	_word		:	"",	//汉字
	_wordLabel	:	null,	//汉字标签

	_pos_Bot	:	null,
	_pos_Mid	:	null,
	_pos_Top	:	null,

	ctor : function (word) {
		this._super();

		if (word) {
			this._word = word;
		}

		this._bg = new cc.Sprite("#kuangbg.png");
		//this._bg.setScale(1.2);
		this.addChild(this._bg, -1);

		this._wordLabel = new cc.LabelTTF(this._word, "arial", 90);
		//this._wordLabel = new cc.LabelTTF(this._word, "myFont", 90);
		//this._wordLabel = new cc.LabelTTF(this._word, res.font_ttf, 90);

		this._pos_Top = cc.p(0, 90);
		this._pos_Mid = cc.p(0, 0);
		this._pos_Bot = cc.p(0, -100);

		// cc.log("bot : " + this._pos_Bot.x + " * " + this._pos_Bot.y);
		// cc.log("bot : " + this._pos_Mid.x + " * " + this._pos_Mid.y);
		// cc.log("bot : " + this._pos_Top.x + " * " + this._pos_Top.y);

		this._wordLabel.setColor(cc.color(0, 0, 0));
		this._wordLabel.setPosition(this._pos_Bot);
		this._wordLabel.setScale(0.65);
		this.addChild(this._wordLabel, 5);

		var mask = new cc.Sprite("#kuang001.png");
		mask.setPosition(0, 1);
		this.addChild(mask, 10);

		return true;
	},

	setWord : function (word) {
		cc.log("CCUModel+setWord");
		this._word = word;
		this._wordLabel.setString(word);
	},

	getWord : function () {
		return this._word;
	},

	getBoxWidth	: function () {
		return this._bg.getBoundingBox().width;
	},

	//动作改变
	changeAction : function (type) {
		//cc.log("type : " + type);

		var action = null;
		switch (type){
			case "tomid" :
				action = cc.moveTo(0.3, this._pos_Mid).easing(cc.easeBackInOut());
				break;
			case "totop" :
				var moveto = cc.moveTo(0.3, this._pos_Top).easing(cc.easeBackInOut());
				var callback = cc.callFunc(this.resetWordLabelPosition, this);
				action = cc.sequence(moveto, callback);
				break;
		}
		this._wordLabel.runAction(action);
	},

	resetWordLabelPosition : function () {
		this._word = "";
		this._wordLabel.setString(this._word);
		this._wordLabel.setPosition(this._pos_Bot);
	},

	setWordColor : function () {
		this._wordLabel.setColor(cc.color(244, 11, 34));
	}

});