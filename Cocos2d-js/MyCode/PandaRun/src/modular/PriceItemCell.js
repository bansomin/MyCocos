/**
 * Created by HAO on 2017/2/6.
 * Brief   : 价格按钮
 * Version :
 */

var PriceItemCell = cc.MenuItemImage.extend({

	_type	:	null,	//物品名称
	_price	:	0,		//物品价格

	_func	:	null,	//回调函数

	ctor : function (type, fun) {

		this._type = type;
		this._func = fun;

		var itemSpr= new cc.Sprite();
		switch (type){
			case GC.ITEMS.MAGNET :
				this._price = GC.PRICE.MAGNET;
				itemSpr = new cc.Sprite("#magnet-prop.png");
				break;
			case GC.ITEMS.BLUESHOES :
				this._price = GC.PRICE.BLUESHOES;
				itemSpr = new cc.Sprite("#shoes-prop.png");
				break;
			case GC.ITEMS.REDSHOES :
				this._price = GC.PRICE.REDSHOES;
				itemSpr = new cc.Sprite("#redshoes-prop.png");
				break;
			default :
				break;
		}
		var img = "#buy-" + this._price + ".png";
		this._super(img, img, img, fun, this);
		if (itemSpr!=null) {
			itemSpr.setScale(2);
			itemSpr.setPosition(-itemSpr.getContentSize().width/2, itemSpr.getContentSize().height);
			this.addChild(itemSpr);
		}
		this.setScale(0.5);

		this.runAction(
			cc.sequence(
				cc.delayTime(Math.random()),
				cc.scaleTo(1, 0.9, 0.9).easing(cc.easeBackInOut()),
				cc.scaleTo(0.2, 0.7, 0.7).easing(cc.easeBackInOut())
			).repeatForever()
		);
	},

	getItemPrice : function () {

		return this._price;
	}
});

