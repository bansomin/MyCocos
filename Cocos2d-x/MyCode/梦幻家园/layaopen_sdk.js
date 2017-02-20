(function (w, undefined) {
    if(undefined == w.console) {
        var noop = function noop() {};
        var methods = [
            'assert', 'clear', 'count', 'debug', 'dir', 'dirxml', 'error',
            'exception', 'group', 'groupCollapsed', 'groupEnd', 'info', 'log',
            'markTimeline', 'profile', 'profileEnd', 'table', 'time', 'timeEnd',
            'timeStamp', 'trace', 'warn'
        ];
        var length = methods.length;
        w.console = {};
        while (length--) {
            w.console[methods[length]] = noop;
        }
    }
    var LayaPay = function () {};

    LayaPay.prototype.param = {
        orderId:null,
        amount:null,
        goodsName:null,
        goodsDesc:null,
        returnUrl:null,
        userId:null,
        notifyUrl:null,
        returnUrl:null,
        serverId:null,
    }

    LayaPay.prototype.init = function () {
        var url = 'http://paycenter.layabox.com/ping/create?';

        for (var key in this.param)
        {
            url += '&' + key + '=' + this.param[key];
        }

        var iframe ='<iframe src="'+url+'" width="100%" height="430px" frameborder="0" scrolling="yes"></iframe>';

        _LAYAOPEN_SDK.getDialog().open('LAYA支付',iframe, function() {
            _LAYAOPEN_SDK.postMessage('pay', {
                status:1
            });
        });
    }

    LayaPay.prototype.setParam = function (param) {
        if (typeof param == 'object')
        {
            for (var key in  param)
            {
                this.param[key] = param[key];
            }
        }
    }

    var dialogBox = function () {
        this.closeCallback = null;
    }
    //====================================================================================
    dialogBox.prototype.init = function() {
        var model = '<div class="modal fade bs-example-modal-sm" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">\
		  <div class="modal-dialog" role="document">\
		    <div class="modal-content">\
		      <div class="modal-header">\
		        <button type="button" id="modal-close" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>\
		        <h4 class="modal-title" id="myModalLabel"></h4>\
		      </div>\
		      <div class="modal-body" style="padding:0px;margin:0px;" id="myModalContent"></div>\
		    </div>\
		  </div>\
		</div>';
        $("body").append(model);
    }

    //打开对话框-------------------------------------------------------------------------
    dialogBox.prototype.open = function (titleText, informaton, closeCallback,isClose) {
        $('#myModalLabel').html(titleText);
        $('#myModalContent').html(informaton);
        if (isClose == 'static')
        {
            $("#modal-close").hide();
        } else {
            $("#modal-close").show();
        }

    	$(".modal").modal({
            show:'show',
            backdrop:isClose
        });
        if(closeCallback) {
            dialogBox.closeCallback = closeCallback;
        }
        $('#myModal').one('hidden.bs.modal', function (e) {
            _LAYAOPEN_SDK.getDialog().close();
        });

    }
    dialogBox.prototype.close = function (callback) {
        if(typeof callback == 'function') {
            dialogBox.closeCallback = null;
            callback();
        } else if(typeof dialogBox.closeCallback == 'function') {
            dialogBox.closeCallback();
        }
        $(".modal").modal('hide');
    }
    var _LAYAOPEN_SDK = {
        config: { //配置
            'proxy_url': w.location.protocol + '//' + w.location.host + '/laya_cross.html',  //跨域回调地址
            'top': -1,      //位于屏幕位置
            'left': -1,     //
            'ssoUrl': 'http://sso.com',
            'gameIframe': 'gameIframe',
        },
        dialog: null,
        _payIframe: null,

        _callback: {
            login: function (data) {
                console.log(data);
            },
            logout: function (data) { //退出回调

            },
            loginCheck: function (data) { //登录检测回调

            }
        },

        setConfig: function(config) {

            if(typeof config == 'object') {
                for (var key in config) {
                    this.config[key] = config[key]
                }
            }
        },

        setCallback: function(callbacks) {
            for(var key in callbacks) {
                if(typeof callbacks[key] === 'function') {
                    this._callback[key] = callbacks[key];
                }
            }
        },

        getDialog: function () {
            if (null === this.dialog) {
                this.dialog = new dialogBox();
                this.dialog.init();
            }
            return this.dialog;
        },

        loginCheck: function () {
            var url = this.config.ssoUrl+"/?callback=_LAYAOPEN_SDK._callback.loginCheck";
            // 创建script标签，设置其属性
            var script = document.createElement('script');
            script.setAttribute('src', url);
            // 把script标签加入head，此时调用开始
            document.getElementsByTagName('head')[0].appendChild(script);
        },

        login: function (_loginCallBack) {  //登录
            if ('function' == typeof _loginCallBack) {
                this._callback.login = _loginCallBack;
            } else if (!this._callback.login) {
                this._callback.login = function (data) {
                    console.log(data);
                }
            }
            this.getDialog().open('layabox登录',
                '<iframe src="'+this.config.ssoUrl+'/phoneLoginReg/?nav=off&proxy_url=' + this.config.proxy_url + '" width="100%" height="430px" frameborder="0" scrolling="yes"></iframe>',
                null,
                'static'
            );
        },

        logout: function () { //退出
            var url = this.config.ssoUrl+"/logout?callback=_LAYAOPEN_SDK._callback.logout";
            // 创建script标签，设置其属性
            var script = document.createElement('script');
            script.setAttribute('src', url);
            // 把script标签加入head，此时调用开始
            document.getElementsByTagName('head')[0].appendChild(script);
        },
        pay:function (param) {
            if(null == this._payIframe) {
                this._payIframe = new LayaPay;
            }
            this._payIframe.setParam(param);
            this._payIframe.init();
        },
        postMessage: function(type, data) {
            window.frames[this.config['gameIframe']].postMessage({
                type: type,
                data: data
            }, '*');
        },
        eventListener:function () {
            var self = this;
            window.addEventListener('message',function(e) {
                var result = e.data.data;
                if(typeof e.data.type === undefined) {
                    alert('不存在的type类型');
                    return;
                }
                switch (e.data.type) {
                    case 'login':
                        _LAYAOPEN_SDK.loginCheck();
                        self.LoginStatus();
                        break;
                    case 'loginOut':
                        _LAYAOPEN_SDK.logout();
                        self.LoginStatus();
                        break;
                    case 'pay':
                        _LAYAOPEN_SDK.pay(result);
                        break;
                    case 'payResult':
                        _LAYAOPEN_SDK.getDialog().close(function() {
                            _LAYAOPEN_SDK.postMessage('pay', {
                                status:result.status
                            });
                        });
                        break;
                    case 'payResultData':
                        console.log(result);
                        break;
                }
            });
        },

        LoginStatus:function () {
            _LAYAOPEN_SDK.setCallback({
                'login': function(data) {
                    if (data.userId) { //检测到用户信息，表示已登录
                        _LAYAOPEN_SDK.postMessage('login', data);
                        //window.close();
                        _LAYAOPEN_SDK.getDialog().close();
                    }
                },
                'logout': function(data) {
                    console.log('logout-----------');
                },
                'loginCheck': function(data) {
                    if (data.userInfo) { //检测到用户信息，表示已登录
                        _LAYAOPEN_SDK.postMessage('login', data.userInfo);
                        _LAYAOPEN_SDK.getDialog().close();
                    } else {
                        _LAYAOPEN_SDK.login();
                    }
                }
            });
        }
    }
    _LAYAOPEN_SDK.eventListener();
    w._LAYAOPEN_SDK = _LAYAOPEN_SDK;
})(window, undefined)