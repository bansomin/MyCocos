
var HelloWorldLayer = cc.LayerColor.extend({


    _isTouch        :   true,

    _beginPointX    :   0,
    _beginPointY    :   0,

    _cardArr        :   null,   //存放cards的数组

    //图片开关
    _isTure1    :   true,      //图片1的判定;
    _isTure2    :   true,      //图片2的判定;
    _isTure3    :   true,      //图片3的判定;

    _isShow     :   true,       //显示提示

    ctor:function () {
        printf("ctor.");

        this._super(cc.color(250, 248, 130, 255));
        
        Wsize = cc.winSize;
        
        this.init();

        return true;
    },
    
    init : function () {
        printf("init.");

        //卡片数组背景层;
        this._bgColor = new cc.LayerColor(cc.color(187, 173, 160, 255), Wsize.width, Wsize.height * 0.62);
        this._bgColor.setAnchorPoint(0, 0);
        this._bgColor.setPosition(0, 0);
        this.addChild(this._bgColor);

        //2048logo
        var logo=new cc.Sprite(res.png_label);
        logo.setPosition(Wsize.width/2,Wsize.height-150);
        logo.setScaleY(0.8);
        this.addChild(logo);

        //触控
        cc.eventManager.addListener({
            event          : cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches : true,
            onTouchBegan   : this.onTouchBegan.bind(this),
            onTouchEnded   : this.onTouchEnded.bind(this)
        }, this);

        this.createCardSprite(Wsize);

        //提示,合并屏幕中的图片
        this.showTipFunc();
        //提示层
        this.promptLayer();

        //产生两个随机数
        this.autoCreateCardNumber();
        this.autoCreateCardNumber();
    },

    onTouchBegan : function (touch, event) {
        printf("onTouchBegan.");

        var point = touch.getLocation();
        this._beginPointX = point.x;
        this._beginPointY = point.y;

        return this._isTouch;
    },

    onTouchEnded : function (touch, event) {
        printf("onTouchEnded.");
        
        var point = touch.getLocation();
        var endX = point.x - this._beginPointX;
        var endY = point.y - this._beginPointY;
        printf("sub = " + "(" + endX + "," + endY + ")");

        //判断方向
        if (Math.abs(endX) > Math.abs(endY)){
           if (Math.abs(endX)>50){
               if (endX < 0){
                   printf("left.");
                   if(this.doLeft()==true){
                       this.autoCreateCardNumber();
                   };
                   setTimeout(function(){
                       this.doCheckGameOver();
                   }.bind(this),1000);
               }
               else {
                   printf("right.");
                   if(this.doRight()==true){
                       this.autoCreateCardNumber();
                   };
                   setTimeout(function(){
                       this.doCheckGameOver();
                   }.bind(this),1000);
               }
           }
        }
        else if (Math.abs(endX) < Math.abs(endY)){
            if (Math.abs(endY)>50){
                if (endY < 0){
                    printf("down.");
                    if( this.doDown()==true){
                        this.autoCreateCardNumber();
                    };
                    setTimeout(function(){
                        this.doCheckGameOver();
                    }.bind(this),1000);
                }
                else {
                    printf("up.");
                    if(this.doUp() == true){
                        this.autoCreateCardNumber();
                    };
                    setTimeout(function(){
                        this.doCheckGameOver();
                    }.bind(this),1000);
                }
            }
        }
    },

    //左移动
    doLeft : function () {
        var isdo = false;
        for (var y = 0; y < 4; y++){
            for (var x = 0; x < 4; x++){
                for (var xx = x+1; xx < 4; xx++){
                    if (this._cardArr[xx][y].getNumber() > 0){
                        if (this._cardArr[x][y].getNumber() <= 0){  //左侧为空
                            this.UDLRCard(this._cardArr[xx][y], this._cardArr[x][y], true, this._cardArr[xx][y].getNumber());
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() == this._cardArr[xx][y].getNumber()){ //左右相等
                            this.UDLRCard(this._cardArr[xx][y], this._cardArr[x][y], true, this._cardArr[x][y].getNumber() * 2);
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() + this._cardArr[xx][y].getNumber() == 20003){  //xin_nian_hao
                            this.UDLRCard(this._cardArr[xx][y], this._cardArr[x][y], true, 20003);
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() + this._cardArr[xx][y].getNumber() == 30006){  //xin_nian_hao
                            this.UDLRCard(this._cardArr[xx][y], this._cardArr[x][y], true, 30006);
                            isdo = true;
                            this.GameWinFunc();
                        }
                        break;
                    }
                }
            }
        }
        return isdo;
    },

    //右移动
    doRight : function () {
        var isdo = false;
        for (var y = 0; y < 4; y++){
            for (var x = 3; x >= 0; x--){
                for (var xx = x-1; xx>=0; xx--){
                    if (this._cardArr[xx][y].getNumber() > 0){
                        if (this._cardArr[x][y].getNumber() <= 0){  //右侧为空
                            this.UDLRCard(this._cardArr[xx][y], this._cardArr[x][y], true, this._cardArr[xx][y].getNumber());
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() == this._cardArr[xx][y].getNumber()){ //左右相等
                            this.UDLRCard(this._cardArr[xx][y], this._cardArr[x][y], true, this._cardArr[x][y].getNumber() * 2);
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() + this._cardArr[xx][y].getNumber() == 20003){  //xin_nian_hao
                            this.UDLRCard(this._cardArr[xx][y], this._cardArr[x][y], true, 20003);
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() + this._cardArr[xx][y].getNumber() == 30006){  //xin_nian_hao
                            this.UDLRCard(this._cardArr[xx][y], this._cardArr[x][y], true, 30006);
                            isdo = true;
                            this.GameWinFunc();
                        }
                        break;
                    }
                }
            }
        }
        return isdo;
    },
    
    doUp : function () {
        var isdo = false;
        for (var x = 0; x < 4; x++){
            for (var y = 3; y>=0; y--){
                for (var yy = y-1; yy>=0; yy--){
                    if (this._cardArr[x][yy].getNumber() > 0){
                        if (this._cardArr[x][y].getNumber() <= 0){ //上侧为空
                            this.UDLRCard(this._cardArr[x][yy], this._cardArr[x][y], false, this._cardArr[x][yy].getNumber());
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() == this._cardArr[x][yy].getNumber()){ //上下相等
                            this.UDLRCard(this._cardArr[x][yy], this._cardArr[x][y], false, this._cardArr[x][y].getNumber() * 2);
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() + this._cardArr[x][yy].getNumber() == 20003){  //xin_nian_hao
                            this.UDLRCard(this._cardArr[x][yy], this._cardArr[x][y], false, 20003);
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() + this._cardArr[x][yy].getNumber() == 30006){  //xin_nian_hao
                            this.UDLRCard(this._cardArr[x][yy], this._cardArr[x][y], false, 30006);
                            isdo = true;
                            this.GameWinFunc();
                        }
                        break;
                    }
                }
            }
        }
        return isdo;
    },

    doDown : function () {
        var isdo = false;
        for (var x = 0; x<4; x++){
            for (var y = 0; y<4; y++){
                for (var yy = y+1; yy<4; yy++){
                    if (this._cardArr[x][yy].getNumber() > 0){
                        if (this._cardArr[x][y].getNumber() <= 0){  //下侧为空
                            this.UDLRCard(this._cardArr[x][yy], this._cardArr[x][y], false, this._cardArr[x][yy].getNumber());
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() == this._cardArr[x][yy].getNumber()){
                            this.UDLRCard(this._cardArr[x][yy], this._cardArr[x][y], false, this._cardArr[x][y].getNumber() * 2);
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() + this._cardArr[x][yy].getNumber() == 20003){  //xin_nian_hao
                            this.UDLRCard(this._cardArr[x][yy], this._cardArr[x][y], false, 20003);
                            isdo = true;
                        }
                        else if (this._cardArr[x][y].getNumber() + this._cardArr[x][yy].getNumber() == 30006){  //xin_nian_hao
                            this.UDLRCard(this._cardArr[x][yy], this._cardArr[x][y], false, 30006);
                            isdo = true;
                            this.GameWinFunc();
                        }
                        break;
                    }
                }
            }
        }
    },

    //数字变更公用方法;
    UDLRCard:function(card1,card2,isTure,num){
        card1.setNumber(0);
        card2.setNumber(num);
        this.MoveCardArr(card1,card2,isTure);
    },

    //卡牌移动动画;
    MoveCardArr:function(card1,card2,isLR){
        var s=card1.getCardPosX()-card2.getCardPosX();
        var d=card1.getCardPosY()-card2.getCardPosY();

        if(isLR){
            var sub=cc.p(-s,d);
        }else{
            var sub=cc.p(s,-d);
        }
        //移动特效;
        card1.runAction(cc.sequence(
            cc.moveBy(0.15,sub),
            cc.hide(),
            cc.moveTo(0.1,cc.p(0,0)),
            cc.show()
        ));
    },

    //卡牌移动动画;
    MoveCardArr:function(card1,card2,isLR){
        var s=card1.getCardPosX()-card2.getCardPosX();
        var d=card1.getCardPosY()-card2.getCardPosY();

        if(isLR){
            var sub=cc.p(-s,d);
        }else{
            var sub=cc.p(s,-d);
        }
        //移动特效;
        card1.runAction(cc.sequence(
            cc.moveBy(0.15,sub),
            cc.hide(),
            cc.moveTo(0.1,cc.p(0,0)),
            cc.show()
        ));
    },

    createCardSprite : function (wsize) {

        var unit = (wsize.width - 38)/4;

        this._cardArr = new Array();
        for (var i = 0; i < 4; i++){
            var column = [];
            for (var j = 0; j < 4; j++){
                //ctor : function (number, width, height, posx, posy)
                var sprite = new CardSprite(0, unit-10, unit-10, unit*i+20, unit*j + 20);
                this.addChild(sprite);
                column.push(sprite);
            }
            this._cardArr.push(column);
        }
    },

    showTipFunc : function(){
        printf("showTipFunc.");
        
        var label = new cc.LabelTTF("提示：合并屏幕中的图片", "", 50);
        label.setColor(cc.color(0, 0, 0));
        label.setPosition(Wsize.width/2, Wsize.height-330);
        this.addChild(label);
    },

    promptLayer : function () {
        printf("promptLayer.");
        
        var layer = new PromptLayer(Wsize.width, Wsize.height * 0.75);
        layer.setPositionY(70);
        this.addChild(layer, 10);
    },

    autoCreateCardNumber : function () {
        printf("autoCreatCardNumber.");

        var i = parseInt(Math.random() * 4);
        var j = parseInt(Math.random() * 4);

        if (this._cardArr[i][j].getNumber() > 0){
            this.autoCreateCardNumber();
        }
        else {
            printf("else.");
            var num = parseInt(Math.random() * 100);
            if (num>=0 && num<10){
                this._cardArr[i][j].setNumber(4);
            }
            else if (num>=10&&num<85){
                this._cardArr[i][j].setNumber(2);
            }
            else if (num>=85&&num<90){
                //创建“新”字，this._maskLayer1为是否创建完“新”字的开关;
                 if (this._isTure1){
                     this._isTure1 = false;
                     this._cardArr[i][j].setNumber(10001); //xin
                 }
                 else {
                     this.autoCreateCardNumber();
                 }
            }
            else if (num>=90&&num<95){
                //测试代码
                //this._isTure1 = false;
                if (!this._isTure1 && this._isTure2){
                    this._isTure2 = false;
                    this._cardArr[i][j].setNumber(10002);   //nian

                    var spr_xin  = new cc.Sprite(res.png_xin);
                    var spr_nian = new cc.Sprite(res.png_nian);
                    var spr_hao  = new cc.Sprite(res.png_hao);
                    var layer=new PromptLayerTwo(Wsize.width, Wsize.height * 0.75, spr_xin, spr_nian, spr_hao);
                    layer.setPositionY(70);
                    this.addChild(layer);
                }
                else {
                    this.autoCreateCardNumber();
                }
            }
            else if (num>=95&&num<100){
                if (!this._isTure1 && !this._isTure2 && this._isTure3){
                    this._isTure3 = false;
                    printf("10003")
                    this._cardArr[i][j].setNumber(10003);   //hao

                    var spr_xin  = new cc.Sprite(res.png_xin);
                    var spr_nian = new cc.Sprite(res.png_nian);
                    var spr_hao  = new cc.Sprite(res.png_hao);
                    var layer=new PromptLayerTwo(Wsize.width, Wsize.height * 0.75, spr_xin, spr_nian, spr_hao);
                    layer.setPositionY(70);
                    this.addChild(layer);
                }
                else {
                    this.autoCreateCardNumber();
                }
            }
        }
    },

    //游戏通过;
    GameWinFunc : function(){
        //系统暂停;
        setTimeout(function(){
            ls_show("恭喜收集所有产品！");
        }.bind(this),600);
    },

    doCheckGameOver:function(){
        var isOver = true;
        for (var y = 0; y < 4; y++) {
            for (var x = 0; x < 4; x++) {
                if (this._cardArr[x][y].getNumber() == 0||
                    (x>0&&(this._cardArr[x][y].getNumber() == this._cardArr[x-1][y].getNumber()))||
                    (x<3&&(this._cardArr[x][y].getNumber() == this._cardArr[x+1][y].getNumber()))||
                    (y>0&&(this._cardArr[x][y].getNumber() == this._cardArr[x][y-1].getNumber()))||
                    (y<3&&(this._cardArr[x][y].getNumber() == this._cardArr[x][y+1].getNumber()))) {
                    isOver = false;
                    break;
                }
            }
        }
        if (isOver) {
            //游戏结束，重新开始游戏
            cc.director.runScene(new GameOver());
        }
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        printf("onEnter.");
        
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

