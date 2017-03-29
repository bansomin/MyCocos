/**
 * Created by HAO on 2017/2/4.
 * Brief   :
 * Version :
 */


var StoreLayer = cc.Layer.extend({

	_board		:	null,

	_goldBar	:	null,	//金币栏

	ctor : function () {
		this._super();

		Wsize = cc.director.getWinSize();

		//创建灰色背景框
		draw = new cc.DrawNode();
		draw.drawRect(cc.p(0, Wsize.height), cc.p(Wsize.width, 0), cc.color(0, 0, 0, 80), 0, cc.color(0, 0, 0, 80));
		this.addChild(draw);

		cc.eventManager.addListener({
			event : cc.EventListener.TOUCH_ONE_BY_ONE,
			swallowTouches : true,
			onTouchBegan   : function(touch, event){
				return true;
			}
		}, draw);

		this.init();

		return true;
	},

	init : function () {

		//背景
		this._board = new cc.Sprite(res.ui.storeBoard);
		this._board.setPosition(cc.p(Wsize.width/2, Wsize.height + this._board.getContentSize().height));
		this._board.setScale(0.7);
		this._board.setScale(0.6);
		this.addChild(this._board);
		this._board.runAction(
			cc.sequence(
				cc.moveTo(1, cc.p(Wsize.width/2, Wsize.height/2)).easing(cc.easeElasticOut()),
				cc.callFunc(this.actionFunc, this)
			)
		);

		//添加GoldBar
		this._goldBar = new GoldBarCell(function () {

		});
		this._goldBar.setPosition(this._board.getContentSize().width*3/4, this._board.getContentSize().height*4/5);


		//磁铁购买按钮
		var btn_magnet = new PriceItemCell(GC.ITEMS.MAGNET, function () {
			this.buyGoodsFunc(GC.ITEMS.MAGNET);
		}.bind(this));
		btn_magnet.setPosition(this._board.getContentSize().width/2 - 170, this._board.getContentSize().height/8);
		//蓝鞋购买按钮
		var btn_blueS = new PriceItemCell(GC.ITEMS.BLUESHOES, function () {
			this.buyGoodsFunc(GC.ITEMS.BLUESHOES);
		}.bind(this));
		btn_blueS.setPosition(this._board.getContentSize().width/2, btn_magnet.getPositionY());
		//红鞋购买按钮
		var btn_redS = new PriceItemCell(GC.ITEMS.REDSHOES, function () {
			this.buyGoodsFunc(GC.ITEMS.REDSHOES);
		}.bind(this));
		btn_redS.setPosition(this._board.getContentSize().width/2 + 170, btn_magnet.getPositionY());

		//back按钮
		var btn_back = new cc.MenuItemImage("#back-btn.png",
											"#back-btn-s.png",
											this.clickBackFunc,this);
		btn_back.setScale(1.1);
		btn_back.setPosition(btn_back.getContentSize().width * 2, this._board.getContentSize().height - btn_back.getContentSize().height);
		btn_back.runAction(
			cc.moveTo(1.5, cc.p(btn_back.getContentSize().width, this._board.getContentSize().height - btn_back.getContentSize().height)).easing(cc.easeElasticOut())
		);

		var menu = new cc.Menu(this._goldBar, btn_back, btn_magnet, btn_blueS, btn_redS);
		menu.attr({
			anchorX :   0,
			anchorY :   0,
			x       :   0,
			y       :   0
		});
		this._board.addChild(menu);

	},

	rechargeFunc : function () {
		cc.log("rechargeFunc");

		cc.log("当前金币：" + this._goldBar.getMyCoin());
		var coin = this._goldBar.getMyCoin() + 100;
		this._goldBar.updateMyCoin(coin);
		cc.log("充值后：" + this._goldBar.getMyCoin());
	},

	buyGoodsFunc : function (type) {
		cc.log("StoreLayer_buyGoodsFunc  " + type);

		cc.log("当前金币：" + this._goldBar.getMyCoin());

		switch (type){
			case GC.ITEMS.MAGNET :
				var coin = this._goldBar.getMyCoin() - GC.PRICE.MAGNET;
				if (coin>=0) {
					new MessageBox().addTips(GC.INFO.BUYMAGNET,function () {
						this.updateMyCoin(coin);
					}.bind(this), this);
				}
				else {
					new MessageBox().addTips(GC.INFO.BUYFAIL, function () {});
				}
				break;
			case GC.ITEMS.BLUESHOES :
				var coin = this._goldBar.getMyCoin() - GC.PRICE.BLUESHOES;
				if (coin>=0) {
					new MessageBox().addTips(GC.INFO.BUYBLUESHOES,function () {
						this.updateMyCoin(coin);
					}.bind(this), this);
				}
				else {
					new MessageBox().addTips(GC.INFO.BUYFAIL, function () {});
				}
				break;
			case GC.ITEMS.REDSHOES :
				var coin = this._goldBar.getMyCoin() - GC.PRICE.REDSHOES;
				if (coin>=0) {
					new MessageBox().addTips(GC.INFO.BUYREDSHOES,function () {
						this.updateMyCoin(coin);
					}.bind(this), this);
				}
				else {
					new MessageBox().addTips(GC.INFO.BUYFAIL, function () {});
				}
				break;
			default:
				break;
		}
		Sound.playEffectBtn();
	},

	updateMyCoin : function (coin) {
		cc.log("Store_coin : " + coin);
		this._goldBar.updateCoin(coin);
	},

	clickBackFunc : function(){

		Sound.playEffectBtn();

		this.unscheduleUpdate();

		this._board.runAction(
			cc.sequence(
				cc.moveTo(0.5, cc.p(Wsize.width/2, Wsize.height + this._board.getContentSize().height)).easing(cc.easeElasticOut()),
				cc.callFunc(this.removeFromParentFunc, this)
			)
		);
	},

	removeFromParentFunc : function () {
		cc.log("removed");

		this.removeFromParent();
	},

	actionFunc : function () {

		this.scheduleUpdate();
	},

	//实现动画的上下移动
	update : function(){
		var currentDate = new Date();
		this._board.y = Wsize.height/2 + (Math.cos(currentDate.getTime() * 0.003)) * 2;
	}

});