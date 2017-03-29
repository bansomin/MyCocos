/**
 * Created by HAO on 2017/2/4.
 * Brief   :
 * Version :
 */


var SetLayer = cc.Layer.extend({

	_board	:	null,

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
		this._board = new cc.Sprite(res.ui.setBoard);
		this._board.setPosition(cc.p(Wsize.width/2, Wsize.height + this._board.getContentSize().height));
		this._board.setScale(0.7);
		this.addChild(this._board);
		this._board.runAction(
			cc.sequence(
				cc.moveTo(1, cc.p(Wsize.width/2, Wsize.height/2)).easing(cc.easeElasticOut()),
				cc.callFunc(this.actionFunc, this)
			)
		);

		//back按钮
		var btn_back = new cc.MenuItemImage("#back-btn.png",
											"#back-btn-s.png",
											this.clickBackFunc,this);
		btn_back.setScale(1.1);
		btn_back.setPosition(btn_back.getContentSize().width * 2, this._board.getContentSize().height - btn_back.getContentSize().height);
		btn_back.runAction(
			cc.moveTo(1.5, cc.p(btn_back.getContentSize().width, this._board.getContentSize().height - btn_back.getContentSize().height)).easing(cc.easeElasticOut())
		);

		//音效
		var item_effec = new SoundToggleCell(false);
		item_effec.setPosition(this._board.getContentSize().width, this._board.getContentSize().height*2/3 - 10);
		item_effec.runAction(
			cc.sequence(
				cc.delayTime(0.1),
				cc.moveTo(2, this._board.getContentSize().width*2/3, this._board.getContentSize().height*2/3 - 10).easing(cc.easeElasticOut())
			)
		);

		//背景音乐
		var item_music = new SoundToggleCell(true);
		item_music.setPosition(this._board.getContentSize().width, item_effec.getPositionY() - 90);
		item_music.runAction(
			cc.sequence(
				cc.delayTime(0.2),
				cc.moveTo(1.9, this._board.getContentSize().width*2/3, item_effec.getPositionY() - 90).easing(cc.easeElasticOut())
			)
		);

		//难易程序
		var item_level = new LevelToggleCell();
		item_level.setPosition(this._board.getContentSize().width, item_music.getPositionY() - 90);
		item_level.runAction(
			cc.sequence(
				cc.delayTime(0.3),
				cc.moveTo(1.8, this._board.getContentSize().width*2/3, item_music.getPositionY() - 90).easing(cc.easeElasticOut())
			)
		);

		var menu = new cc.Menu(btn_back, item_effec, item_music, item_level);
		//menu.alignItemsVertically(50);
		menu.attr({
			anchorX :   0,
			anchorY :   0,
			x       :   0,
			y       :   0
		});
		this._board.addChild(menu);

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