/**
 * socket服务器连接地址
 **/
var gameConfig = {
	ip:'121.41.92.10', //ip地址
	port:30001,//端口
	hostname:''
};

/**
 * 统计信息类
 **/
var layaSystem = {
	uid:100,
	osSystem:'',
	browser:'',
	isWebSocket:false,
	isWeiXin:false,
	isWebGl:false,
	channelId:1
};

/**
 * localStorage
 * 缓存类
 ***/
var store = {
    lcst: window.localStorage,
    read: function (key) {
        var value = (store.lcst && store.lcst.getItem(key)) || "";
        return value;
    },
    write: function (key, value) {
        store.lcst && store.lcst.setItem(key, value);
    },
    getAll: function () {
        var data = {}, key;
        for (var i = 0; i < store.lcst.length; i++) {
            key = store.lcst.key(i);
            data[key] = store.lcst.getItem(key);
        }
        return data;
    },
    clear: function () {
        store.lcst && store.lcst.clear();
    }
};

/**
 * 主类
 **/
var index = {
	isStartGame:false,
	clearId:null,
	httpLoading:null,
	fileUrl:null,
	curTime:null,
	stageWidth:null,
	stageHeight:null,
	clearTextId:null,
	tipsIndex:0,
	mainBgWidth:1200,
	mainBgHeight:768,
	mainSize:null,
	tipsArr:[],
	imageType:1,
	pixelRatio:1,
	imageCurType:0,//当前加载图片方向类型
	theCanvas:null,
	context:null,
	imageBg:null,
	imageMainBg:null,
	imageGuide:null,
	imageGuideWidth:null,
	imageGuideHeight:null,
	isGuide:false,//默认是否显示webgl引导图片
	clearDrawId:null,
	debug:true,//调试模式 默认true开启
	debugTextField:'', //调试打印信息
	guideImageType:1,//默认引导图片类型
	isRequestComplete:false,//请求是否完成
	alertGlobalError:true,//是否捕获全局错误并弹出提示
	init:function()
	{

		var oldDocumentWrite = document.write;
	    document.write = function (node) 
	    {
	        index.insertAndExecute(node);
	    };
		
	
		if(index.webSocketSupported())
		{
			index.gameSupported();
		}else
		{
			var testNum = 0;
			var clearId = setInterval(function(){
				var type = index.webSocketSupported();
				if(type)
				{
					clearInterval(clearId);
					index.gameSupported();
				}else
				{
					if(testNum == 10)
					{
						clearInterval(clearId);
						index.statHandler();
						index.getStatDataHandler('1.11','websocket不支持');
						alert("----您当前的浏览器不支持WebSocket通讯,请尝试更换其他浏览器!----");
						return;
					}else
					{
						testNum++;
					}
				}
			},500);
		}
	},
	getStatDataHandler:function(act,desc)
	{
		var data = index.getJsName(act,desc);
		
		index.httpReqHander(data.url,index.onGetStatDataSuccess,index.onGetStatDataError,data.temp,"POST");
	},
	onGetStatDataSuccess:function(httpLoading)
	{
		console.log("----------data-----success----");
	},
	onGetStatDataError:function()
	{
		console.log("----------data-----error----");
	},
	/**
	 * 统计数据
	 **/
	statHandler:function()
	{
		layaSystem.isWebGl = index.webGLSupported();//是否支持webgl
		curTime = new Date().getTime();//当前时间
		layaSystem.osSystem = index.getOS();//手机系统系统
		layaSystem.browser = index.getBrowserInfo();//手机浏览器类型
		layaSystem.isWebSocket = index.webSocketSupported();//浏览器是否支持websocket
		layaSystem.isWeiXin = index.isFromWeiXin();//是否来自微信
	},
	/**
	 * webgl情况处理
	 **/
	gameSupported:function()
	{
		var phoneType = index.getOS();
		var type = index.webGLSupported();

		if(!type)
		{
			if(phoneType.indexOf('iP') != -1)
			{
				//苹果设备提示
				index.statHandler();
				index.getStatDataHandler('1.12','苹果设备webgl不支持');
				alert('你当前的浏览器版本不支持最新的WebGl显示,请选择其他浏览器或更换设备!');
				return;
			}else
			{
				if(index.isLocalStorageSupported())
				{
					var currentNum = store.read("WebGlnumber");
					if(!currentNum)
					{
						store.write('WebGlnumber',1);
						window.location.reload();
					}else
					{
						index.showGuideImg();
					}
				}else
				{
					index.showGuideImg();
				}
			}
		}else
		{
			index.initGame();
		}
	},
	showGuideImg:function()
	{
		var gameGuide;
		var logoBox = document.getElementById('logoBox');
		logoBox.style.display = "none";
		var waitImg = document.getElementById('waitImg');
		waitImg.style.display = "none";
		waitImg.style.webkitAnimation = 'none';
		index.statHandler();
		if(index.isFromWeiXin())
		{
			//安卓设备需要加载图片提示;
			gameGuide = document.getElementById('gameGuide1');
			gameGuide.style.background = 'url(images/anzhuo_1_1.jpg) no-repeat center center';
			gameGuide.style.display = "block";
			index.getStatDataHandler('1.13','安卓设备在微信里webgl不支持');
		}else
		{
			//非微信登录平台提示
			gameGuide = document.getElementById('gameGuide2');
			gameGuide.style.background = 'url(images/anzhuo_2_1.jpg) no-repeat center center';
			gameGuide.style.display = "block";
			index.getStatDataHandler('1.14','安卓设备在其他浏览器里webgl不支持');
		}
		
		
	},
	/**
	 * 预加载页面初始化操作
	 **/
	initGame:function()
	{
		index.statHandler();

		var debugButton = document.getElementById('debugButton');
		debugButton.onclick = function()
		{
			if(!index.debug)
			{
				return;
			}
			var type = debugText.style.display;
			if(type == 'none')
			{
				debugText.style.display = 'block';
			}else
			{
				debugText.style.display = 'none';
			}
		};

		//获取jsname信息监测判断,默认间隔2秒尝试一次
		index.isRequestComplete = false;
		var data = index.getJsName();
		var clearJsId = setInterval(function(){
			if(index.isRequestComplete)
			{
				clearInterval(clearJsId);
			}
			else{
				//index.getJsName();
				index.httpReqHander(data.url,index.onSuccessGetJSName,index.onErrorGetJSName,data.temp,"POST");
			}
		},2500);
		index.httpReqHander(data.url,index.onSuccessGetJSName,index.onErrorGetJSName,data.temp,"POST");
		//index.getJsName();
	},
	/**
	 * 发送数据获取动态创建的js文件名
	 **/
	getJsName:function (act,desc)
	{
		var uid = "";
		if(index.isLocalStorageSupported())
		{
			uid = store.read('uid');
		}else
		{
			uid = index.md5(String(curTime));//不支持window.localStorage,按时间随机一个uid
		}
		
		if(uid == "")
		{
			var randomNum = parseInt(Math.random() * 1000000000);
			uid = index.md5(String(randomNum + curTime));
			store.write('uid',uid);
		}
		var channelId;
		var href = window.location.href;
		var newHref = href.substring(href.indexOf("relatedid="));
		var newHrefII = newHref.substring(0,newHref.indexOf("&"));
		if(newHrefII == "")
		{
			channelId = newHref.substring(newHref.indexOf("=")+1,newHref.length);
		}else
		{
			channelId = newHrefII.substring(newHrefII.indexOf("=")+1,newHrefII.length);
		}
		layaSystem.channelId = channelId;
		layaSystem.uid =  uid;
		var data = {};
		data.channelId = channelId;
		data.gameId = 10037;
		data.serverId = 1;
		data.uid = layaSystem.uid;
		data.ct = curTime;
		data.act = act || 1.1;
		data.ext = {};
		data.ext.dec = desc || '预加载页面统计';
		data.ext.act = act || 1.1;
		data.ext.os = layaSystem.osSystem;
		data.ext.webgl = layaSystem.isWebGl;
		data.ext.browser = layaSystem.browser;
		data.ext.websocket = layaSystem.isWebSocket;
		data.ext.weiXin = layaSystem.isWeiXin;

		var params = {};
		var temp = "";
		params.gameinfo = encodeURIComponent(JSON.stringify(data));
		for(var key in params)
		{
			temp += key + "=" + params[key] + "&";
		}
		temp = temp.substring(0,temp.length - 1);

		var hostname = window.location.hostname;
		var url;
		if(hostname == 'mhjy.layabox.com')
		{
			//正式地址
			index.debug = false;
			url = 'http://log.lmzy.layabox.com/log/collect';
		}else
		{
			//测试或本地地址
			index.debug = true;
			url = 'http://log.lmzy.layabox.com/log/testcollect';
		}
		var hostnameTemp = window.location.href;
		if(hostnameTemp == "http://lmzy.layabox.com/mhjy/")
		{
			//测试或本地地址
			index.debug = true;
			url = 'http://lmzy-log-collect.hong.chen.inner.layabox.com/log/test2tcollect';
		}
		gameConfig.hostname = "http://" + hostname;

		var sendData = {url:url,temp:temp};
		return sendData;
		
	},
	/**
	 * 请求成功
	 **/
	onSuccessGetJSName:function(httpLoading)
	{
		var status = httpLoading.status !== undefined ? httpLoading.status : 200;
		var data;
		if(index.isRequestComplete)
			return;//之前请求完成避免重复操作
		index.isRequestComplete = true;
		index.getStatDataHandler('1.15','成功获取js文件路径');

		if (status === 200 || status === 204 || status === 0) 
		{
			data = httpLoading.response || httpLoading.responseText;
		} else
		{
			alert("[" + httpLoading.status + "]" + httpLoading.statusText + ":" + httpLoading.responseURL);
			return;
		}
		if(data == "" || data == null)
		{
			index.appendChild("----------服务端返回的js文件名为空-------");
			return;
		}else
		{
			index.appendChild('和服务端获取文件名成功,js文件路径为:' + data);
			index.fileUrl = data;
			//和后台获取js文件名给fileUrl
			index.loadingJSInfo(index.fileUrl);
		}
		httpLoading = null;
	},
	/**
	 * 请求失败
	 **/
	onErrorGetJSName:function ()
	{
		if(index.isRequestComplete)
			return;//之前请求完成避免重复操作
		index.isRequestComplete = true;
		index.appendChild('---和服务端获取文件名失败---');
	},
	/**
	 * 文本内容追加方法
	 * @param content 追加内容
	 **/
	appendChild:function(content)
	{
		var debugText = document.getElementById('debugText');
		debugText.innerText += content + '\n';
	},
	/**
	 * 移除预加载的画布,初始化游戏
	 **/
	hideScreen:function()
	{
		index.appendChild('---调用游戏加载类加载:loading.png---loadingBg.jpg---reuse.json---成功----');
		Main.initGame();
		index.isStartGame = true;
		var clearId = setInterval(function(){
			//index.appendChild('---1---游戏loading背景初始化状态:' + window.Laya.GameMain._ins.isLoadingBg);
			if(window.Laya.GameMain._ins.isLoadingBg)
			{
				//index.appendChild('------2---游戏loading背景初始化状态:' + window.Laya.GameMain._ins.isLoadingBg);
				clearInterval(clearId);
				index.appendChild('-------------预加载预加载页面,显示出游戏页面--------------');
				var waitdiv=document.getElementById('waitdiv');
				waitdiv.style.display = "none";
				waitdiv.innerHTML="";
			}
		},500);
	},
	/**
	 * 请求加载方法
	 * @param url String url 请求 
	 * @param successCallBack Function 成功回调
	 * @param errorCallBack Function 失败回调
	 * @param data Object  发送数据
	 * @param method  String 请求方式 默认是 GET
	 * @param responseType String 返回消息类型，可设置为"text"，"json"，"xml","arraybuffer" 
	 **/
	httpReqHander:function (url,successCallBack,errorCallBack,data,method,responseType)
	{
		method = method || "GET";
		data = data || null;
		index.fileUrl = url;
		try
		{
			var httpLoading = new XMLHttpRequest();
			httpLoading.open(method,url,true);
			httpLoading.responseType = responseType !== "arraybuffer" ? "text" : "arraybuffer";
			httpLoading.onload = function(){
				successCallBack && successCallBack(httpLoading);
			};
			httpLoading.onerror = function(){
				errorCallBack && errorCallBack();
			};
			httpLoading.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
			httpLoading.send(data);
		}catch(e)
		{
			alert('---------throw---error:' + e);
		}
		
	},
	/**
	 * 动态创建script标签加载游戏js文件 
	 * @param url String js文件名
	 **/
	loadingJSInfo:function (url)
	{
		index.appendChild('---开始动态加载游戏的js文件---');
		var jsScript =  document.getElementById('jsScript');
		jsScript.src = url;
		var curent = new Date().getTime();//当前时间
		jsScript.onload = function()
		{
			clearInterval(clearId);
			var last = new Date().getTime();//当前时间
			chazhi = last - curent;
			index.getStatDataHandler('1.19','js文件动态加载成功,初始化游戏,消耗时间:' + chazhi + "(ms)");
			index.appendChild('---动态加载游戏的js文件---成功---');
			index.hideScreen();
		};
		jsScript.onerror = function()
		{
			index.getStatDataHandler('1.18','js文件动态加载失败,尝试重新再次加载----');
			index.appendChild('---动态加载游戏的js文件---失败---');
			//是否考虑嵌入加载js文件识别的情况
			jsScript.src = url;
		};
		var currentTime = new Date().getTime();//当前时间
		var number = 0;
		var clearId = setInterval(function(){
			var last = new Date().getTime();//当前时间
			chazhi = last - curent;
			index.getStatDataHandler('1.16','加载js耗时:' + chazhi + "(ms)");
		},500);
	},
	/**
	 * 判断是否支持WebGl方法
	 **/
	webGLSupported:function ()
	{
		var webGLSupport = new TestWebGLSupport();
		var type = webGLSupport.checkWebGlSupport();
		return type;

		// return;
		// var canvas = document.createElement('canvas');
		// var gl;
		// try { gl = canvas.getContext("webgl"); }
		// catch (e) { gl = null; }
		// if (gl == null) {
		// 	try { gl = canvas.getContext("experimental-webgl"); }
		// 	catch (e) { gl = null; }
		// }
		// return gl != null;
	},
	/**
	 * 获取手机设备类型
	 **/
	getOS:function()
	{
		var sUserAgent = window.navigator.userAgent;
		var navigator = window.navigator;
		var isWin = (navigator.platform == "Win32") || (navigator.platform == "Windows");
		var isMac = (navigator.platform == "Mac68K") || (navigator.platform == "MacPPC") || (navigator.platform == "Macintosh") || (navigator.platform == "MacIntel");
		if (isMac) return "Mac";
		var isIpad = navigator.platform.indexOf('iPad') > -1;
		if (isIpad) return 'iPad';		
		var isIPhone = navigator.platform.indexOf('iPhone') > -1;
		if (isIPhone) return 'iPhone';
		var isIpod = navigator.platform.indexOf('iPod') > -1;
		if (isIpod) return 'iPod';
		var isUnix = (navigator.platform == "X11") && !isWin && !isMac;
		if (isUnix) return "Unix";
		var isLinux = (navigator.platform.indexOf("Linux") > -1);
		if (isLinux) return "Linux";
		if (isWin) {
			var isWin2K = sUserAgent.indexOf("Windows NT 5.0") > -1 || sUserAgent.indexOf("Windows 2000") > -1;
			if (isWin2K) return "Win2000";
			var isWinXP = sUserAgent.indexOf("Windows NT 5.1") > -1 || sUserAgent.indexOf("Windows XP") > -1;
			if (isWinXP) return "WinXP";
			var isWin2003 = sUserAgent.indexOf("Windows NT 5.2") > -1 || sUserAgent.indexOf("Windows 2003") > -1;
			if (isWin2003) return "Win2003";
			var isWinVista= sUserAgent.indexOf("Windows NT 6.0") > -1 || sUserAgent.indexOf("Windows Vista") > -1;
			if (isWinVista) return "WinVista";
			var isWin7 = sUserAgent.indexOf("Windows NT 6.1") > -1 || sUserAgent.indexOf("Windows 7") > -1;
			if (isWin7) return "Win7";
			var isWin8 = sUserAgent.indexOf("Windows 8") > -1;
			if (isWin8) return "Win8";
		}
		return "other";
	},
	/**
	 * 获取手机浏览器类型
	 **/
	getBrowserInfo:function()
	{
		if(index.getBroType() instanceof Array)
			return index.getBroType()[0];
		return "unknown";
	},
	
	/**
	 * 获取浏览器版本信息  
	 *  360     360 aphone
	 *	2345    mb2345browser
	 *	qq      mqqbrowser
	 *	sougou  sogoumse,sogoumobilebrowser
	 *	uc      ucbrowser
	 *	遨游    mxbrowser
	 *	百度    baidubrowser
	 *	猎豹    liebaofast
	 *	欧鹏    opr
	 *	微信    micromessenger
	 * @return 
	 * type.replace(/[^0-9.]/ig,"")
	 */		
	getBroType:function()
	{	
		var regStr_ie = /msie [\d.]+;/gi;
		var regStr_ff = /firefox\/[\d.]+/gi;
		var regStr_chrome = /chrome\/[\d.]+/gi;
		var regStr_saf = /safari\/[\d.]+/gi;
		var regStr_QQ = /mqqbrowser\/[\d.]+/gi;
		var regStr_Opera = /opr\/[\d.]+/gi;
		var regStr_360 = /360 aphone browser\/[\d.]+/gi;
		var regStr_2345 = /mb2345browser\/[\d.]+/gi;			
		var regStr_sougou = /sogoumobilebrowser\/[\d.]+/gi;
		var regStr_uc = /ucbrowser\/[\d.]+/gi;
		var regStr_aoyou = /mxbrowser\/[\d.]+/gi;
		var regStr_baidu = /baidubrowser\/[\d.]+/gi;
		var regStr_liebao = /liebaofast\/[\d.]+/gi;
		var regStr_wx = /micromessenger\/[\d.]+/gi;

		var agent = window.navigator.userAgent.toLowerCase() ;	
		if(agent.indexOf("micromessenger") > 0)//微信
			return agent.match(regStr_wx);		
		if(agent.indexOf("QQ") > 0 || agent.indexOf("mqqbrowser") > 0)//QQ
			return agent.match(regStr_QQ) ;			
		if(agent.indexOf("Opera") > 0 || agent.indexOf("opr") > 0)//Opera
			return agent.match(regStr_Opera);			
		if(agent.indexOf("360") > 0 || agent.indexOf("360 aphone browser") > 0)//360
		{
			if(agent.match(regStr_360) instanceof Array)
				return agent.match(regStr_360);
			var news = agent.slice(agent.indexOf("360"),agent.length-1);
			return [news.replace(/\x20\(/g,'/')];
		}
		if(agent.indexOf("mb2345browser") > 0)//2345
			return agent.match(regStr_2345);
		if(agent.indexOf("sogoumse") > 0 || agent.indexOf("sogoumobilebrowser") > 0)//sougou
			return agent.match(regStr_sougou);			
		if(agent.indexOf("ucbrowser") > 0)//uc
			return agent.match(regStr_uc);			
		if(agent.indexOf("mxbrowser") > 0)//遨游
			return agent.match(regStr_aoyou);			
		if(agent.indexOf("baidubrowser") > 0)//百度
			return agent.match(regStr_baidu);			
		if(agent.indexOf("liebaofast") > 0)//猎豹
			return agent.match(regStr_liebao);			
		if(agent.indexOf("msie") > 0)	//IE
			return agent.match(regStr_ie) ;			
		if(agent.indexOf("firefox") > 0)//firefox
			return agent.match(regStr_ff) ;
		if(agent.indexOf("chrome") > 0)	//Chrome
			return agent.match(regStr_chrome) ;			
		if(agent.indexOf("safari") > 0 && agent.indexOf("chrome") < 0)//Safari
			return agent.match(regStr_saf) ;		
		return "unknown";
	},
	/**
	 * 判断是否支持WebSocket方法
	 **/
	webSocketSupported:function()
	{
		if(window.WebSocket)
			return true;
		else
			return false;
	},
	/**
	 * 判断是否在微信里
	 **/
	isFromWeiXin:function()
	{
	    var ua = window.navigator.userAgent.toLowerCase();
	    if(ua.match(/MicroMessenger/i) == 'micromessenger')
	        return true;
	    else
	        return false;
	},
	/**设备像素比*/
	pixelRatio:function()
	{	
		return 1;
		var backingStore = index.context.backingStorePixelRatio || index.context.webkitBackingStorePixelRatio || index.context.mozBackingStorePixelRatio || index.context.msBackingStorePixelRatio || index.context.oBackingStorePixelRatio || index.context.backingStorePixelRatio || 1;
		_pixelRatio = (window.devicePixelRatio || 1) / backingStore;
		return _pixelRatio;
	},
	//判断浏览器是否支持localStorage
	isLocalStorageSupported:function()
	{
		var testKey = "test",
			storage = window.localStorage;
			try
			{
				storage.setItem(testKey,'testValue');
				storage.removeItem(testKey);
				return true;
			}catch(error)
			{
				return false;
			}
	},
	/**
	 * md5计算
	 **/
	md5:function(str) 
	{
        function rl(l, i) {
            return (l << i) | (l >>> (32 - i));
        }

        function au(lX, lY) {
            var lX4, lY4, lX8, lY8, lr;
            lX8 = (lX & 0x80000000);
            lY8 = (lY & 0x80000000);
            lX4 = (lX & 0x40000000);
            lY4 = (lY & 0x40000000);
            lr = (lX & 0x3FFFFFFF) + (lY & 0x3FFFFFFF);
            if (lX4 & lY4) {
                return (lr ^ 0x80000000 ^ lX8 ^ lY8);
            }
            if (lX4 | lY4) {
                if (lr & 0x40000000) {
                    return (lr ^ 0xC0000000 ^ lX8 ^ lY8);
                } else {
                    return (lr ^ 0x40000000 ^ lX8 ^ lY8);
                }
            } else {
                return (lr ^ lX8 ^ lY8);
            }
        }

        function f(x, y, z) {
            return (x & y) | ((~x) & z);
        }

        function g(x, y, z) {
            return (x & z) | (y & (~z));
        }

        function h(x, y, z) {
            return (x ^ y ^ z);
        }

        function i(x, y, z) {
            return (y ^ (x | (~z)));
        }

        function ff(a, b, c, d, x, s, ac) {
            a = au(a, au(au(f(b, c, d), x), ac));
            return au(rl(a, s), b);
        }

        function gg(a, b, c, d, x, s, ac) {
            a = au(a, au(au(g(b, c, d), x), ac));
            return au(rl(a, s), b);
        }

        function hh(a, b, c, d, x, s, ac) {
            a = au(a, au(au(h(b, c, d), x), ac));
            return au(rl(a, s), b);
        }

        function ii(a, b, c, d, x, s, ac) {
            a = au(a, au(au(i(b, c, d), x), ac));
            return au(rl(a, s), b);
        }

        function cta(str) {
            var wc;
            var ml = str.length;
            var tmp1 = ml + 8;
            var tmp2 = (tmp1 - (tmp1 % 64)) / 64;
            var nw = (tmp2 + 1) * 16;
            var wa = Array(nw - 1);
            var bp = 0;
            var bc = 0;
            while (bc < ml) {
                wc = (bc - (bc % 4)) / 4;
                bp = (bc % 4) * 8;
                wa[wc] = (wa[wc] | (str.charCodeAt(bc) << bp));
                bc++;
            }
            wc = (bc - (bc % 4)) / 4;
            bp = (bc % 4) * 8;
            wa[wc] = wa[wc] | (0x80 << bp);
            wa[nw - 2] = ml << 3;
            wa[nw - 1] = ml >>> 29;
            return wa;
        }

        function wth(lv) {
            var wthv = "", temp = "", lb, lc;
            for (lc = 0; lc <= 3; lc++) {
                lb = (lv >>> (lc * 8)) & 255;
                temp = "0" + lb.toString(16);
                wthv = wthv + temp.substr(temp.length - 2, 2);
            }
            return wthv;
        }

        function ue(str) {
            str = str.replace(/\r\n/g, "\n");
            var ut = "";
            for (var n = 0; n < str.length; n++) {
                var c = str.charCodeAt(n);
                if (c < 128) {
                    ut += String.fromCharCode(c);
                } else if ((c > 127) && (c < 2048)) {
                    ut += String.fromCharCode((c >> 6) | 192);
                    ut += String.fromCharCode((c & 63) | 128);
                } else {
                    ut += String.fromCharCode((c >> 12) | 224);
                    ut += String.fromCharCode(((c >> 6) & 63) | 128);
                    ut += String.fromCharCode((c & 63) | 128);
                }
            }
            return ut;
        }

        var x = [];
        var k, AA, BB, CC, DD, a, b, c, d;
        var S11 = 7, S12 = 12, S13 = 17, S14 = 22;
        var S21 = 5, S22 = 9, S23 = 14, S24 = 20;
        var S31 = 4, S32 = 11, S33 = 16, S34 = 23;
        var S41 = 6, S42 = 10, S43 = 15, S44 = 21;
        str = ue(str);
        x = cta(str);
        a = 0x67452301;
        b = 0xEFCDAB89;
        c = 0x98BADCFE;
        d = 0x10325476;
        for (k = 0; k < x.length; k += 16) {
            AA = a;
            BB = b;
            CC = c;
            DD = d;
            a = ff(a, b, c, d, x[k + 0], S11, 0xD76AA478);
            d = ff(d, a, b, c, x[k + 1], S12, 0xE8C7B756);
            c = ff(c, d, a, b, x[k + 2], S13, 0x242070DB);
            b = ff(b, c, d, a, x[k + 3], S14, 0xC1BDCEEE);
            a = ff(a, b, c, d, x[k + 4], S11, 0xF57C0FAF);
            d = ff(d, a, b, c, x[k + 5], S12, 0x4787C62A);
            c = ff(c, d, a, b, x[k + 6], S13, 0xA8304613);
            b = ff(b, c, d, a, x[k + 7], S14, 0xFD469501);
            a = ff(a, b, c, d, x[k + 8], S11, 0x698098D8);
            d = ff(d, a, b, c, x[k + 9], S12, 0x8B44F7AF);
            c = ff(c, d, a, b, x[k + 10], S13, 0xFFFF5BB1);
            b = ff(b, c, d, a, x[k + 11], S14, 0x895CD7BE);
            a = ff(a, b, c, d, x[k + 12], S11, 0x6B901122);
            d = ff(d, a, b, c, x[k + 13], S12, 0xFD987193);
            c = ff(c, d, a, b, x[k + 14], S13, 0xA679438E);
            b = ff(b, c, d, a, x[k + 15], S14, 0x49B40821);
            a = gg(a, b, c, d, x[k + 1], S21, 0xF61E2562);
            d = gg(d, a, b, c, x[k + 6], S22, 0xC040B340);
            c = gg(c, d, a, b, x[k + 11], S23, 0x265E5A51);
            b = gg(b, c, d, a, x[k + 0], S24, 0xE9B6C7AA);
            a = gg(a, b, c, d, x[k + 5], S21, 0xD62F105D);
            d = gg(d, a, b, c, x[k + 10], S22, 0x2441453);
            c = gg(c, d, a, b, x[k + 15], S23, 0xD8A1E681);
            b = gg(b, c, d, a, x[k + 4], S24, 0xE7D3FBC8);
            a = gg(a, b, c, d, x[k + 9], S21, 0x21E1CDE6);
            d = gg(d, a, b, c, x[k + 14], S22, 0xC33707D6);
            c = gg(c, d, a, b, x[k + 3], S23, 0xF4D50D87);
            b = gg(b, c, d, a, x[k + 8], S24, 0x455A14ED);
            a = gg(a, b, c, d, x[k + 13], S21, 0xA9E3E905);
            d = gg(d, a, b, c, x[k + 2], S22, 0xFCEFA3F8);
            c = gg(c, d, a, b, x[k + 7], S23, 0x676F02D9);
            b = gg(b, c, d, a, x[k + 12], S24, 0x8D2A4C8A);
            a = hh(a, b, c, d, x[k + 5], S31, 0xFFFA3942);
            d = hh(d, a, b, c, x[k + 8], S32, 0x8771F681);
            c = hh(c, d, a, b, x[k + 11], S33, 0x6D9D6122);
            b = hh(b, c, d, a, x[k + 14], S34, 0xFDE5380C);
            a = hh(a, b, c, d, x[k + 1], S31, 0xA4BEEA44);
            d = hh(d, a, b, c, x[k + 4], S32, 0x4BDECFA9);
            c = hh(c, d, a, b, x[k + 7], S33, 0xF6BB4B60);
            b = hh(b, c, d, a, x[k + 10], S34, 0xBEBFBC70);
            a = hh(a, b, c, d, x[k + 13], S31, 0x289B7EC6);
            d = hh(d, a, b, c, x[k + 0], S32, 0xEAA127FA);
            c = hh(c, d, a, b, x[k + 3], S33, 0xD4EF3085);
            b = hh(b, c, d, a, x[k + 6], S34, 0x4881D05);
            a = hh(a, b, c, d, x[k + 9], S31, 0xD9D4D039);
            d = hh(d, a, b, c, x[k + 12], S32, 0xE6DB99E5);
            c = hh(c, d, a, b, x[k + 15], S33, 0x1FA27CF8);
            b = hh(b, c, d, a, x[k + 2], S34, 0xC4AC5665);
            a = ii(a, b, c, d, x[k + 0], S41, 0xF4292244);
            d = ii(d, a, b, c, x[k + 7], S42, 0x432AFF97);
            c = ii(c, d, a, b, x[k + 14], S43, 0xAB9423A7);
            b = ii(b, c, d, a, x[k + 5], S44, 0xFC93A039);
            a = ii(a, b, c, d, x[k + 12], S41, 0x655B59C3);
            d = ii(d, a, b, c, x[k + 3], S42, 0x8F0CCC92);
            c = ii(c, d, a, b, x[k + 10], S43, 0xFFEFF47D);
            b = ii(b, c, d, a, x[k + 1], S44, 0x85845DD1);
            a = ii(a, b, c, d, x[k + 8], S41, 0x6FA87E4F);
            d = ii(d, a, b, c, x[k + 15], S42, 0xFE2CE6E0);
            c = ii(c, d, a, b, x[k + 6], S43, 0xA3014314);
            b = ii(b, c, d, a, x[k + 13], S44, 0x4E0811A1);
            a = ii(a, b, c, d, x[k + 4], S41, 0xF7537E82);
            d = ii(d, a, b, c, x[k + 11], S42, 0xBD3AF235);
            c = ii(c, d, a, b, x[k + 2], S43, 0x2AD7D2BB);
            b = ii(b, c, d, a, x[k + 9], S44, 0xEB86D391);
            a = au(a, AA);
            b = au(b, BB);
            c = au(c, CC);
            d = au(d, DD);
        }
		var ret = (wth(a) + wth(b) + wth(c) + wth(d)).toLowerCase()
		x.length=0;
		x= [];
        return ret;
    },
    insertAndExecute:function(text)
    {
    	var element = document.createElement('div');
        element.innerHTML = text;
        var scripts = [];

        var ret = element.childNodes;
        for (var i = 0; ret[i]; i++) {
            if (scripts && index.nodeName(ret[i], "script") && (!ret[i].type || ret[i].type.toLowerCase() === "text/javascript")) {
                scripts.push(ret[i].parentNode ? ret[i].parentNode.removeChild(ret[i]) : ret[i]);
            }
        }

        for (var script in scripts) 
        {
            index.evalScript(scripts[script]);
        }
    },
	nodeName:function (elem, name) 
	{
        return elem.nodeName && elem.nodeName.toUpperCase() === name.toUpperCase();
    },
    evalScript:function (elem) 
    {
        var data = ( elem.text || elem.textContent || elem.innerHTML || "" );

        var head = document.getElementsByTagName("head")[0] || document.documentElement, script = document.createElement("script");
        script.type = "text/javascript";
        script.appendChild(document.createTextNode(data));
        head.insertBefore(script, head.firstChild);
        head.removeChild(script);

        if (elem.parentNode) {
            elem.parentNode.removeChild(elem);
        }
    }
 

};
