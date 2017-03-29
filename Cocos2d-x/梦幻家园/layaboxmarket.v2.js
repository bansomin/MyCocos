(function (wnd) {
    "use strict";
    wnd.loadScript = function (url, onload, onerror) {
        var scp = document.createElement("script");
        scp.onload = function () {
            onload && onload({"result": 0, "desc": "OK"});
        };
        scp.onerror = function () {
            onerror && onerror({"result": -1, "desc": "js load error"})
        };
        document.head.appendChild(scp);
        scp.src = url;
    };
    if (!wnd["conchMarket"]) {
            //loadScript("http://api.dongdong.feng.inner.layabox.com/MarketH5/LayaH5Market.js?rand="+Math.random(), function () {
            loadScript("http://plugins.dawawa.com/LayaH5Market.js?rand="+Math.random(), function () {
            wnd.LayaBoxMarket = wnd.LayaBoxMarketH5;
        }, function (param) {
            console.log(JSON.stringify(param));
        });
    }
    else {
        loadScript("http://plugins.dawawa.com/layaboxmarket.js", function () {
            //wnd.LayaBoxMarket = wnd.LayaBoxMarket;
        }, function () {
        });
    }
})(window);