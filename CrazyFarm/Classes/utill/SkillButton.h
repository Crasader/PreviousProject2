/** 
    实现技能冷却效果 

    Notice:添加child时要注意上下层关系
    最下方是按钮 其次是半透明的模版图片 最上方是CCProgressTimer进度条精灵
*/
#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include <cocos2d.h>
USING_NS_CC;
class SkillButton : public Node
{
public:
    SkillButton();
    virtual ~SkillButton();

    /** 创建一个SkillButton对象
        */
    static SkillButton* createSkillButton(float cdTime,
                                        const char* stencil_file_name, 
                                        const char* button_normal_name, 
                                        const char* button_click_name,
										int propNum);

	void refreshPropNumLabel();
    /** CD时间设置
        */
    void    setCDTime(float time) { mCDTime = time; }
    float   getCDTime() const { return mCDTime; }
protected:
    /** 技能按钮点击回调 */
   virtual void    skillClickCallBack(Ref* obj);

    /** 技能冷却完毕回调*/
   virtual void    skillCoolDownCallBack();


    /** 初始化 */
	bool    init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, int propNum);
	int              mPropNum;       //道具数量
private:
    MenuItemImage*   mItemSkill;     // 技能按钮
    Menu*            mMenuSkill;     // 技能按钮所在menu
    Sprite*          mStencil;       // 蒙板精灵,黑色半透明(这个是为了显示一个冷却计时效果)
    ProgressTimer*   mProgressTimer; // 时间进度条精灵(360度旋转)
    float            mCDTime;          // CD时间
	
};


#endif
