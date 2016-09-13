/**
 * Created by Bansomin on 5/26/2016.
 */

var PromptLayer = cc.LayerColor.extend({

    _bgColor    :   null,

    ctor : function (width, heigth) {
        this._super(cc.color(255,255,255));

        this.setContentSize(width, heigth);

        var size = this.getContentSize();

        var label_tishi = new cc.LabelTTF("提示", "Arial", 50);
        label_tishi.setPosition(size.width/2, size.height - 50);
        label_tishi.setColor(cc.color(0, 0, 0));
        this.addChild(label_tishi);

        var spr_xin = new cc.Sprite(res.png_xin);
        spr_xin.setPosition(100, size.height-180);
        this.addChild(spr_xin);

        var label_add = new cc.LabelTTF("+", "", 50);
        label_add.setPosition(210, size.height-180);
        label_add.setColor(cc.color(0, 0, 0));
        this.addChild(label_add);

        var spr_nian = new cc.Sprite(res.png_nian);
        spr_nian.setPosition(320, size.height-180);
        this.addChild(spr_nian);

        var label_equ = new cc.LabelTTF("=", "", 50);
        label_equ.setPosition(420, size.height-180);
        label_equ.setColor(cc.color(0, 0, 0));
        this.addChild(label_equ);

        var spr_xinnian=new cc.Sprite(res.png_xinnian);
        spr_xinnian.setPosition(520, size.height-180);
        this.addChild(spr_xinnian);

        /******************************************/

        var spr_xinnianTwo = new cc.Sprite(res.png_xinnian);
        spr_xinnianTwo.setPosition(100, size.height-380);
        this.addChild(spr_xinnianTwo);

        var label_addTwo = new cc.LabelTTF("+", "", 50);
        label_addTwo.setPosition(210, size.height-380);
        label_addTwo.setColor(cc.color(0,0,0));
        this.addChild(label_addTwo);

        var spr_hao = new cc.Sprite(res.png_hao);
        spr_hao.setPosition(320, size.height-380);
        this.addChild(spr_hao);

        var label_equTwo = new cc.LabelTTF("=", "", 50);
        label_equTwo.setPosition(420, size.height-380);
        label_equTwo.setColor(cc.color(0, 0, 0));
        this.addChild(label_equTwo);

        var spr_xinnianhao = new cc.Sprite(res.png_xinnianhao);
        spr_xinnianhao.setPosition(520, size.height-380);
        this.addChild(spr_xinnianhao);

        var btn = new ccui.Button(res.png_btn);
        btn.setPosition(size.width/2, 100);
        this.addChild(btn);
        var me=this;
        btn.addClickEventListener(function(){
            me.removeFromParent();
        });

        var font = new cc.LabelTTF("集齐所有图片即可获得奖励", "", 30);
        font.setPosition(size.width/2,200);
        font.setColor(cc.color(0,0,0));
        this.addChild(font);

        //触控
        cc.eventManager.addListener({
            event          : cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches : true,
            onTouchBegan   : function (touch, event) {
                printf("PromptLayer_touch.");
                return true;
            },
        }, this);

        return true;
    }
});





















