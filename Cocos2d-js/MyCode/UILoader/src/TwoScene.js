/**
 * Created by HAO on 2016/9/18.
 */

TwoLayer = cc.Layer.extend({

    ctor : function () {
        this._super();

        sz.uiloader.widgetFromJsonFile(this, "res/cocos/Inventory.json");
        this.rootNode.setScale(.7);

        this.init();
        
        return true;
    },
    
    init : function () {

    }
});

var TwoScene = cc.Scene.extend({

    onEnter : function () {
        this._super();

        var layer = new TwoLayer();
        this.addChild(layer);
    }
});