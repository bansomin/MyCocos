/**
 * Created by HAO on 2016/12/8.
 * Brief   : 候选项的汉字单元
 * Version :
 */

var WordCellModel = cc.Sprite.extend({

	_bg			:	null,	//背景
	_word		:	"",		//汉字
	_wordLabel	:	null,	//汉字标签

	ctor : function (word) {
		this._super();

		if (word) {
			this._word = word;
		}

		this._bg = new cc.Sprite("#kong5.png");
		this._bg.setScale(1.2);
		this.addChild(this._bg);

		this._wordLabel = new cc.LabelTTF(this._word, "arial", 55);
		//this._wordLabel = new cc.LabelTTF(this._word, "myFont", 55);
		this._wordLabel.setColor(cc.color(0, 0, 0));
		this._wordLabel.setPosition(cc.p(this._bg.getContentSize().width/2, this._bg.getContentSize().height/2));
		this._bg.addChild(this._wordLabel);

		return true;
	},

	setWord : function (word) {
		cc.log("wordCellModel+setWord");
		this._word = word;
		this._wordLabel.setString(word);
	},

	getWord : function () {
		return this._word;
	},

	getBoxWidth	: function () {
		return this._bg.getBoundingBox().width;
	},

	//改变字的背景色
	changeWordBG : function (isSelected) {
		if (isSelected) {
			this._wordLabel.setScale(1.1);
			this._bg.setSpriteFrame(cc.spriteFrameCache.getSpriteFrame("kong3.png"));
		}
		else {
			this._wordLabel.setScale(1);
			this._bg.setSpriteFrame(cc.spriteFrameCache.getSpriteFrame("kong5.png"));
		}
	},

	changeAction : function (isForever) {

		var scale1 = cc.scaleTo(0.04, 1.4, 1.4).easing(cc.easeBackInOut());
		var scale2 = cc.scaleTo(0.1, 0.8, 0.8);
		var scale3 = cc.scaleTo(0.08, 1.2, 1.2).easing(cc.easeBackInOut());
		var seq = cc.sequence(scale1, scale2, scale3);
		if (isForever) {
			this._bg.runAction(seq.repeatForever());
		}
		else {
			this._bg.runAction(seq);
		}
	}

});