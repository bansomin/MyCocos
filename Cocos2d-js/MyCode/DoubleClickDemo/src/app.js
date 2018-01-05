/**
 * Created by Bansomin on 2017/10/20.
 * Brief   :    cocos2d-js====单击 + 双击====
 * Version :
 */

var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
	isTouch		:	false,
	isDoubleTouch	:	false,

    ctor:function () {

        this._super();

        this.isTouch = false;
		this.isDoubleTouch = false;
		Wsize = cc.director.getWinSize();

		this.init();

        return true;
    },

	init : function () {

		this._infoLab = new cc.LabelTTF("wait", "arial", 40);
		this._infoLab.attr({
			x   :   Wsize.width/2,
			y   :   Wsize.height/2
		});
		this.addChild(this._infoLab);

		cc.eventManager.addListener({
			event          : cc.EventListener.TOUCH_ONE_BY_ONE,
			swallowTouches:true,
			onTouchBegan	: this.onTouchBegan.bind(this),
			onTouchEnded	:	this.onTouchEnded.bind(this)
		}, this);
	},

	onTouchBegan : function (touch, event) {

    	return true;
	},

	onTouchEnded : function (touch, event) {

    	this.isDoubleTouch = false;
		if(this.isTouch == false){
			this.isTouch = true;
			this.runAction(
				cc.sequence(
					cc.delayTime(.4),
					cc.callFunc(function () {
						this.isTouch = false;
						if(this.isDoubleTouch == true) return;
						//Single click
						cc.log('Single click');
						this._infoLab.setString("Single click");
					}, this)
				)
			);
		}else {
			this.isDoubleTouch = true;
			//Double click
			cc.log('Double click');
			this._infoLab.setString("Double click");
		}
	}
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

