/**
 * Created by Bansomin on 05/11/2016.
 */

var SPRITE_TAG = 1;
var PTM_RATIO = 32;     //32像素为一个单位

var Box2dLayer = cc.Layer.extend({

    _world : null,

    ctor : function() {

        this._super();

        Wsize = cc.director.getWinSize();

        this.init();

        return true;
    },

    init : function(){

        var bg = new cc.Sprite(res.HelloWorld_png);
        bg.attr({
            x: Wsize.width / 2,
            y: Wsize.height / 2
        });
        this.addChild(bg, 0);

        var helloLabel = new cc.LabelTTF("Box2D", "Arial", 38);
        helloLabel.x = Wsize.width / 2;
        helloLabel.y = Wsize.height / 2 + 200;
        this.addChild(helloLabel, 5);

        cc.eventManager.addListener({
            event          : cc.EventListener.TOUCH_ALL_AT_ONCE,
            onTouchesEnded   : this.onTouchesEnded
        }, this);


        var b2Vec2          = Box2D.Common.Math.b2Vec2  //数据类型
            , b2Body        = Box2D.Dynamics.b2Body
            , b2World       = Box2D.Dynamics.b2World
            , b2BodyDef     = Box2D.Dynamics.b2BodyDef
            , b2FixtureDef  = Box2D.Dynamics.b2FixtureDef
            , b2PolygonShape = Box2D.Collision.Shapes.b2PolygonShape;


        //创建世界(-10)
        var b2ver2 = new b2Vec2(0, -10);
        //允许休眠，可以提高物理世界中物体的处理效率，
        // 只有在发生碰撞时才唤醒该对象
        this._world = new b2World(new b2Vec2(0, -10), true);

        //开启连续物理测试
        this._world.SetContinuousPhysics(true);

        //夹具定义对象
        var fixDef = new b2FixtureDef;
        fixDef.density      =   1.0;
        fixDef.friction     =   0.5;    //摩擦系数
        fixDef.restitution  =   0.2;    //弹性系数

        //夹具物体定义对象
        var bodyDef = new b2BodyDef;
        //静态
        bodyDef.type = b2Body.b2_staticBody;


        fixDef.shape        =   new b2PolygonShape; //多边形

        var ww = Wsize.width / PTM_RATIO;
        var hh = Wsize.height / PTM_RATIO;

        /*
        * 一参    ：   矩形盒子中心点到左边的距离
        * 二参    ：   矩形盒子中心点到顶边的距离
        *
        * */

        //设置宽度的水平线
        fixDef.shape.SetAsBox(20, 2);

        //上限
        bodyDef.position.Set(10, hh + 1.8);
        this._world.CreateBody(bodyDef).CreateFixture(fixDef);

        //下限
        bodyDef.position.Set(10, -1.8);
        this._world.CreateBody(bodyDef).CreateFixture(fixDef);

        //设置高度垂直线
        fixDef.shape.SetAsBox(2, 14);

        //左限
        bodyDef.position.Set(-1.8, 13);
        this._world.CreateBody(bodyDef).CreateFixture(fixDef);

        //右限
        bodyDef.position.Set(26.8, 13);
        this._world.CreateBody(bodyDef).CreateFixture(fixDef);

        var batch = new cc.SpriteBatchNode(res.png_blocks, 150);
        this.addChild(batch, 0, SPRITE_TAG);

        this.addSpriteFunc(cc.p(Wsize.width/2, Wsize.height/2));

        this.scheduleUpdate();
    },

    onTouchesEnded : function(touches, event){
        printf("onTouchesEnded.");

        var touch    = touches[0];
        var location = touch.getLocation();

        event.getCurrentTarget().addSpriteFunc(location);
    },


    addSpriteFunc : function(position){

        var batch = this.getChildByTag(SPRITE_TAG);

        var indexx = (Math.random() > 0.5 ? 0 : 1);
        var indeyy = (Math.random() > 0.5 ? 0 : 1);

        var sprite = new cc.Sprite(batch.texture, cc.rect(32 * indexx, 32 * indeyy, 32, 32));
        batch.addChild(sprite);

        sprite.x = position.x;
        sprite.y = position.y;

        var b2BodyDef = Box2D.Dynamics.b2BodyDef
            , b2Body = Box2D.Dynamics.b2Body
            , b2FixtureDef = Box2D.Dynamics.b2FixtureDef
            , b2PolygonShape = Box2D.Collision.Shapes.b2PolygonShape;

        var bodyDef     = new b2BodyDef();
        bodyDef.type    = b2Body.b2_dynamicBody;
        bodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
        bodyDef.userData= sprite;

        var body = this._world.CreateBody(bodyDef);

        var dynamicBox = new b2PolygonShape();
        dynamicBox.SetAsBox(0.5, 0.5);

        var fixtureDef      = new b2FixtureDef();
        fixtureDef.shape    = dynamicBox;
        fixtureDef.density  = 1.0;
        fixtureDef.friction = 0.3;

        body.CreateFixture(fixtureDef);

    },

    update : function(dt){

        printf("update.");

        var velocityIterations  =   8;
        var positionIterations  =   1;

        this._world.Step(dt, velocityIterations, positionIterations);

        for (var b = this._world.GetBodyList(); b; b= b.GetNext()){

            if (b.GetUserData() != null){
               var myActor = b.GetUserData();
                myActor.x  = b.GetPosition().x * PTM_RATIO;
                myActor.y  = b.GetPosition().y * PTM_RATIO;
                myActor.rotation = -1 * cc.radiansToDegrees(b.GetAngle());
            }
        }
    }

});


var Box2dScene = cc.Scene.extend({

    onEnter : function(){

        this._super();

        var layer = new Box2dLayer();
        this.addChild(layer);
    }
});





















