#pragma once
#include "cocos2d.h"
#include "LoginScene.h"
USING_NS_CC;


	class DropDownList : public CCLayer
	{
	public:
		//构造方法
		DropDownList(Sprite* label, Size size);
		//析构函数
		~DropDownList();

		//创建实例对象方法
		static DropDownList* create(Sprite* label, Size size);
		 
		void onEnter();


		virtual bool onTouchBegan(CCTouch *touch, CCEvent *event);

		virtual bool emptyTouch(CCTouch *touch, CCEvent *event){ return true; };
		//创建以menu item 并添加一个label覆盖到上面
		void addLabel(std::string label);

		//选中下拉列表后
		void onSelected(Object* sender);

		//关闭下拉列表框
		void onClose();

		void setLoginscene(LoginScene*scene);
	private:
		CCMenu* mainMenu;  //下拉列表选项的集合

		Sprite* showLabel;  //显示选中的结果

		std::vector<std::string> selectLabels;  //下拉列表label
		std::vector<Sprite*> selectSpriteFrame; 

		bool isShowMenu;  //是否显示了下拉列表

		Sprite*bgFrame; 
		int lastSelectedIndex;  //选中下拉列表的index
		LoginScene* _loginscene;
	};
