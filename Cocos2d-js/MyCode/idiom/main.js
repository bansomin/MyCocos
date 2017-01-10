/**
 * A brief explanation for "project.json":
 * Here is the content of project.json file, this is the global configuration for your game, you can modify it to customize some behavior.
 * The detail of each field is under it.
 {
    "project_type": "javascript",
    // "project_type" indicate the program language of your project, you can ignore this field

    "debugMode"     : 1,
    // "debugMode" possible values :
    //      0 - No message will be printed.
    //      1 - cc.error, cc.assert, cc.warn, cc.log will print in console.
    //      2 - cc.error, cc.assert, cc.warn will print in console.
    //      3 - cc.error, cc.assert will print in console.
    //      4 - cc.error, cc.assert, cc.warn, cc.log will print on canvas, available only on web.
    //      5 - cc.error, cc.assert, cc.warn will print on canvas, available only on web.
    //      6 - cc.error, cc.assert will print on canvas, available only on web.

    "showFPS"       : true,
    // Left bottom corner fps information will show when "showFPS" equals true, otherwise it will be hide.

    "frameRate"     : 60,
    // "frameRate" set the wanted frame rate for your game, but the real fps depends on your game implementation and the running environment.

    "noCache"       : false,
    // Set "noCache" to true can make the loader ignoring the html page cache while loading your resources, 
    // especially useful in Android web browsers.

    "id"            : "gameCanvas",
    // "gameCanvas" sets the id of your canvas element on the web page, it's useful only on web.

    "renderMode"    : 0,
    // "renderMode" sets the renderer type, only useful on web :
    //      0 - Automatically chosen by engine
    //      1 - Forced to use canvas renderer
    //      2 - Forced to use WebGL renderer, but this will be ignored on mobile browsers

    "engineDir"     : "frameworks/cocos2d-html5/",
    // In debug mode, if you use the whole engine to develop your game, you should specify its relative path with "engineDir",
    // but if you are using a single engine file, you can ignore it.

    "modules"       : ["cocos2d"],
    // "modules" defines which modules you will need in your game, it's useful only on web,
    // using this can greatly reduce your game's resource size, and the cocos console tool can package your game with only the modules you set.
    // For details about modules definitions, you can refer to "../../frameworks/cocos2d-html5/modulesConfig.json".

    "jsList"        : [
    ]
    // "jsList" sets the list of js files in your game.
 }
 *
 */

cc.game.onStart = function(){
    if(!cc.sys.isNative && document.getElementById("cocosLoading")) //If referenced loading.js, please remove it
        document.body.removeChild(document.getElementById("cocosLoading"));

    // Pass true to enable retina display, on Android disabled by default to improve performance
    cc.view.enableRetina(cc.sys.os === cc.sys.OS_IOS ? true : false);
    // Adjust viewport meta
    cc.view.adjustViewPort(true);
    // Setup the resolution policy and design resolution size
	cc.view.setDesignResolutionSize(720, 1157, cc.ResolutionPolicy.FIXED_HEIGHT);
    // Instead of set design resolution, you can also set the real pixel resolution size
    // Uncomment the following line and delete the previous line.
    // cc.view.setRealPixelResolution(960, 640, cc.ResolutionPolicy.SHOW_ALL);
    // The game will be resized when browser size change
    cc.view.resizeWithBrowserSize(true);

	// //（资源）/（设计）
	cc.director.setContentScaleFactor(720/720);

	RCCommon.scaleXRatio = cc.director.getVisibleSize().width/720;
	cc.log("RCCommon.scaleXRatio : " + RCCommon.scaleXRatio);

    /*
	// 获取游戏主循环是否被暂停
	var paused = cc.director.isPaused();
	// 设置或获取动画帧间隔，这个设置会直接影响帧率
	var interval = cc.director.getAnimationInterval();
	cc.director.setAnimationInterval(value);
	// 设置或获取导演对象的内容放缩比例
	var scale = cc.director.getContentScaleFactor();
	cc.director.setContentScaleFactor(scaleFactor);
	// 设置或获取游戏世界可视窗口的原点和大小
	var origin = cc.director.getVisibleOrigin();
	var size = cc.director.getVisibleSize();
	// 获取游戏世界大小，winSize的大小通常等同于设计分辨率，而winSizeInPixel的大小是游戏世界的像素大小
	var winSize = cc.director.getWinSize();
	var winSizeInPixel = cc.director.getWinSizeInPixels();
	// 设置或获取调试信息是否被显示
	var isDisplaying = cc.director.isDisplayStats();
	cc.director.setDisplayStats(displayStats);
	// 设置或获取视图，它指向`cc.view`
	var view = cc.director.getOpenGLView();
	cc.director.setOpenGLView(openGLView);
	// 设置或获取WebGL/OpenGL的投影，
	// 可能的投影类型包括：cc.Director.PROJECTION_2D, cc.Director.PROJECTION_3D, cc.Director.PROJECTION_CUSTOM
	cc.director.getProjection();
	cc.director.setProjection(projection);
*/

	//load resources
    cc.LoaderScene.preload(g_resources, function () {
        cc.director.runScene(new StartScene());
    }, this);
};
cc.game.run();