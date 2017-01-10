/**
 * Created by HAO on 2016/12/13.
 * Brief   : 解释、出处信息
 * Version :
 */

var DetailLayer = cc.Sprite.extend({

	_bg			:	null,
	_exp		:	"",
	_expLabel	:	null,

	ctor : function (exp) {
		this._super();

		if (exp) {
			this._exp = exp;
		}

		Wsize = cc.director.getWinSize();

		this._bg = new cc.Sprite(res.png_bg_exp);
		this.addChild(this._bg);

		this._expLabel = new cc.LabelTTF(this._exp, "arail", 30);
		this._expLabel.setPosition(this._bg.getContentSize().width/2 + 20, this._bg.getContentSize().height/3);
		this._expLabel.setColor(cc.color(0, 0, 0));
		this._expLabel.setDimensions(460, 200);
		this._bg.addChild(this._expLabel);

		this._bg.setScale(1, 0);

		return true;
	},

	setExp : function (exp) {
		this._exp = exp;
		this._expLabel.setString(this._exp);
	},

	getExp : function () {
		return this._exp;
	},

	getHeightFunc : function () {

		return this._bg.getContentSize().height;
	},

	changeAction : function (isShow) {
		cc.log("changeAction");

		var scale = null;
		if (isShow) {
			scale = cc.scaleTo(0.2, 1, 1).easing(cc.easeBackInOut());
		}
		else {
			scale = cc.scaleTo(0.2, 1, 0).easing(cc.easeBackInOut());
		}
		this._bg.runAction(scale);
	}

});