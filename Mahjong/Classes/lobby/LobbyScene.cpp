#include "lobby/LobbyScene.h"
#include "game/mahjong/MjGameScene.h"



bool LobbyScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//connectServer();//���ӷ�����
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
	


	//���ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//TODO չʾ�˳�����
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


// Socker����
void LobbyScene::connectServer()
{
	// ��ʼ��
	// ODSocket socket;
	socket.Init();
	socket.Create(AF_INET, SOCK_STREAM, 0);

	// ���÷�������IP��ַ���˿ں�
	// �����ӷ����� Connect
	const char* ip = "172.23.1.58";
	int port = 9999;
	bool result = socket.Connect(ip, port);

	// �������� Send
	socket.Send("login", 5);

	if (result) {
		CCLOG("connect to server success!");
		// �������̣߳������߳��У���������
		std::thread recvThread = std::thread(&LobbyScene::receiveData, this);
		recvThread.detach(); // �����̷߳���
	}
	else {
		CCLOG("can not connect to server");
		return;
	}
}


void LobbyScene::receiveData(){
	// ��Ϊ��ǿ����
	// ���Կ���һֱ��������Ƿ������ݴ���
	while (true) {
		// �������� Recv
		char data[512] = "";
		int result = socket.Recv(data, 512, 0);
		CCLOG("receive data result:%d", result);
		// ������������ӶϿ���
		if (result <= 0) break;
		CCLOG("receive data:%s", data);
	}
	// �ر�����
	socket.Close();
}