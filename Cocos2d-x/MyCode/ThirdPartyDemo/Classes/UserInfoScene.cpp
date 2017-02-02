#include "UserInfoScene.h"

#include "InformationScene.h"

UserInfoScene::UserInfoScene() {

};

UserInfoScene::~UserInfoScene() {

};

Scene* UserInfoScene::createScene() {
	auto scene = Scene::create();
	auto layer = UserInfoScene::create();
	scene->addChild(layer);

	return scene;
};

bool UserInfoScene::init() {
	
	if (!Layer::init())	{
		return false;
	}

	_userdef = UserDefault::sharedUserDefault();

	Wsize = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("bginfo.png");
	bg->setPosition(Wsize.width/2, Wsize.height/2);
	this->addChild(bg);

	//返回
	auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(UserInfoScene::backFunc, this));
	itemBack->setPosition(100, (Wsize.height-50));
	itemBack->setScale(1.5);

	auto menu = Menu::create(itemBack, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	
	//string token = userdef->getStringForKey("token");
	//log("token : %s.", token.c_str());
	//string openid = userdef->getStringForKey("openid");
	//log("openid : %s.", openid.c_str());
	string nickname = _userdef->getStringForKey("nickname");
	log("nickname : %s.", nickname.c_str());
	string sex = _userdef->getStringForKey("sex");
	log("sex : %s.", sex.c_str());
	//string headimageurl = userdef->getStringForKey("headimageurl");
	//log("headimageurl : %s.", headimageurl.c_str());
	string province = _userdef->getStringForKey("province");
	log("province : %s.", province.c_str());
	string city = _userdef->getStringForKey("city");
	log("city : %s.", city.c_str());

	//gbk转换utf-8
	GBKToUTF8(nickname, "gb2312", "utf-8");
	//log("nickname : %s", nickname.c_str());
	Label* nicknameLabel = Label::createWithSystemFont(nickname.c_str(), "Arial", 40);
	nicknameLabel->setPosition(Wsize.width/2, Wsize.height/2);
	nicknameLabel->setColor(Color3B::BLACK);
	this->addChild(nicknameLabel);

	GBKToUTF8(sex, "gb2312", "utf-8");
	//log("sex : %s", sex.c_str());
	Label* sexLabel = Label::createWithSystemFont(sex.c_str(), "Arial", 40);
	sexLabel->setPosition(Wsize.width/2, nicknameLabel->getPositionY() - 50);
	sexLabel->setColor(Color3B::BLACK);
	this->addChild(sexLabel);

	GBKToUTF8(province, "gb2312", "utf-8");
	//log("province : %s", province.c_str());
	Label* provinceLabel = Label::createWithSystemFont(province.c_str(), "Arial", 40);
	provinceLabel->setPosition(Wsize.width/2, sexLabel->getPositionY()-50);
	provinceLabel->setColor(Color3B::BLACK);
	this->addChild(provinceLabel);

	GBKToUTF8(city, "gb2312", "utf-8");
	//log("city : %s", city.c_str());
	Label* cityLabel = Label::createWithSystemFont(city.c_str(), "Arial", 40);
	cityLabel->setPosition(Wsize.width/2, provinceLabel->getPositionY()-50);
	cityLabel->setColor(Color3B::BLACK);
	this->addChild(cityLabel);

	_path = FileUtils::sharedFileUtils()->getWritablePath()+_userdef->getStringForKey("uid")+"_head.png";
	if (FileUtils::sharedFileUtils()->isFileExist(_path)){
		log("exsit");
		_headSpr = Sprite::create(_path.c_str());
		_headSpr->setPosition(Wsize.width/2, Wsize.height*4/5);
		this->addChild(_headSpr);
	}
	else {
		log("not exsit");
		this->downloadHttpImage(this, _userdef->getStringForKey("headimageurl").c_str());
	}

	return true;
};

void UserInfoScene::downloadHttpImage(Object* obj, const char* url) {
	log("getHttpImage");

	//创建httpRequest对象
	HttpRequest* httprequest = new HttpRequest();
	//请求url
	httprequest->setUrl(url);
	//请求类型
	httprequest->setRequestType(HttpRequest::Type::GET);
	//请求完成后的回调
	httprequest->setResponseCallback(obj, httpresponse_selector(UserInfoScene::getImageCompleted));

	//为请求设置标签,后面可以根据这个标签来获取想要的数据
	httprequest->setTag("getimage");

	HttpClient* httpclient = HttpClient::getInstance();
	//连接超时
	httpclient->setTimeoutForConnect(30);
	httpclient->send(httprequest);
	httprequest->release();
};

void UserInfoScene::getImageCompleted(HttpClient* sender, HttpResponse* response) {
	log("getImageCompleted");

	if(!response) {
		return;
	}

	const char* tag = response->getHttpRequest()->getTag();
	/*
	若str1==str2，则返回零；
	若str1<str2，则返回负数；
	若str1>str2，则返回正数
	*/
	if(0==strcmp("getimage", tag)) {
		log("%s completed", response->getHttpRequest()->getTag());
	}

	//判断是否响应成功
	if(!response->isSucceed()) {
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	vector<char>* buffer = response->getResponseData();
	/*	保存到本地文件中  */
	log("uid  : %s", _path.c_str());
	string buffff(buffer->begin(), buffer->end());
	FILE* file = fopen(_path.c_str(), "wb+");
	fwrite(buffff.c_str(), 1, buffer->size(), file);
	fclose(file);

	//Texture
	Image* image = new Image;
	image->initWithImageData((unsigned char*)buffer->data(), buffer->size());

	Texture2D* texture = new Texture2D();
	bool isImage = texture->initWithImage(image);
	image->release();
	if (!isImage){
		delete texture;
		return;
	}

	this->createHeadImage(texture);
};

void UserInfoScene::createHeadImage(Texture2D* texture) {
	log("createHeadImage");

	_headSpr = Sprite::createWithTexture(texture);
	_headSpr->setPosition(Wsize.width/2, Wsize.height*4/5);
	this->addChild(_headSpr);
	texture->release();
};

int UserInfoScene::GBKToUTF8(string & gbkStr, const char* toCode, const char* fromCode){

	//iconv_t iconvH;
	//iconvH = iconv_open(fromCode, toCode);
	//if(iconvH==0) {
	//	return -1;
	//}

	//const char* strChar = gbkStr.c_str();
	//const char** pin = &strChar;
	//size_t strLength = gbkStr.length();

	//char* outbuf = (char*)malloc(strLength*4);
	//char* pBuff = outbuf;

	//memset(outbuf, 0, strLength*4);

	//size_t outLength = strLength*4;
	//if(-1==iconv(iconvH, pin, &strLength, &outbuf, &outLength)) {
	//	iconv_close(iconvH);
	//	return -1;
	//}

	//gbkStr = pBuff;
	//iconv_close(iconvH);

	return 1;
};

void UserInfoScene::backFunc(Ref* pSender) {
	log("backFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, InformationScene::createScene()));
};

