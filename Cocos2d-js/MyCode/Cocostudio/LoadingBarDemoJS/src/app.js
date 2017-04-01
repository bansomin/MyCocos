
var HelloWorldLayer = cc.Layer.extend({

    _loadingBar :   null,
    _text       :   null,
    sprite      :   null,

    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        var size = cc.winSize;

        var helloLabel = new cc.LabelTTF("Hello World", "Arial", 38);
        helloLabel.x = size.width / 2;
        helloLabel.y = size.height / 2 + 200;
        this.addChild(helloLabel, 5);

        //加载cocostudio的JSON文件
        var json = ccs.load(res.cocosJson);
        var node = json.node;
        this.addChild(node);

        //获取进度条
        this._loadingBar = ccui.helper.seekWidgetByName(node, "LoadingBar_1");
        //获取Text
        this._text = ccui.helper.seekWidgetByName(node, "Text_1");

        //this.schedule(this.updateFunc, 0.05);

        this.scheduleUpdate();

        return true;
    },

    update : function (dt) {

        var num = this._loadingBar.getPercent();
        this._loadingBar.setPercent(++num);

        this._text.setString(num + "%");
        if(!this._text.isVisible()){
            this._text.setVisible(true);
        }

		if (this._loadingBar.getPercent()>=100) {
            this.unscheduleUpdate();    //停止定时器

            var label = new cc.LabelTTF("加载完成", "arial", 25);
            label.attr({
                x   :   this._loadingBar.getPositionX(),
                y   :   this._loadingBar.getPositionY() + label.getContentSize().height*2
            });
            this.addChild(label);
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

