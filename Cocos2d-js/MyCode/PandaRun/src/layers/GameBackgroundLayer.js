/**
 * Created by HAO on 2017/2/13.
 * Brief   : 背景层相关代码
 * Version :
 */

var GameBackgroundLayer = cc.Layer.extend({

	_nearBg			:	null,
	_nearBgIndex	:	0,

	ctor : function (camera, resurl, options) {

		this._super();

		Wsize = cc.director.getWinSize();

		this._nearBg = this.titleBg(this.createBg(resurl).bind(this));

		var self = this;
		if (!options) {
			options = {
				scaleX : 2,
				scaleY : 1
			}
		}

		camera.addListener(function (pos) {
			var eyeX = pos.x;
			var eyeY = pos.y;
			self.refresh(eyeX/options.scaleX, eyeY/options.scaleY);
			self.setPosition(cc.p(-eyeX/options.scaleX, -eyeY/options.scaleY));
		});
	},

	titleBg : function (func) {
		cc.log("titleBg");

		var doubleWinWidth = Wsize.width*2;
		var remainWidth = doubleWinWidth;
		var tiles = [];

		do{
			var nearBg = func(cc.p(doubleWinWidth - remainWidth, 0));
			remainWidth -= nearBg.getContentSize().width;
			tiles.push(nearBg);
			this.addChild(nearBg);
		}while (remainWidth>0);
		if (tiles.length < 2) {
			var nearBg = func(cc.p(doubleWinWidth - remainWidth, 0));
			tiles.push(nearBg);
			this.addChild(nearBg);
		}

		return tiles;
	},

	createBg : function (resurl) {
		cc.log("createBg");

		return function (pos) {
			pos = pos || cc.p(0, 0);
			var bg = new cc.Sprite(resurl);
			bg.setPosition(pos);
			bg.attr({
				anchorX	:	0,
				anchorY	:	0
			});
			return bg;
		}
	},

	refresh : function (x, y) {

		var newIndex = parseInt(x/this._nearBg[0].width);
		if (this._nearBgIndex == newIndex) {
			return false;
		}
		this._nearBg[(newIndex + this._nearBg.length - 1) % this._nearBg.length].setPositionX(this._nearBg[0].width * (newIndex + this._nearBg.length - 1));
		this._nearBgIndex = newIndex;

		return true;
	}

});