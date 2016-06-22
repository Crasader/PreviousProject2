#include "GameWidget.h"
#include "CommonFunction.h"
#include "Block/SpriteManager.h"

USING_NS_CC;

GameWidget::GameWidget()
	: m_nextGroup(NULL)
{

}

// on "init" you need to initialize your instance
bool GameWidget::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//�������
	float cx = 0.0f;
	float cy = 0.0f;

	//��
	int nZOrderField = 0;
	int nZOrderScore = 0;
	int nZOrderNext = 0;
	int nZOrderScoreLabel = 1;

	//����ͼƬ����
	auto field = SpriteManager::GetInstance()->GetGameFieldSprite();	//Sprite::create("field.png");
	
	

	//�����Ϸ����
	field->setPosition(240,450);
	m_posBlock = Vec2(field->getPositionX() - field->getContentSize().width/2, field->getPositionY() + field->getContentSize().height/2);
	this->addChild(field, nZOrderField);


	m_posScore = Vec2(240, 758);


	m_rectNext = Rect(387,534,70,110);


	//��ʼ������
	m_nScore = 0;
	//������������
	m_scoreLabel = LabelAtlas::create(Value(m_nScore).asString(),"scoreNum.png",16,25,'0');	//2376500
	m_scoreLabel->setPosition(m_posScore);
	this->addChild(m_scoreLabel, nZOrderScoreLabel);

	

	//������һ��ͼ��
	ResetNextGroup();
    
    return true;
}

//��ȡ��һ��ͼ��
void GameWidget::GetNextBlockGroup(BlockGroup*& curGroup, cocos2d::Node* parent)
{
	//��ȡ��һ��ͼ��
	CommonFunction::GetNewBlockGroup(curGroup, m_nextGroup->GetBlockGroupType());
	if (curGroup != NULL)
	{
		curGroup->SetBlockGroupDirection(m_nextGroup->GetBlockGroupDirection());
		curGroup->ResetBlockGroup(parent, m_nextGroup->GetBlocks()[0].index);
	}

	//������һ��ͼ��
	ResetNextGroup();
}

//����ͼ��
void GameWidget::ResetNextGroup()
{
	//����ͼ��
	if (m_nextGroup != NULL)
	{
		for (int i=0; i<BlockGroup::GetBlockGroupNumber(); i++)
		{
			this->removeChild(m_nextGroup->GetBlocks()[i].sprite);
		}
		delete m_nextGroup;
		m_nextGroup = NULL;
	}

	//������һ��ͼ��
	BlockGroupType type =CommonFunction::GetRandonNormalModeType();
	CommonFunction::GetNewBlockGroup(m_nextGroup, type);

	//���÷���
	if (m_nextGroup != NULL)
	{
		m_nextGroup->ResetNextBlockGroup(this, m_rectNext);
	}
}

//ˢ�·���
void GameWidget::RefreshScore()
{
	std::stringstream ss;
	ss << m_nScore;

	std::string strScore = ss.str();
	m_scoreLabel->setString(strScore);
}

//�������
void GameWidget::ResetScore()
{
	m_nScore = 0;
	RefreshScore();
}

//ͼ�νӴ�����ķ���(��10��)
void GameWidget::BlockGroupLanding()
{
	RefreshScore();
}

//��ȥ�����ȡ����
void GameWidget::AddScore(const vector<int>& vecFullRow)
{
	switch (vecFullRow.size())
	{
	case 1:
		m_nScore += 10;
		break;
	case 2:
		//��ȥ��������������йأ�
		m_nScore += (vecFullRow.at(0) + 1 == vecFullRow.at(1) ? 30 : 30);
		break;
	case 3:
		//ͬ�ϵ�����
		m_nScore += (vecFullRow.at(0) + 1 == vecFullRow.at(1) && vecFullRow.at(1) + 1 == vecFullRow.at(2)) ? 60 : 60;
		break;
	case 4:
		m_nScore += 100;
		break;
	default:
		break;
	}
	RefreshScore();
}