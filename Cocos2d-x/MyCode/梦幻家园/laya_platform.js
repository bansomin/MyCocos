(function (w, undefined) {
    var LAYA_PLATFORM = {
        ssoUrls: {
            'count': 0,
            'url': "/"
        },
        checkData: function (data, err) {
            if (data.code == 0) {
                return true;
            }

            if('function' == typeof err) {
                err.call(this, data);
            } else {
                this.showError(data);
            }

            return false;
        },

        timer : null,
        iframe: null,
        isJump: false,

        showError: function(data) {
            alert(data.msg);
        },
        formSend: function(obj, befor, succ, err) {
            if('function' == typeof befor) {
                befor();
            }
            $.post(obj.attr('action'), obj.serialize(), function (data) {
                LAYA_PLATFORM.checkCallBack(data, succ, err);
            });
            return false;
        },

        checkCallBack: function(data, succ, err) {
            var self = this;
            if (this.checkData(data, err)) {
                self.isJump = false;
                if (data.url) {
                    self.ssoUrls.url = data.url;
                }
                if(data.data.ssoUrls) {
                    self.ssoUrls.count = data.data.ssoUrls.length;
                    for(var key in data.data.ssoUrls) {
                        $.getJSON(data.data.ssoUrls[key]+'?'+data.data.sname+'='+data.data.sid+'&jsoncallback=?', function(ret) {
                            if(ret.sid) {
                                self.loginJump(succ, data);
                            }
                        });
                    }
                } else {
                    self.loginJump(succ, data);
                }
                self.timer = w.setTimeout(function(){
                    self.ssoUrls.count = -1;
                    self.loginJump(succ, data);
                    //w.top.location.href = self.ssoUrls.url;
                }, 5000);
            }
        },

        loginJump: function(succ, data) {
            this.ssoUrls.count--;
            if(this.ssoUrls.count < 1) {
                if(this.timer) {
                    w.clearTimeout(this.timer);
                }
                if(this.isJump) {
                    return;
                }
                this.isJump = true;
                if(data.data && data.data.proxyUrl) {
                    if(null == this.iframe) {
                        this.iframe = document.createElement("iframe");
                        this.iframe.style.width = "0px";
                        this.iframe.style.height = "0px";
                        document.body.appendChild(this.iframe);
                    }
                    this.iframe.src = data.data.proxyUrl+'#'+encodeURIComponent(JSON.stringify(data.data.userInfo));
                    return;
                }
                if('function' == typeof succ) {
                    succ.call(this, data);
                } else {
                    w.top.location.href = data.url;
                }
            }
        }
    }
    w.LAYA_PLATFORM = LAYA_PLATFORM;
})(window, undefined);