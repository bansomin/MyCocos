/**
 * Created by Bansomin on 5/26/2016.
 */
var PromptLayerTwo = cc.LayerColor.extend({
    
    _bgColor    :   null,
    
    ctor : function (width, height, spr_xin, spr_nian, spr_hao) {
        this._super(cc.color(255,255,255));
        this.setContentSize(width,height);
        
        Wsize = cc.winSize;
        Csize=this.getContentSize();

        var label_tip = new cc.LabelTTF("提示", "", 50);
        label_tip.setPosition(Csize.width/2, Csize.height - 100);
        label_tip.setColor(cc.color(0, 0, 0));
        this.addChild(label_tip);
        
        spr_xin.setPosition(100, Csize.height-300);
        this.addChild(spr_xin);

        var label_add = new cc.LabelTTF("+", "", 50);
        label_add.setPosition(210, Csize.height - 300);
        label_add.setColor(cc.color(0, 0, 0));
        this.addChild(label_add);

        spr_nian.setPosition(320, Csize.height - 300);
        this.addChild(spr_nian);

        var label_equ = new cc.LabelTTF("=", "", 50);
        label_equ.setPosition(420,Csize.height - 300);
        label_equ.setColor(cc.color(0, 0, 0));
        this.addChild(label_equ);

        spr_hao.setPosition(520, Csize.height - 300);
        this.addChild(spr_hao);

        var button = new ccui.Button(res.png_btn);
        button.setPosition(Csize.width/2,100);
        this.addChild(button);
        var me=this;
        button.addClickEventListener(function(){
            me.removeFromParent();
        });

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











