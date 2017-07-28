
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        var Wsize = cc.director.getWinSize();

		var btn = new cc.MenuItemImage(res.btn, res.btn2, this.onClickBtn);
		var menu = new cc.Menu(btn);
		menu.attr({
			x   :   Wsize.width/2,
			y   :   Wsize.height/2
		});
		this.addChild(menu, 1);

        return true;
    },

	onClickBtn : function () {
        //cc.log("onClickBtn");
        console("onClickBtn");

		/*if (cc.sys.os == cc.sys.ANDROID) {
			cc.log("iffifiiffi");
			//var deviceID = jsb.reflection.callStaticMethod("org/cocos2dx/javascript/Cocos2dxActivity", "getDeviceID", "()Ljava/lang/String;");
			//cc.log("J:SODJFOSDIJFO:SDJF : " + deviceID);
		}
		else {
			cc.log("ELSEELSE");
		}*/
	}
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

