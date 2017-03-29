/**
 * Created by HAO on 2017/2/15.
 * Brief   : 创建所有金币并存储到PlaySingleLayer中
 * Version :
 */

var ObjectShapedGenerator = cc.Class.extend({

	_px	:	0,
	_py	:	0,

	_gold	:	[],
	_layer	:	null,
	_objectGeneratorFunc	:	null,

	ctor : function (layer, objectGeneratorFunc) {

		if (!objectGeneratorFunc) {
			objectGeneratorFunc = function (x, y) {
				return new Gold(x, y);	//默认创建金币
			}
		}

		this._layer = layer;
		this._objectGeneratorFunc = objectGeneratorFunc;

		//创建所有的金币
		for (var i = 0; i < GC.NUMBERS.GOLD; i++) {
			//cc.log("i : " + i);
			this._gold[i] = this._objectGeneratorFunc(-100, -100);
			this._layer.addRole(this._gold[i]);
			this._layer._objects.push(this._gold[i]);
		}
	},

	generate : function (platform) {
		//cc.log("generate_ObjectShapedGenerator");
		if ((!platform)) {
			return;
		}

		this._px = platform.getX();
		this._py = platform.getY();
		var herox = this._layer._hero.getX();
		//cc.log("px : " + this._px + " &hero : " + herox);
		if ((this._layer._hero.getX() - this._gold[0].getX())>800 && (this._px>this._layer._hero.getX())) {
			this.create(parseInt(Math.random()*7));
		}
	},

	create : function (type) {
		cc.log("create : " + type);

		var x, y, dy, dy2;
		switch (type){
			case 0 :	//桥形
				x = this._px + 200;
				y = this._py + 140;
				var radius = Math.random()*6 + 5;
				for (var i = -4; i < 5; i++) {
					x += 60;
					dy = -i * i * radius + 100;
					this._gold[4+i].initPos(cc.p(x, y + dy));
				}
				break;
			case 1 :	//矩形
				x = this._px + 130;
				y = this._py + 150;
				var k = 0;
				for (var i = 0; i < 4; i++) {
					for (var j = 0; j < 3; j++) {
						this._gold[k].initPos(cc.p(x + i*60, y + j*60));
						++k;
					}
				}
				break;
			case 2 :	//单线
				x = this._px + 130;
				y = this._py + 130;
				var nums = 6;
				for (var i = 0; i < nums; i++) {
					this._gold[i].initPos(cc.p(x + i*60, y));
				}
				break;
			case 3 :	//双线
				x = this._px + 130;
				y = this._py + 110;
				var nums = 6;
				var k = 0;
				for (var i = 0; i < nums; i++) {
					for (var j = 0; j < 2; j++) {
						this._gold[k].initPos(cc.p(x + i*60, y + j*50));
						++k;
					}
				}
				break;
			case 4 :	//双桥
				x = this._px + 200;
				y = this._py + 140;
				var radius = Math.random() * 5 + 5;
				for (var i = -4; i < 5; i++) {
					x += 60;
					dy  = -i * i * radius + 100;
					dy2 = -i * i * radius + 170;
					this._gold[i+4].initPos(cc.p(x, y + dy));
					this._gold[i+13].initPos(cc.p(x, y + dy2));
				}
				break;
			case 5 :	//三角形
				var k  = 0;
				var dx = 0;
				var dy = 0;
				x = this._px + 220;
				y = this._py + 130;

				for (var i = 0; i < 6; i++) {
					dy = i*40;
					dx = i*25;
					for (var j = 0; j < 6-i; j++) {
						this._gold[k].initPos(cc.p(x + dx + j*50, y + dy));
						++k;
					}
				}
				break;
			case 6 :	//棱形
				x = this._px + 200;
				y = this._py + 120;
				var k = 0;
				for (var i = 0; i < 7; i++) {
					dy = i * 35;
					var nums= 0;
					if (i<4) {
						nums = i+1;
						var offsetLeft = (3-i)*30;
					}
					else {
						nums = 7-i;
						var offsetLeft = (i-3)*30;
					}
					for (var j = 0; j < nums; j++) {
						this._gold[k].initPos(cc.p(x + offsetLeft + j * 60, y + dy));
						++k;
					}
				}
				break;
		}
	}

});