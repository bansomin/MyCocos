/**
 * Created by Administrator on 2016/3/31.
 */
if(self == top) {
    location.href = 'http://game.layabox.com/265';
}
var SPSdk = (function () {

    function SPSdk() {
        this.userId = "";
    }

    var __proto = SPSdk.prototype;
    __proto.callbacks = {
        'login': null,
        'pay': null
    };
    __proto.login = function (param, callback, shareHandler) {
        console.log("微信公众号登录：" + JSON.stringify(param));
        var m_this = this;
        m_this.callbacks['login'] = callback;
        window.parent.postMessage({
            type: 'login'
        }, '*');
    }
    __proto.pay = function (param, callback) {
        console.log("微信公众号支付：" + JSON.stringify(param));
        var m_this = this;
        window.parent.postMessage({
            type: 'pay',
            data: {
                orderId:param.data.orderId,
                amount:param.data.amount,
                goodsName:param.data.goodsName,
                goodsDesc:param.data.goodsName,
                userId:m_this.userId,
                notifyUrl:'',
                serverId:'1',
                param:param.data.orderId
            }
        }, '*');
        m_this.callbacks['pay'] = callback;
    }
    __proto.init = function (param, callback) {
        console.log("微信公众号初始化：" + JSON.stringify(param));
        var m_this = this;
        m_this.access_token = param.access_token;
        m_this.spId = param.spId;
        m_this.appId = param.appId;
        m_this.spFname = param.spFname;
        m_this.openKey = param.openKey;
        m_this.queryParams = param.queryParams;
        window.addEventListener('message',function(e) {
            var data = e.data;
            if(typeof data.type === undefined) {
                alert('不存在的type类型');
                return;
            }
            switch (e.data.type) {
                case 'login':
                    m_this.userId =  data.data.userId;
                    m_this.callbacks['login'] && m_this.callbacks['login']({"result":0,"spuid": data.data.userId,"nickname": data.data.username});
                    break;
                case 'pay':
                    m_this.callbacks['pay'] && m_this.callbacks['pay']({result:data.data.status,desc:""});
                    break;
            }
        }, false);
        callback && callback({"result": 0, "desc": "ok"});
    }
    return SPSdk;
})();