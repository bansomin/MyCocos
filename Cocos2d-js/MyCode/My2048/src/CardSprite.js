/**
 * Created by Bansomin on 5/26/2016.
 */

var CardSprite = cc.Sprite.extend({

    _number     :   0,
    _labelNum   :   0,
    _posX       :   0,
    _posY       :   0,
    _bgColor    :   null,   //背景
    _sprite     :   null,

    //图片开关
    _isTure1    :   true,      //图片1的判定;
    _isTure2    :   true,      //图片2的判定;
    _isTure3    :   true,      //图片3的判定;

    ctor : function (number, width, height, posx, posy) {
        this._super();

        this._posX   = posx;
        this._posY   = posy;
        this._number = number;

        this._bgColor = new cc.LayerColor(cc.color(204, 192, 179, 255), width, height);
        this._bgColor.setContentSize(width,height);
        this._bgColor.setPosition(cc.p(posx, posy));
        this.addChild(this._bgColor);
        
        //判断如果大于0就显示，否则显示为空；
        if (this._number > 0 && this._number < 10000){
            this.addLabelFunc(this._number);
        }
        else {
            this.addLabelFunc("");
        }
    },

    addLabelFunc : function (number) {
        this._labelNum = new cc.LabelTTF(number, "HiraKakuProN-W6", 100);
        this._labelNum.setPosition(cc.p(this._bgColor.getContentSize().width/2,
                                            this._bgColor.getContentSize().height/2));
        this._bgColor.addChild(this._labelNum);
    },
    
    getNumber : function () {
        return this._number;
    },
    
    setNumber : function (number) {
        printf("setNumber = ", number);

        this._number = number;
        //设置背景颜色
        this.setCardColorFunc();

        if (this._number >= 0) {
            this._labelNum.setFontSize(100);
        }
        if (this._number >= 16) {
            this._labelNum.setFontSize(90);
        }
        if(this._number >= 128){
            this._labelNum.setFontSize(70);
        }
        if(this._number >= 1024){
            this._labelNum.setFontSize(60);
        }

        if (this._number > 0 && this._number < 10000){
            if (this._sprite){
                this._sprite.removeFromParent();
            }
            this._labelNum.setVisible(true);
            this._labelNum.setString(this._number);
        }
        else if (this._number <= 0){
            if (this._sprite){
                this._sprite.removeFromParent();
            }
            this._labelNum.setVisible(true);
            this._labelNum.setString("");
        }
        else if (this._number == 10001){
            this.addSetFunc("res.png_xin");
        }
        else if (this._number == 10002){
            this.addSetFunc("res.png_nian");
        }
        else if (this._number == 10003){
            this.addSetFunc("res.png_hao");
        }
        else if (this._number == 20003){
            this.addSetFunc("res.png_xinnian");
        }
        else if (this._number == 20004){
            this.addSetFunc("res.TIME_PNG");
        }
        else if (this._number == 20005){
            this.addSetFunc("res.STAR_PNG");
        }
        else if (this._number == 30006){
            this.addSetFunc("res.png_xinnianhao");
        }
    },

    addSetFunc : function (url) {
        printf("addSetFunc.");
        printf("url = ", url);

        if (this._labelNum){
            this._labelNum.setVisible(false);
        }

        if (this._sprite){
            this._sprite.removeFromParent();
        }

        this._sprite = new cc.Sprite(eval(url));
        this._sprite.setPosition(cc.p(this._bgColor.getContentSize().width/2,
                                            this._bgColor.getContentSize().height/2));
        this._bgColor.addChild(this._sprite);
    },

    setCardColorFunc : function () {
        printf("setCardColorFunc = ", this._number);

        switch (this._number){
            case 0 :
                this._bgColor.setColor(cc.color(200,190,180));
                break;
            case 2 :
                this._bgColor.setColor(cc.color(240,230,220));
                break;
            case 4 :
                this._bgColor.setColor(cc.color(240,220,200));
                break;
            case 8 :
                this._bgColor.setColor(cc.color(240,180,120));
                break;
            case 16 :
                this._bgColor.setColor(cc.color(240,140,90));
                break;
            case 32 :
                this._bgColor.setColor(cc.color(240,120,90));
                break;
            case 64 :
                this._bgColor.setColor(cc.color(240,90,60));
                break;
            case 128 :
                this._bgColor.setColor(cc.color(240,90,60));
                break;
            case 256 :
                this._bgColor.setColor(cc.color(240,200,70));
                break;
            case 512 :
                this._bgColor.setColor(cc.color(240,200,70));
                break;
            case 1024 :
                this._bgColor.setColor(cc.color(0,130,0));
                break;
            case 2048 :
                this._bgColor.setColor(cc.color(0,230,0));
                break;
            default   :
                break;
        }
    },

    getCardPosX : function () {
        return this._posX;
    },

    setCardPosY : function (posx) {
        this._posX = posx;
    },

    getCardPosY : function () {
        return this._posY;
    },
    
    setCardPosY : function (posy) {
        this._posY = posy;
    }
});








