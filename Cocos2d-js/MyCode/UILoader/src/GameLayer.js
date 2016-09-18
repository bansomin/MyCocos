/**
 * Created by HAO on 2016/9/14.
 */

GameLayer = cc.LayerColor.extend({

    rootNode    :   null,

    ctor : function () {
        this._super(cc.color.GREEN);

        var button = new ccui.ImageView("res/Heiti10.png", ccui.Widget.LOCAL_TEXTURE);
        button.setName("_button");
        this.addChild(button);

        sz.uiloader.widgetFromJsonFile(this, "res/DemoLogin.ExportJson", {eventPrefix : "_on", memberPrefix : "_"});
        this.rootNode.setPosition(this.width/2, this.height/2);
        this.rootNode.setAnchorPoint(0.5, 0.5);

        this.testRegisterTouchEvent();
    },

    testRegisterTouchEvent : function () {

        //为当前layer注册触摸
        sz.uiloader.registerTouchEvent(this, this);

        //创建一个Sprite并注册
        var spr = new cc.Sprite("#button.png");
        spr.setName("_spriteButton");
        spr.setPosition(this.width - spr.width*0.5, spr.height*0.5);
        this.addChild(spr);
        sz.uiloader.registerTouchEvent(spr, this);
    },

    //spr
    _onSpriteButtonTouchBegan : function () {
        cc.log("_onSpriteButtonTouchBegan");

        return;
    },

    //layer
    _onTouchBegan : function (sender, touch) {
        cc.log("_onTouchBegan");

        return true;
    },

    _onTouchMoved : function (sender, touch) {
        cc.log("_onTouchMoved");
    },

    _onTouchEnded : function (sender, touch) {
        cc.log("_onTouchEnded");
    },

    //录按钮检测一
    /*
    _onLoginButtonTouchBegan : function () {
        cc.log("_onLoginButtonTouchBegan");

    },

    _onLoginButtonTouchMoved : function () {
        cc.log("_onLoginButtonTouchMoved");

    },

    _onLoginButtonTouchEnded : function () {
        cc.log("_onLoginButtonTouchEnded");

    },
    */

    //登录按钮检测二
    _onLoginButtonEvent : function (sender, type) {

        switch (type){
            case 0:
                cc.log("_onLoginButtonEvent_began.");
                break;
            case 1:
                cc.log("_onLoginButtonEvent_move.");
                break;
            case 2:
                cc.log("_onLoginButtonEvent_end.");
                cc.loader.load(g_cocos, function () {
                    var scene = new TwoScene();
                    cc.director.runScene(scene);
                })
                break;
        }
    },

    //长按登录按钮
    _onLoginButtonTouchLong : function (sender, type) {
        cc.log("_onLoginButtonTouchLong.");
    },

    //关闭按钮
    _onCloseButtonEvent : function (sender, type) {

        switch (type){
            case 0:
                cc.log("_onCloseButtonEvent_began.");
                break;
            case 1:
                cc.log("_onCloseButtonEvent_move.");
                break;
            case 2:
                cc.log("_onCloseButtonEvent_end.");
                break;
        }
    },

    //长按登录按钮
    _onCloseButtonTouchLong : function (sender, type) {
        cc.log("_onCloseButtonTouchLong.");
    },

    //nameTextField
    _onNameTextFieldInsertText : function (sender) {
       cc.log(sender.string);
    },

    _onNameTextFieldDeleteBackward : function (sender) {
        cc.log(sender.string);
    },

    _onAgreeCheckBoxSelected : function (sender) {
        cc.log("_onAgreeCheckBoxSelected");
    },

    //名称标签触摸
    _onNameLabelTouchBegan : function () {
        cc.log("_onNameLabelTouchBegan");
    },

    //名称标签长按
    _onNameLabelTouchLong : function () {
        cc.log("_onNameLabelTouchLong");
    }

});
