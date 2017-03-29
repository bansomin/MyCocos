/**
 * Created by HAO on 2017/2/15.
 * Brief   :
 * Version :
 */

var PlatformGenerator = cc.Class.extend({
	
	_layer	:	null,
	
	_platformArr	:	[],
	_lastPlatform	:	null,

	_platformGeneratorFunc	:	null,
	
	ctor : function (layer, more, platformGeneratorFunc, pos) {

		Wsize = cc.director.getWinSize();

		if (!pos) {
			pos = {
				x	:	Wsize.width/2,
				y	:	Wsize.height/2 - 50
			};
		}

		if (!platformGeneratorFunc) {
			platformGeneratorFunc = function (x, y, length) {
				return new Platform(x, y, length);
			}
		}

		this._layer = layer;
		this._platformGeneratorFunc = platformGeneratorFunc;

		var platform = this._platformGeneratorFunc(pos.x, pos.y, 2);
		this._layer.addRole(platform);
		this._platformArr.push(platform);
		if (more) {
			this.generate(platform.getLastX());
		}
	},

	//生成随机平台
	generate : function (x) {

		var gap = parseInt(Math.random() * 200 + 100);
		var height = parseInt(Math.random() * 150 + 100);
		var block = parseInt(Math.random() * 4);	//0，1，2，3

		var platform = this._platformGeneratorFunc(x + gap, height, block);
		this._layer.addRole(platform);
		this._platformArr.push(platform);

		return this._lastPlatform = platform;
	},

	//平台的反复移动
	update : function (dt) {

		for (var i = 0; i < this._platformArr.length; i++) {
			if ((this._layer.getEyeX() - this._platformArr[i].getLastX()) < 0) {
				break;
			}
			else if (this._platformArr[i] != undefined) {
				this._platformArr[i].removeFromLayer();
			}
		}

		this._platformArr.splice(0, i);

		var mostX = this._platformArr[this._platformArr.length - 1].getLastX();
		if (mostX < this._layer.getEyeX() + Wsize.width) {
			return this.generate(mostX);
		}

		return this._lastPlatform;
	}
	
});
