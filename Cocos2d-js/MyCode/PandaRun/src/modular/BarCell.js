/**
 * Created by HAO on 2017/2/4.
 * Brief   : 相关显示栏
 * Version :
 */

var GoldBarCell = cc.MenuItemImage.extend({

	_func	:	null,	//回调函数
	_label	:	null,	//金币标签

	ctor : function (fun) {

		this._super("#gold-bar.png", "#gold-bar.png", "#gold-bar.png", this.rechargeFunc, this);

		//标签
		//GC.NUMBERS.COIN = "99998";
		this._label = new cc.LabelBMFont(GC.NUMBERS.COIN, res.font.fnt);
		this._label.setPosition(105, 20);
		this._label.setScale(0.5);
		this.addChild(this._label);

		this.runAction(
			cc.scaleTo(0.8, 1.3, 1.3).easing(cc.easeBackInOut())
		);

	},

	getMyCoin : function () {
		return GC.NUMBERS.COIN;
	},

	updateCoin : function (coin) {
		GC.NUMBERS.COIN = coin;
		this._label.setString(coin);
		//保存金币
		cc.sys.localStorage.setItem(GC.KEY.COIN, coin);
	},

	rechargeFunc : function () {

		GC.NUMBERS.COIN = parseInt(GC.NUMBERS.COIN) + 1000;
		if (GC.NUMBERS.COIN>99999) {
			GC.NUMBERS.COIN = 99999;
			this._label.setString(GC.NUMBERS.COIN);
			//保存金币
			cc.sys.localStorage.setItem(GC.KEY.COIN, GC.NUMBERS.COIN);
			new MessageBox().addTips(GC.INFO.COINFULL, function () {});
		}
		else {
			this._label.setString(GC.NUMBERS.COIN);
			//保存金币
			cc.sys.localStorage.setItem(GC.KEY.COIN, GC.NUMBERS.COIN);
		}
	}

});
