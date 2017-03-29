/**
 * Created by HAO on 2017/2/3.
 * Brief   : 提示信息模块
 * Version :
 */

var MessageBox = cc.Node.extend({

	_bg		:	null,
	_node	:	null,
	_fun	:	null,

	ctor : function () {
		this._super();

		this._node = this;
		Wsize = cc.director.getWinSize();

		return true;
	},

	addTips : function (info, fun) {
		cc.log("addTips.");

		this._fun = fun;

		//提示信息面板
		this._bg = new cc.Sprite("#common_tips.png");
		this._bg.setPosition(Wsize.width/2, Wsize.height/10);
		this._bg.setScale(0);
		this._node.addChild(this._bg);

		//提示信息
		var label = new cc.LabelTTF(info, "Arial", 35);
		label.setPosition(this._bg.getContentSize().width/2, this._bg.getContentSize().height/2);
		this._bg.addChild(label);

		cc.director.getRunningScene().addChild(this._node,999);
		this.bgActionFunc();
	},

	//背景动画 
	bgActionFunc : function () {
		this._bg.runAction(
			cc.sequence(
				cc.scaleTo(0.2, 1, 1),
				cc.delayTime(1.8),
				cc.scaleTo(0.2, 0, 1),
				cc.callFunc(this.callback.bind(this),this)
			)
		);
	},

	//移除
	callback:function(){
		cc.log("Removed");
		this._node.removeFromParent();
		this._fun();
	}

});
