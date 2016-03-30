#pragma once
#include "cocos2d.h"
#include "LoginScene.h"
USING_NS_CC;


	class DropDownList : public CCLayer
	{
	public:
		//���췽��
		DropDownList(Sprite* label, Size size);
		//��������
		~DropDownList();

		//����ʵ�����󷽷�
		static DropDownList* create(Sprite* label, Size size);
		 
		void onEnter();


		virtual bool onTouchBegan(CCTouch *touch, CCEvent *event);

		virtual bool emptyTouch(CCTouch *touch, CCEvent *event){ return true; };
		//������menu item �����һ��label���ǵ�����
		void addLabel(std::string label);

		//ѡ�������б��
		void onSelected(Object* sender);

		//�ر������б��
		void onClose();

		void setLoginscene(LoginScene*scene);
	private:
		CCMenu* mainMenu;  //�����б�ѡ��ļ���

		Sprite* showLabel;  //��ʾѡ�еĽ��

		std::vector<std::string> selectLabels;  //�����б�label
		std::vector<Sprite*> selectSpriteFrame; 

		bool isShowMenu;  //�Ƿ���ʾ�������б�

		Sprite*bgFrame; 
		int lastSelectedIndex;  //ѡ�������б��index
		LoginScene* _loginscene;
	};
