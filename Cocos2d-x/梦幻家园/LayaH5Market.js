(function (wnd) {
    "use strict";
    var TALKING_DATA = "http://sdk.talkingdata.com/websdk/js/sdk_release.js?v=1.02";
    wnd.LayaStruct = (function () {
        function LayaStruct() {
        }

        LayaStruct.getUserStruct = function () {
            return {
                SP_UID: "",
                SP: "",
                NICKNAME: "",
                AVTOR_URL: "",
                DEV_OS: "",
                DEV_OS_VER: "",
                DEV_IMEI: "",
                DEV_IMSI: "",
                DEV_MAC: "",
                SP_TOKEN: "",
                IP: "",
                ACCESS_TOKEN: "",
                GAME_ID: "",
                IS_VIP: "",
                CITY: "",
                SEX: "",
                PROVINCE: "",
                COUNTRY: "",
                HEADIMG: "",
                DEV_MOBILE: "",
                EMAIL: "",
                EQUIPMENT_NUM: "",
                SP_NAME: ""
            }
        };
        LayaStruct.getLoginStruct = function () {
            return {
                spuid: "",
                sptoken: "",
                userId: "",
                typeId: "",
                sp: "",
                nickName: "",
                email: "",
                equipmentNum: "",
                mobile: "",
                headimg: "",
                country: "",
                province: "",
                city: "",
                language: "",
                isvip: ""
            }
        };
        LayaStruct.spLoginInfo = function () {
            return {
                "result": "",
                "desc": "",
                "nickName": "",
                "avatarUrl": "",
                "sessionKey": "",
                "spuid": "",
                "sex": ""
            }
        };
        return LayaStruct;
    })();
    wnd.LayaBoxMarketH5 = (function () {
        function LayaBoxMarketH5() {
            this.basicInfo = {};
            this.queryParams = {};
            this.userInfo = {};
            this.gameInfo = {};
            this.logonKey = {};

            this.loginInput = "";
            this.spSdk = null;
            this.loginType = -1;
            this.loginResult = null;
        }

        LayaBoxMarketH5.instance = null;

        LayaBoxMarketH5.getInstance = function () {
            if (LayaBoxMarketH5.instance == null) {
                wnd.LBMH5 = LayaBoxMarketH5.instance = new LayaBoxMarketH5();
                if (wnd.hasOwnProperty("openId") && wnd.hasOwnProperty("openKey")) {
                    myInit();
                }
                else
                    LBMH5.loginResult = {result: -5, desc: "openId or openKey not exist"};
            }
            return LayaBoxMarketH5.instance;
        };

        var __proto = LayaBoxMarketH5.prototype;
        __proto.login = function (param, callback) {
            if(param.indexOf("authorizeType")>0)
            {
                param = JSON.parse(param).authorizeType;
            }
            LBMH5.loginInput = param;
            if (!param) {
                var time = setInterval(function (target) {
                    if ((target.loginResult ) && window["TDGA"]) {
                        clearInterval(time);
                        callback && callback(JSON.stringify(target.loginResult))
                    }
                }, 100, LBMH5);
            }
            else {
                innerLogin(param, function (data) {
                    callback && callback(JSON.stringify(data))
                });
            }
        };
        __proto.logout = function (param, callback) {
            if (!LBMH5.spSdk.logout)
            {
                callback && callback(JSON.stringify({"result":-2,"desc":"no function"}));
                return;
            }
            LBMH5.loginResult = {result: 1000,data:{"loginType":parseInt(LBMH5.gameInfo.loginType)},desc: ""};
            LBMH5.spSdk.logout(param, callback)
        };
        __proto.recharge = function (param, callback) {
            if (LBMH5.loginType == 0) {
                callback && callback(JSON.stringify({"result": -1000, "desc": "pay not support"}));
                return;
            }
            if (typeof param == "string") {
                try {
                    param = JSON.parse(param);
                }
                catch (e) {
                    callback && callback(JSON.stringify({"result": -1, "desc": "json parse error"}));
                    return
                }
            }
            if (!param.params)
                param.params = param.order_id;

            var url = "http://paycenter.layabox.com/?a=Pay&m=Payment&ac=submit" +
                "&sp=" + LBMH5.gameInfo["sp"] +
                "&appId=" + LBMH5.gameInfo["appId"] +
                "&openKey=" + LBMH5.gameInfo["openKey"] +
                "&suserId=" + LBMH5.userInfo["spuid"] +
                "&stoken=" + LBMH5.userInfo["sessionKey"] +
                "&lang=cn&amount=" + param.amount +
                "&payinfo=" + encodeURIComponent(param.goods_name) +
                "&params=" + param.params +
                "&token=" + LBMH5.basicInfo["access_token"] +
                "&currencyCode=CNY&goodsDescription=" + encodeURIComponent(param.goods_desc) +
                "&gameId=" + LBMH5.gameInfo["gameId"] +
                "&serverId=" + param.serverId +
                "&userId=" + LBMH5.userInfo["unionUserId"];

            console.log(url);
            LayaCommon.getJson(url, function (param1) {
                param1.data.goodsName = param.goods_name;
                param1.data.params = param.params;
                var payLogInfo = {
                    amount: param1.data.amount,
                    oid: param1.data.orderId,
                    pc: "",
                    status: 4
                };
                if (window.LogCat != null)window.LogCat.addParam(payLogInfo);
                if (window.LogCat != null)window.LogCat.logPay(payLogInfo);
                var payLogTDGA = {
                    orderId: param1.data.orderId,
                    iapId: LBMH5.gameInfo["sp"],
                    currencyAmount: param1.data.amount,
                    currencyType: "fen",
                    virtualCurrencyAmount: parseInt(param1.data.amount) / 10,
                    paymentType: "alipay"
                };
                if (window["TDGA"])
                    window.TDGA.onChargeRequest(payLogTDGA);

                LBMH5.spSdk.pay(param1, function (param2) {
                    callback && callback(JSON.stringify(param2));
                });
            });
        };
        __proto.enterShareAndFeed = function (param, callback) {
            if (LBMH5.loginType == 0) {
                callback && callback(JSON.stringify({"result": -1, "desc": "not support share"}));
                return;
            }
            if (typeof param == "string") {//解析json
                try {
                    param = JSON.parse(param)
                }
                catch (e) {
                    callback && callback(JSON.stringify({"result": -2, "desc": "json parse error"}));
                    return;
                }
            }
            //title link desc imgsrc imgtitle custxt
            if (!LBMH5.spSdk.share)
            {
                callback && callback(JSON.stringify({"result":-2,"desc":"not support share"}));
                return;
            }
            if (!param.imgUrl && param.imgsrc)
                param.imgUrl = param.imgsrc;
            if (!param.content && param.desc)
                param.content = param.desc;
            param.link = LBMH5.gameInfo["spGameUrl"] || param.link;
            LBMH5.spSdk.share && LBMH5.spSdk.share(param, callback);
        };
        __proto.init = function(win,param, callback){
              if(param)
              {
                  param = JSON.parse(param);
                  if(param.openId && param.openKey)
                  {
                      wnd.openId = param.openId;
                      wnd.openKey = param.openKey;
                  }
                  callback&&callback(JSON.stringify({"result":0}));
              }
        }
        __proto.getGameFriends = function (param, callback) {
            if (!LBMH5.spSdk.getGameFriends)
            {
                callback && callback(JSON.stringify({"result":-2,"desc":"no function"}));
                return;
            }
            LBMH5.spSdk.getGameFriends(param, callback);
        };
        __proto.openTopicCircle = function (param, callback) {
            if (!LBMH5.spSdk.openTopicCircle)
            {
                callback && callback(JSON.stringify({"result":-2,"desc":"no function"}));
                return;
            }
            LBMH5.spSdk.openTopicCircle(param, callback);
        };
        __proto.preloadResource = function (param, callback) {
            LBMH5.spSdk.preloadResource(param, callback);
        };
        __proto.sendToDesktop = function (param, callback) {
            if (!LBMH5.spSdk.sendToDesktop)
            {
                callback && callback(JSON.stringify({"result":-2,"desc":"no function"}));
                return;
            }
            LBMH5.spSdk.sendToDesktop(param, callback);
        };

        __proto.canSendToDesktop = function (param, callback) {
            return LBMH5.spSdk && LBMH5.spSdk.sendToDesktop;
        };
        __proto.canShareAndFeed = function () {
            return LBMH5.spSdk && LBMH5.spSdk.share;
        };
        __proto.canLogout = function () {
            return LBMH5.spSdk && LBMH5.spSdk.logout;
        };
        __proto.customize = function (name, array) {
            LBMH5.spSdk && LBMH5.spSdk[name] && LBMH5.spSdk[name].apply(array)
        }
        __proto.canOpenTopicCircle = function () {
            return LBMH5.spSdk && LBMH5.spSdk.openTopicCircle;
        };
        __proto.getIsLogined = function (localInfo) {
            if (localInfo != null) try {
                var data = JSON.parse(localInfo);
                return !!(data.x5_tokenid);
            } catch (e) {
                return false;
            }
            return false;
        };
        function myInit() {
            console.log("game start:" + location.href);
            if (location.search != "") {//获取游戏启动地址的参数
                var paramInvalid = true;
                var queryParameters = location.search.substring(1).split("&");
                for (var i = 0; i < queryParameters.length; i++) {
                    if (queryParameters[i].toLowerCase().indexOf("relatedid=") == 0) {
                        paramInvalid = false;
                        LBMH5.basicInfo["relatedId"] = queryParameters[i].replace(/relatedId=/i, "");
                    }
                    else {
                        var pos = queryParameters[i].indexOf("=");
                        if (pos == -1)
                            LBMH5.queryParams[queryParameters[i]] = "";
                        else
                            LBMH5.queryParams[queryParameters[i].substring(0, pos)] = queryParameters[i].substring(pos + 1);
                    }
                }
                if (paramInvalid) {
                    LBMH5.loginResult = {result: -2, desc: "relatedid参数丢失"};
                    return;
                }
            } else {
                LBMH5.loginResult = {result: -2, desc: "relatedid参数丢失"};
                return;
            }

            wnd.appDisplayName = "";
            wnd.sequenceNumber = "75A34FEB22C7A761A9AE798D030DABB4";
            wnd.DTGARequestUrl = "http://tdwv1.talkingdata.com/g/h5/v1/receive";
            if (!wnd["sessionStorage"])
                wnd["sessionStorage"] = wnd["localStorage"];

            LayaCommon.loadScript(TALKING_DATA, function () {
            }, function () {
            });

            getAccessToken(function (param) {
                if (param.result == 0) {
                    getGInfoByRelId(function (param) {
                        if (param.result == 0) {
                            getSPLogonKey(function (param) {
                                if (param.result == 0) {
                                    var spName = LBMH5.gameInfo["spFname"] && LBMH5.gameInfo["spFname"].toLowerCase();
                                    if (!spName || spName == "") {
                                        LBMH5.loginResult = {result: -6, desc: "sp not configure"};
                                        return;
                                    }
                                    var loadSPJS = function (names) {
                                        var url = "http://plugins.dawawa.com/sp/" + names + ".js?rand=" + Math.random().toString();
                                        //var url = "http://api.dongdong.feng.inner.layabox.com/MarketH5/sp/" + names + ".js?rand=" + Math.random().toString();
                                        //var url = "http://10.10.20.206/sp/" + names + ".js?rand=" + Math.random().toString();
                                        LayaCommon.loadScript(url, function () {
                                            LBMH5.spSdk = new SPSdk();
                                            LBMH5.gameInfo["logonKeyInfo"] = LBMH5.logonKey;
                                            LBMH5.gameInfo["access_token"] = LBMH5.basicInfo["access_token"];
                                            LBMH5.gameInfo["spId"] =  LBMH5.gameInfo["sp"];
                                            LBMH5.spSdk.init(LBMH5.gameInfo, function (param) {
                                                if (param.result == 0) {
                                                    innerLogin();
                                                }
                                                else {
                                                    LBMH5.loginResult = {
                                                        result: -105,
                                                        desc: "sp init failed[" + param.result + "]"
                                                    };
                                                }
                                            });
                                        }, function () {
                                            //LBMH5.loginResult = {result: -100,desc: "js download error[-7]" };
                                            loadSPJS("layabox");
                                        });
                                    };
                                    loadSPJS(spName);
                                }
                                else {
                                    LBMH5.loginResult = param;
                                }
                            });
                        }
                        else {
                            LBMH5.loginResult = param;
                        }
                    });
                }
                else {
                    LBMH5.loginResult = param;
                }
            });
        }

        function innerLogin(param, callback) {
            if (LBMH5.loginType == 0) {
                var data = {};
                data.data = {};
                data.result = -100;
                data.desc = "error";
                data.data.loginType = 0;
                data.data.sp = "";
                data.data.gameId = "";
                LBMH5.loginResult = data;
                return;
            }
            LBMH5.logonKey["authorizeType"] = LBMH5.loginInput;
            LBMH5.spSdk.login(LBMH5.logonKey, function (param) {
                if (param.result == 0) {
                    LBMH5.userInfo = param;
                    ucenterLogin(function (param) {
                        callback && callback(param);
                    });
                }
                else if (param.result == -100) {
                    LBMH5.loginResult = param;
                    callback && callback(param);
                } else if (param.result == 1000) {
                    param.loginType =  parseInt(LBMH5.gameInfo.loginType);
                    param.spId =  LBMH5.gameInfo.spId;
                    LBMH5.loginResult = param;
                    callback && callback(param);
                }
                else {
                    callback && callback({"result": param.result, "desc": param.desc});
                }
            });
        }

        function ucenterLogin(callback) {
            var user = LayaStruct.getUserStruct();
            user.SP_UID = LBMH5.userInfo["spuid"];
            user.AVTOR_URL = LBMH5.userInfo["avatarUrl"];
            user.SP = LBMH5.gameInfo["sp"];
            user.NICKNAME = LBMH5.userInfo["nickName"];
            user.SP_TOKEN = LBMH5.userInfo["sessionKey"];
            user.ACCESS_TOKEN = LBMH5.basicInfo["access_token"];
            user.GAME_ID = LBMH5.gameInfo["gameId"];
            user.HEADIMG = LBMH5.userInfo["avatarUrl"];
            user.SP_NAME = LBMH5.gameInfo["spFname"];
            var url = "http://ucenter.layabox.com/api/reglogin" +
                "?spuid=" + user.SP_UID +
                "&sp=" + user.SP +
                "&nickname=" + encodeURIComponent(user.NICKNAME) +
                "&photo=" + encodeURIComponent(user.AVTOR_URL) +
                "&os=" + user.DEV_OS +
                "&osver=" + user.DEV_OS_VER +
                "&imei=" + user.DEV_IMEI +
                "&imsi=" + user.DEV_IMSI +
                "&mac=" + user.DEV_MAC +
                "&sptoken=" + user.SP_TOKEN +
                "&ip=" + user.IP +
                "&typeId=2&access_token=" + user.ACCESS_TOKEN +
                "&gameId=" + user.GAME_ID +
                "&isvip=" + user.IS_VIP +
                "&city=" + user.CITY +
                "&sex=" + user.SEX +
                "&language=cn&province=" + user.PROVINCE +
                "&country=" + user.COUNTRY +
                "&headimg=" + encodeURIComponent(user.HEADIMG) +
                "&mobile=" + user.DEV_MOBILE +
                "&email=" + user.EMAIL +
                "&equipmentNum=" + user.EQUIPMENT_NUM +
                "&SpFname=" + user.SP_NAME;

            LayaCommon.getJson(url, function (param) {
                param.data.spFname = LBMH5.gameInfo["spFname"];
                LBMH5.userInfo["unionUserId"] = param.data.unionUserId = param.data.userId;
                param.data.accessToken = LBMH5.basicInfo["access_token"];
                var loginLogInfo = {
                    gid: LBMH5.gameInfo["gameId"],
                    cid: param.data.sp,
                    uid: param.data.spuid,
                    gsid: "",
                    act: ""
                };
                if (window.LogCat != null)window.LogCat.addParam(loginLogInfo);
                if (window.LogCat != null)window.LogCat.log(loginLogInfo);


                var time = setInterval(function (target) {
                    if (window["TDGA"]) {
                        clearInterval(time);

                        if (target.userInfo["type"])
                            param.type = target.userInfo["type"];

                        param.data.avatarUrl = param.data.headimg;
                        param.data.nickName = param.data.nickname;
                        param.loginType = parseInt(target.gameInfo.loginType);
                        param.spId = target.gameInfo.sp;

                        param.result = param.ret;
                        param.desc = param.msg;
                        delete  param.data.nickname;
                        delete  param.data.headimg;
                        delete  param.ret;
                        delete  param.msg;

                        var tdagAccountInfo = {
                            accountId: param.data.spuid,
                            level: param.data.sp,
                            gameServer: param.data.sp + "--" + LBMH5.gameInfo["gameId"],
                            accountType: param.data.sp,
                            age: "",
                            accountName: param.data.nickName,
                            gender: ""
                        };
                        window.TDGA.Account(tdagAccountInfo);

                        console.log(param);
                        target.loginResult = param;
                        //callback && callback(param);
                        callback && callback(target.loginResult)
                    }
                }, 100, LBMH5);
            });
        }

        function getSPLogonKey(callback) {
            var url = "http://ucenter.layabox.com/api/getLogonKey?sp=" + LBMH5.gameInfo["sp"] + "&openKey=" + LBMH5.gameInfo["openKey"] + "&access_token=" + LBMH5.basicInfo["access_token"];
            LayaCommon.getJson(url, function (param) {
                if (param.ret == 0) {
                    LBMH5.logonKey = param;
                    callback && callback({"result": 0});
                }
                else if (param.ret == 112)
                    callback && callback({"result": -104, "desc": "token error[-4]"});
                else
                    callback && callback({"result": param.ret, "desc": param.msg});
            }, function () {
                callback && callback({"result": -104, "desc": "get spKey error[" + param.result + "]"});
            });
        }

        function getGInfoByRelId(callback) {
            var url = "http://ucenter.layabox.com/api/getRelatedById?access_token=" + LBMH5.basicInfo["access_token"] + "&relatedId=" + LBMH5.basicInfo["relatedId"];
            LayaCommon.getJson(url, function (param) {
                if (param.ret == 0) {
                    LBMH5.gameInfo = param.data;
                    LBMH5.loginType = parseInt(LBMH5.gameInfo.loginType);
                    LBMH5.gameInfo["queryParams"] = LBMH5.queryParams;
                    callback && callback({"result": 0});
                }
                else if (param.ret == 112)
                    callback && callback({"result": -103, "desc": "token error[-4]"});
                else
                    callback && callback({"result": -9999, "desc": "unknown error[" + param.ret + "]"});
            }, function () {
                callback && callback({"result": -103, "desc": "get related error[" + param.result + "]"});
            });
        }

        function getAccessToken(callback) {
            var url = "http://ucenter.layabox.com/oauth2/authorize?appid=" + window["openId"] + "&appkey=" + window["openKey"];
            LayaCommon.getJson(url, function (param) {
                if (param.ret == 0) {
                    LBMH5.basicInfo["access_token"] = param.data.access_token;
                    LBMH5.basicInfo["overTime"] = param.data.overTime;
                    LBMH5.basicInfo["times"] = Math.floor(new Date().getTime() / 1000);

                    callback && callback({"result": 0});
                }
                else if (param.ret == 111) {
                    callback && callback({"result": -102, "desc": "appid or appkey error[-3]"});
                }
                else {
                    callback && callback({"result": -9999, "desc": "unknown error[" + param.ret + "]"});
                }
            }, function () {
                callback && callback({"result": -102, "desc": "get token error[" + param.result + "]"});
            });
        }

        LayaBoxMarketH5.instance = null;

        return LayaBoxMarketH5;
    })();
    wnd.LayaStorageH5 = (function () {
        function LayaStorageH5(storageName) {
            if (window.localStorage)
                this.store = window.localStorage;
            else
                this.store = {
                    //内存storage, 写入的localStorage临时存放在内存里，
                    //程序关闭后，数据消失，防止不支持localStorage的浏览器报错
                    "keys": [],
                    "values": [],
                    "setItem": function (key, value) {
                        var index = this.keys.indexOf(key);
                        if (index > -1)
                            this.values[index] = value;
                        else {
                            this.values.push(value);
                            this.keys.push(key);
                        }
                    },
                    "getItem": function (key) {
                        var index = this.keys.indexOf(key);
                        if (index > -1)
                            return this.values[index];
                        return null;
                    },
                    "removeItem": function (key) {
                        var index = this.keys.indexOf(key);
                        if (index > -1)
                            return this.values.splice(index, 1)[0];
                        return null;
                    },
                    "clear": function () {
                        this.values.length = 0;
                        this.keys.length = 0;
                    },
                    "key": function (index) {
                        return index < this.keys.length ? this.keys[index] : null;
                    },
                    "length": function () {
                        return this.keys.length;
                    }
                };
            this.storageName = storageName;
        }

        var __proto = LayaStorageH5.prototype;
        __proto.getLocalStore = function (key) {
            var m_this = this;
            var storage = m_this.store.getItem(m_this.storageName) || '{}';
            var store = JSON.parse(storage);
            return store.hasOwnProperty(key) ? store[key] : null;
        };
        __proto.removeLocalStore = function (key) {
            var m_this = this;
            var storage = m_this.store.getItem(m_this.storageName) || '{}';
            var store = JSON.parse(storage);
            store.hasOwnProperty(key) && delete store[key];
            m_this.store.setItem(m_this.storageName, JSON.stringify(store));
        };
        __proto.clearLocalStore = function () {
            var m_this = this;
            m_this.store.setItem(m_this.storageName, '{}');
        };
        __proto.setLocalStore = function (key, value) {
            var m_this = this;
            var storage = m_this.store.getItem(m_this.storageName) || '{}';
            var store = JSON.parse(storage);
            store[key] = value;
            m_this.store.setItem(m_this.storageName, JSON.stringify(store));
        };

        return LayaStorageH5;
    })();
    wnd.LayaCommon = (function () {
        function LayaCommon() {
        }

        LayaCommon.closeWnd = function (frameId) {
            var frame = document.getElementById(frameId);
            frame && document.body.removeChild(frame);
        };
        LayaCommon.openUrl = function (frameId, popupUrl, css) {
            var iframe = document.createElement("iframe");
            iframe.frameBorder = "0";
            iframe.scrolling = "auto";
            iframe.setAttribute("id", frameId);
            if (css) {
                var content = css;
                var style = document.createElement("style");
                style.innerHTML = content;
                style.setAttribute("id", frameId + "Style");
                document.head.appendChild(style);
            }
            else {
                iframe.style.position = "relative";
                iframe.style.left = "0px";
                iframe.style.top = "0px";
                iframe.style.height = "100%";
                iframe.style.width = "100%";
                iframe.style.zIndex = 9998;
                iframe.style.backgroundColor = "#ffffff";
            }
            iframe.src = popupUrl;
            document.body.appendChild(iframe);
        };
        LayaCommon.checkWeiXin = function () {
            var ua = window.navigator.userAgent.toLowerCase();
            console.log(ua);
            return ua.match(/MicroMessenger/i) == "micromessenger";
        };
        LayaCommon.checkIOS = function () {
            var ua = window.navigator.userAgent.toLowerCase(), app = window.navigator.appVersion;
            var isAndroid = ua.indexOf('Android') > -1;
            var isIOS = !!ua.match(/\(i[^;]+;( U;)? CPU.+Mac OS X/);
            return !isAndroid && isIOS;
        };
        LayaCommon.getParameterByName = function (url, name) {
            var reg = new RegExp('[?&]' + name + '=([^&#]*)', 'i');
            var str = reg.exec(url);
            return str ? str[1] : null;
        };
        LayaCommon.loadScript = function (url, onload, onerror) {
            var scp = document.createElement("script");
            scp.onload = function () {
                onload && onload({"result": 0});
            };
            scp.onerror = function () {
                onerror && onerror({"result": -100, "desc": "脚本下载失败"})
            };
            document.head.appendChild(scp);
            scp.src = url;
        };
        LayaCommon.getUniqueID = function (splitChar) {
            var uniqueID = "";
            for (var i = 1; i <= 32; i++) {
                uniqueID += Math.floor(Math.random() * 16.0).toString(16);
                if ((i == 8) || (i == 12) || (i == 16) || (i == 20))
                    uniqueID += (splitChar ? splitChar : "");
            }
            return uniqueID;
        };
        LayaCommon.createCallback = function (callback, callbackName) {
            if (!callbackName)
                callbackName = "callback" + LayaCommon.getUniqueID("_");
            window[callbackName] = (function (name) {
                function CallbackHandler(param) {
                    if (window[CallbackHandler.funcName]) {
                        window[CallbackHandler.funcName] = null;
                        delete window[CallbackHandler.funcName];
                    }
                    if (document && document.head) {
                        var scp = document.getElementById(CallbackHandler.funcName)
                        scp && document.head.removeChild(scp);
                    }
                    callback && callback(param);
                }

                CallbackHandler.funcName = name;
                return CallbackHandler;
            })(callbackName);
            return callbackName;
        };
        LayaCommon.getJson = function (url, callback, onError) {
            var callbackName = LayaCommon.createCallback(function (param) {
                callback && callback(param);
            });
            var scp = document.createElement("script");
            document.head.appendChild(scp);
            scp.id = callbackName;
            scp.onerror = function () {
                onError && onError({"result": -101, "desc": "json download error"})
            };
            scp.src = (url.indexOf("?") > -1) ? (url + "&callback=" + callbackName) : (url + "?callback=" + callbackName);
        };
        LayaCommon.getPostJson = function (targetUrl, params, method, accessToken, callback) {
            var url = "http://ucenter.layabox.com/HRProxy/http?url=" + targetUrl + "&params=" + params + "&ac=" + method + "&access_token=" + accessToken;
            LayaCommon.getJson(url, function (param) {
                callback && callback(param);
            }, function (param) {
                callback && callback(param);
            });
        };
        return LayaCommon;

    })();

    (function () {
        var hasls = !!window.localStorage;
        var EVENTS_KEY = 'layaboxlog';
        var PAYMENT_KEY = 'layaboxpaylog';
        var isAgentTeardown = false;

        function teardown() {
            isAgentTeardown = true;
        }

        function isTeardown() {
            return isAgentTeardown;
        }

        var supports = {
            get localStorage() {
                return hasls;
            }
        };

        var LS = supports.localStorage ? window.localStorage : null;

        var dataStore = {
            removeBykey: function (key) {
                LS.removeItem(key);
            },
            updateByKey: function (key, value) {
                key = wrapKey(key);
                var list = this.getdataByKey(key);
                if (Array.isArray(value)) {
                    value.forEach(function (item) {
                        return list.push(item);
                    });
                } else {
                    list.push(value);
                }
                // 这里不做条数判断，取出来的时候截取
                LS.setItem(wrapKey(key), JSON.stringify(list));
            },
            getdataByKey: function (key) {
                key = wrapKey(key);
                try {
                    var items = JSON.parse(LS.getItem(key));
                    return Array.isArray(items) ? items : [];
                }
                catch (e) {
                    LS.removeItem(key);
                    return [];
                }
            }
        };

        function loop() {
            reportLogs();
        }

        function reportLogs() {
            if (isTeardown())
                return;
        }


        function wrapKey(key) {
            return key;
        }

        window.LogServer = (function () {
            function LogServer() {
                var di;
                var _v;
                if (window.layabox && window.layabox.getDeviceInfo) di = window.layabox.getDeviceInfo(); //conchConfig.getWifiMac();//设备信息
                else if (!window.conchConfig) {
                    di = '{mac:"undefined"}';
                } else {
                    di = di = '{mac:"' + conchConfig.getWifiMac() + '"}';
                }
                this.lsServer = "http://log.dongdong.feng.inner.layabox.com/log/loginLog";
                this.psServer = "http://log.dongdong.feng.inner.layabox.com/log/payLog";
                if (!window.conchConfig) {
                    _v = "undefined";
                } else {
                    _v = window.conchConfig.getRuntimeVersion();
                }
                this._urldata = {
                    uuid: di.mac,
                    ext: encodeURIComponent(JSON.stringify(di)),
                    v: _v
                }
            }

            var __proto__ = LogServer.prototype;
            __proto__.addParam = function (data) {
                for (var key in data) {
                    if (data.hasOwnProperty(key))
                        this._urldata[key] = data[key];
                }
            };
            __proto__.log = function (data) {
                this.logByKey(data, EVENTS_KEY);
            };
            __proto__.logByKey = function (data, key) {
                data["ct"] = Date.now();
                for (var d in this._urldata) {
                    data[d] = this._urldata[d];
                }
                var temp = dataStore.getdataByKey(key);
                dataStore.removeBykey(key);
                temp.push(data);
                var tempUrl = (key == EVENTS_KEY ? this.lsServer : this.psServer);
                this._sendlog(tempUrl, temp, function (d) {
                    dataStore.updateByKey(key, d);
                });
            };
            __proto__.logPay = function (data) {
                this.logByKey(data, PAYMENT_KEY);
            };
            __proto__._sendlog = function (url, data, error) {
                var xhr = new XMLHttpRequest();
                xhr.onload = function (e) {
                };
                xhr.onerror = function (e) {
                };
                xhr.open("POST", url, true);
                xhr.send("layainfo=" + encodeURIComponent(JSON.stringify(data)));
            };
            __proto__.getQueryByName = function (name) {
                var reg = new RegExp("(^|&)" + name + "=([^&]*)(&|$)");
                var r = window.location.search.substr(1).match(reg);
                if (r != null) return decodeURIComponent(r[2]);
                return "";
            };
            return LogServer;
        })();
        window.LogCat = new LogServer();
    })();

    LayaBoxMarketH5.getInstance();
})(window);
