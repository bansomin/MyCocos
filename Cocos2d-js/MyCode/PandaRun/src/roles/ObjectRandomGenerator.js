/**
 * Created by HAO on 2017/2/15.
 * Brief   : 创建鞋子（默认蓝）并存储到PlaySingleLayer中
 * Version :
 */

var ObjectRandomGenerator = cc.Class.extend({

	_px	:	0,
	_py	:	0,

	_objSpr			:	null,
	_objArr			:	[],
	_layer			:	null,
	_opt			:	null,
	_previousX		:	0,
	_objectGeneratorFunc	:	null,

	ctor : function (layer, objectGeneratorFunc, opt) {

		// if (!objectGeneratorFunc) {
		// 	//cc.log("if");
		// 	objectGeneratorFunc = function (x, y) {
		// 		return new BlueShoes(x, y);	//创建蓝鞋
		// 	}
		// }

		if (!objectGeneratorFunc) {
			var itme = new BlueShoes(-100, -100);
			objectGeneratorFunc = function (x, y) {
				itme._sprite.setPosition(x, y);
				return itme;
			}
		}

		this._opt = opt || {
			height 	: 200,
			gap 	: 2500
		};

		this._layer = layer;
		this._objectGeneratorFunc = objectGeneratorFunc;

		//鞋子（蓝、红）、磁铁
		this._objSpr = this._objectGeneratorFunc(100, 100);	//设置鞋子的位置
		this._layer._objects.push(this._objSpr);
		this._layer.addRole(this._objSpr);
	},

	generate : function (platform) {
		//cc.log("generate_ObjectRandomGenerator");

		if (!platform) {
			return;
		}

		this._px = platform.getLastX() + parseInt(Math.random()*300 + 200);
		this._py = platform.getY() + this._opt.height;

		if (((this._layer._hero.getX() - this._objSpr.getX())>this._opt.gap) && (Math.random()*1000>999)) {
			this._objSpr = this._objectGeneratorFunc(cc.p(this._px, this._py));
		}
	},

	cleanup : function () {
		for (var i = 0; i < this._objArr.length; i++) {
			if ((this._objArr[i].getShape() != null) &&(this._objArr[i] != undefined)) {
				if (this._layer._hero._sprite.getPositionX() > (this._objArr[i].getX()+300)) {
					this._objArr[i].removeFromLayer();
					delete this._objArr[i];
					this._objArr.splice(i, 1);
				}
			}
			else {
				this._objArr.splice(i, 1);
			}
		}
	}

});