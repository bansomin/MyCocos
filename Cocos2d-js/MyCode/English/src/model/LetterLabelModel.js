/**
 * Created by HAO on 2016/11/24.
 * Brief   :	单词显示
 * Version :
 */

var LetterLabelModel = cc.Sprite.extend({

	_letter			:	null,	//字母
	_letterBg		:	null,	//背景
	_letterLabel	: 	null,	//字母标签
	_underline		:	null,	//下划线

	ctor : function (letter, isShow) {
		this._super();

		this._letter = letter;

		this._letterBg = new cc.Sprite("#touming.png");
		//this._letterBg = new cc.Sprite(res.png_butouming);
		this.addChild(this._letterBg);

		//下划线
		this._underline = new cc.Sprite("#xiahuaxian.png");
		this._underline.setPosition(0, -40);
		this._underline.setVisible(false);	//隐藏underline
		this.addChild(this._underline);

		this._letterLabel = new cc.LabelBMFont(this._letter, res.font_fnt_aht);
		if (this._letter=='w' || this._letter=='m') {	//'w','m'做特殊处理
			this._letterLabel.setScaleX(0.8);
		}
		this.addChild(this._letterLabel);

		return true;
	},

	//设置字母
	setLetter : function (letter) {

		this._letter = letter;
		this._letterLabel.setString(this._letter);
		//this.letterAction(letter);
	},

	//获取字母
	getLetter : function () {
		return this._letter;
	},

	//设置下划线的显隐
	setUnderlineShow : function (isShow) {
		this._underline.setVisible(isShow);
	},

	//字母动作
	letterAction : function (type) {

		var moveto = cc.moveTo(0.1, 0, 30);
		//var reverse_moveto = moveto.reverse();
		var reverse_moveto = cc.moveTo(0.1, 0, 0);
		var scale = cc.scaleTo(0.1, 1, 1);
		switch (type){
			case "show" :
				//cc.log("letter_out");
				this._letterLabel.setScaleY(0);
				var seq = cc.sequence(scale, moveto, reverse_moveto);
				this._letterLabel.runAction(seq);
				break;
			case "hide":
				//cc.log("letter_hide");
				var movetod = cc.moveTo(0.1, 0, -20);
				var callfunc = cc.callFunc(this.finishedFunc, this);
				var seq = cc.sequence(movetod, moveto, callfunc);
				this._letterLabel.runAction(seq);

				break
		}
	},

	finishedFunc : function () {
		this._letter = '';
		this._letterLabel.setString('');
		this._letterLabel.setPosition(0, 0);
	}

});

