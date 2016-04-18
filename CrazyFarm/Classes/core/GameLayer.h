#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "fish/FishManage.h"
#include "bullet/BulletManage.h"
#include "turret/PlayerTurret.h"
#include "net/Net.h"
#include "domain/room/RoomManager.h"
#include "domain/magnate/MagnateManager.h"
#include "server/MsgObserver.h"
#include "server/Msg/MSGstdafx.h"
USING_NS_CC;
enum TouchType
{
	TouchInNormal,
	TouchInLock,
	TouchInBoom,
	TouchInAutoShoot,
	TouchInLight
};

class GameLayer: public cocos2d::Layer ,public MsgObserver{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void loadNewMonent(int monmentType);
	void RefreShmyPlayerTurret();
	
	void addReward(int itemid, int num);



	Vector<PlayerTurret*> GetOtherTurret(){ return otherTurrets; }

	void createNet(Bullet *bullet);//������
	PlayerTurret* GetMyTurret(){ return myTurret; }
	//�齱�����������̻�
	void onGetReward(int itemid, int num);
	//ĳ���������߻���ʯ
	void onGetRewardByfish(PlayerTurret*turrent,Fish*fish,int itemid,int num);
	void onExitEX();
private:
	void createTurret();//����������������
	void addTouchEvent();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	//�����ӵ�	

	void rotateTurret(float degree, PlayerTurret* turret);//��ת����

	void showYourChairno();

	void AiUpdata(float dt);
	
	void onEnter();
	virtual void onEnterTransitionDidFinish();
	//Updata
	void collisionUpdate(float dt);
	void update(float dt);
	void shootUpdata(float dt);
	//���10Sͬ��һ����Ϣ
public:
	void UpdateUserinfo(float dt);

	//����
public:
	void beginLight();
	void endLight();
	void LightUpdata(float dt);
	bool lightTouchEvent(Touch *touch, Event  *event);
 //����
public:
	void beginLock();
	void endLock();
private:
	void LockUpdata(float dt);
	bool lockTouchEvent(Touch *touch, Event  *event);
//�˵�
public:
	void beginSkillBoom();
	void endSkillBoom(); 
	void onBoomCatchFish(Point pos,PlayerTurret*turrent);
	void doBoom(Point pos, PlayerTurret*turrent,bool isrobot);
private:
	bool boomTouchEvent(Touch *touch, Event  *event);
	
//�Զ�����
public:
	void beginAutoShoot();
	void endAutoShoot();
private:
	Point autoShootPos;
	bool AutoShootTouchEvent(Touch *touch, Event  *event);
////////////����
public:
	void useFreeze(PlayerTurret*turret);
	void onFreezeEnd(PlayerTurret*turret);
////�㳱����
	void onClearFish();
	void onClearFishUpdata(float dt);
	void onClearFishFinish();
private:

	int m_index = -1; //�ͻ�����ʾλ��
	int m_curIndex;//ʵ��λ��


	void initFishAndBulletData();


	//�����
	bool onTouTurret(Point pos);
	void removePlayerInfo();
	void calculateFreeChair();

	//utill
	static bool sortFish(const Fish * m1, const Fish * m2);
	

	PlayerTurret* myTurret = NULL;

	Vector<PlayerTurret*> otherTurrets;
	std::vector<RoomPlayer> players;
	
	EventListenerTouchOneByOne* touchListener;
	bool isShoot = true;
//����¼�
	void changeTouchFunByTouchType(TouchType type);
	TouchType m_touchType;
	TouchType m_lasttouchType;


	std::list<TouchType> _touchtypes;
	Sprite* game_bg;

	CC_SYNTHESIZE(Node*, createFishAcNode, CreateFishAcNode);
	CC_SYNTHESIZE(bool, isShowYourChairno, IsShowYourChairno);
	Point touchpos;
	bool istouched = false;
	float shootTemp = 0;


	std::map<int, Sprite*> TxtWaitingTurrent;

	public:
	void onTurretLeave(PlayerTurret*turret);
///////ǿ�������
public:
	virtual void handle_event(const char* msgId, const char* msgBody);
private:
//��Ϣ
	static bool sortMsg(const Msg_Base * m1, const Msg_Base * m2);

	

	void onSomeoneLeave(Msg_onLeave* msg);  //����뿪
	void onSomeoneComing(Msg_onAdd* msg);  //��ҽ���
	void onClientInit(Msg_onInit* msg);   //init
	void onFishesMsg(Msg_OnFishes*msg);  //��Ⱥ��Ϣ
	void onConError(Msg_ConError*msg);  //�Ͽ�����
	void onUpdateTurrent(Msg_OnUpdateTurrent*msg); //��������
	void onUpdateLevel(Msg_OnExpUpdate*msg); //����
	void onGetBounsPool(Msg_OnGetBounsPool*msg); //��ȡ�����
	void onUseSkill(Msg_UseSkill* msg); //ʹ�ü���
	void onLuckDraw(Msg_LuckDraw* msg); //ת�̳齱
	void onBankrupt(Msg_OnBankrupt* msg); //�Ʋ���Ϣ
	void onbankruptRebirth(Msg_OnBankruptRebirth* msg); //�Ʋ���ȡ
	void onMagnate(Msg_OnMagnate*msg); //����
	void onPayresulet(Msg_Payresult*msg); //֧�����
	void onBossDead(Msg_OnBossDead*msg); //BOSS������
	void onMarquee(Msg_OnMarquee*msg);  //��������������Ϣ
	void onBeginMarried(Msg_OnBeginMarried*msg);  //����������ʼ
	void onCathchMarriedFish(Msg_OnCatchMarriedFish*msg);//��������
	void onMarriedTaskSuccess(Msg_OnMarriedSuccess*msg); //����������ɹ�
	void ToPayShopCallBack(Ref*psend);
	void exitCallback(Ref*psend);
	void MsgUpdata(float dt);
	std::list<Msg_Base*> Msgs;
	//��ʼʱ��
	unsigned long init_creat_time;
	//�������
	void FFOneTimeToFishes(float FFTime);

	void UpdateCreateFishByServer(float dt);


	int _fishGroupType;//0 ��Ⱥ 1�㳱

	int _fishGroupMonentType;
	//
	bool isInitData = false;


};
#endif