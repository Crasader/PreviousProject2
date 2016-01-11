#include "lobby/LobbyScene.h"
#include "game/mahjong/MjGameScene.h"



bool LobbyScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//connectServer();//连接服务器
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* lobby_bg = Sprite::create("main/mainbk.jpg");
	lobby_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	lobby_bg->setScale(0.5);
	this->addChild(lobby_bg,-1);
	//add statr menu to layer

	MenuItemImage* mahjong = MenuItemImage::create("main/mainmajiang.png", "main/mainmajiang.png", CC_CALLBACK_0(LobbyScene::startGame,this));
	mahjong->setScale(0.5);
	Menu* gameMenu = Menu::create(mahjong,NULL);
	gameMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(gameMenu, 1);
	


	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//TODO 展示退出界面
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void LobbyScene::startGame(){
	Director::getInstance()->replaceScene(TransitionFade::create(1, MjGameScene::create()));
}


// Socker连接
void LobbyScene::connectServer()
{
	// 初始化
	// ODSocket socket;
	socket.Init();
	socket.Create(AF_INET, SOCK_STREAM, 0);

	// 设置服务器的IP地址，端口号
	// 并连接服务器 Connect
	const char* ip = "172.23.1.58";
	int port = 9999;
	bool result = socket.Connect(ip, port);

	// 发送数据 Send
	socket.Send("login", 5);

	if (result) {
		CCLOG("connect to server success!");
		// 开启新线程，在子线程中，接收数据
		std::thread recvThread = std::thread(&LobbyScene::receiveData, this);
		recvThread.detach(); // 从主线程分离
	}
	else {
		CCLOG("can not connect to server");
		return;
	}
}


void LobbyScene::receiveData(){
	// 因为是强联网
	// 所以可以一直检测服务端是否有数据传来
	while (true) {
		// 接收数据 Recv
		char data[512] = "";
		int result = socket.Recv(data, 512, 0);
		CCLOG("receive data result:%d", result);
		// 与服务器的连接断开了
		if (result <= 0) break;
		CCLOG("receive data:%s", data);
	}
	// 关闭连接
	socket.Close();
}