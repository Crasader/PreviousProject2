#include "DragModeGameWidget.h"
#include "CommonFunction.h"
#include "Block/SpriteManager.h"

USING_NS_CC;


enum
{
	kTagZordePutedBlock = 5
};

DragModeGameWidget::DragModeGameWidget()
	: m_nextGroup(NULL)
{

}

// on "init" you need to initialize your instance
bool DragModeGameWidget::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	RestReadGroup();


	auto sp = Sprite::create();
	sp->setPosition(0, 0);
	addChild(sp);

	auto pos = sp->getPosition();

	auto draw = DrawNode::create();
	addChild(draw);
	for (int i = 0; i < 11; i++)
	{
		draw->drawLine(Vec2(0, i * GridSide) + GridZeroPos, Vec2(RowCount*GridSide, i * GridSide) + GridZeroPos, Color4F::WHITE);
	}
	for (int i = 0; i < 11; i++)
	{
		draw->drawLine(Vec2(i * GridSide, 0) + GridZeroPos, Vec2(0 + i * GridSide, ColCount*GridSide) + GridZeroPos, Color4F::WHITE);
	}

	//	Size visibleSize = Director::getInstance()->getVisibleSize();
	//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//
	//	//�������
	//	float cx = 0.0f;
	//	float cy = 0.0f;
	//
	//	//��
	//	int nZOrderField = 0;
	//	int nZOrderScore = 0;
	//	int nZOrderNext = 0;
	//	int nZOrderScoreLabel = 1;
	//
	//	//����ͼƬ����
	//	auto field = SpriteManager::GetInstance()->GetGameFieldSprite();	//Sprite::create("field.png");
	//	auto score = SpriteManager::GetInstance()->GetScoreSprite();		//Sprite::create("score.png");
	//	auto next = SpriteManager::GetInstance()->GetNextSprite();			//Sprite::create("next.png");
	//	int sprite_interval = (visibleSize.width - field->getContentSize().width
	//		- score->getContentSize().width - next->getContentSize().width)/4;
	//
	//	//�����Ϸ����
	//	field->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	//	//ͼƬ����������Ϸ����30px����߾�����Ϸ����35px
	//	m_posBlock = Vec2(field->getPositionX() - field->getContentSize().width/2 + 35, field->getPositionY() + field->getContentSize().height/2 - 30);
	//	this->addChild(field, nZOrderField);
	//
	//	//��ӷ�������
	//	cx = origin.x + sprite_interval + score->getContentSize().width/2;
	//	cy = origin.y + visibleSize.height/10*9 - score->getContentSize().height/2;
	//	m_posScore = Vec2(cx, cy);
	//	m_sizeScore = score->getContentSize();
	//	score->setPosition(m_posScore);
	//	this->addChild(score, nZOrderScore);
	//
	//	//�����һ������
	//	float height_inetrval = 50.0f;
	//	cx = origin.x + score->getContentSize().width + field->getContentSize().width + sprite_interval*3 + next->getContentSize().width/2;
	//	m_rectNext = Rect(cx - next->getContentSize().width/2, cy + next->getContentSize().height/2 - height_inetrval,
	//		next->getContentSize().width, next->getContentSize().height - height_inetrval);
	//	next->setPosition(Vec2(cx, cy));
	//	this->addChild(next, nZOrderNext);
	//
	//	//ͨ���ַ�ͼƬ�������壺��Ҫ����������ߡ���ʼ�ַ�
	//// 	Label* label = Label::createWithCharMap("fonts/number.png", 38, 38, '0');
	//// 	label->setString("0");	//�����ַ�������
	//// 	m_score->setPosition(Vec2(origin.x + 127, origin.y + 900 + 20));
	//
	//	//������������
	//	m_scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 80);	//2376500
	//	m_scoreLabel->setPosition(Vec2(m_posScore.x, m_posScore.y - height_inetrval/2));
	//	this->addChild(m_scoreLabel, nZOrderScoreLabel);
	//
	//	//��ʼ������
	//	m_nScore = 0;
	//
	//	//������һ��ͼ��
	//	ResetNextGroup();
	//    
	return true;
}

//��ȡ��һ��ͼ��
void DragModeGameWidget::GetNextBlockGroup(BlockGroup*& curGroup, cocos2d::Node* parent)
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
void DragModeGameWidget::ResetNextGroup()
{
	//����ͼ��
	if (m_nextGroup != NULL)
	{
		for (int i = 0; i < BlockGroup::GetBlockGroupNumber(); i++)
		{
			this->removeChild(m_nextGroup->GetBlocks()[i].sprite);
		}
		delete m_nextGroup;
		m_nextGroup = NULL;
	}

	//������һ��ͼ��
	BlockGroupType type = BlockGroupType(rand() % BlockGroup::GetGroupTypeNumber());
	CommonFunction::GetNewBlockGroup(m_nextGroup, type);

	//���÷���
	if (m_nextGroup != NULL)
	{
		m_nextGroup->ResetNextBlockGroup(this, m_rectNext);
	}
}

//ˢ�·���
void DragModeGameWidget::RefreshScore()
{
	std::stringstream ss;
	ss << m_nScore;

	std::string strScore = ss.str();
	m_scoreLabel->setString(strScore);
}

//�������
void DragModeGameWidget::ResetScore()
{
	m_nScore = 0;
	RefreshScore();
}

//ͼ�νӴ�����ķ���(��10��)
void DragModeGameWidget::BlockGroupLanding()
{
	m_nScore += 10;
	RefreshScore();
}

//��ȥ�����ȡ����
void DragModeGameWidget::AddScore(const vector<int>& vecFullRow)
{
	switch (vecFullRow.size())
	{
	case 1:
		m_nScore += 100;
		break;
	case 2:
		//��ȥ��������������йأ�
		m_nScore += (vecFullRow.at(0) + 1 == vecFullRow.at(1) ? 200 : 200);
		break;
	case 3:
		//ͬ�ϵ�����
		m_nScore += (vecFullRow.at(0) + 1 == vecFullRow.at(1) && vecFullRow.at(1) + 1 == vecFullRow.at(2)) ? 400 : 400;
		break;
	case 4:
		m_nScore += 800;
		break;
	default:
		break;
	}
	RefreshScore();
}

void DragModeGameWidget::RestReadGroup()
{
	if (m_vecReadBlocks.size() > 0)
	{
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		BlockGroupEntity* temp = new BlockGroupEntity();
		temp->data = CommonFunction::GetDropModeNewBlockGroup();
		temp->sprite = Sprite::create();
		m_vecReadBlocks.push_back(temp);
		addChild(temp->sprite, 10);
	}

	for (int i = 0; i < m_vecReadBlocks.size(); i++)
	{
		auto group = m_vecReadBlocks[i];
		group->sprite->setPosition(Vec2(300 + i * 300, 100));
		group->sprite->setAnchorPoint(Point::ZERO);
		for (auto var : group->data->GetBlocks())
		{
			auto size = SpriteManager::GetInstance()->GetBlockSize();
			int rowSign = var.row == 0 ? 0 : var.row / abs(var.row);
			int colSign = var.col == 0 ? 0 : var.col / abs(var.col);
			var.sprite->setPosition(Vec2((var.row - 0.5*(rowSign))*size.width, (var.col - 0.5*(colSign))*size.height));
			group->sprite->addChild(var.sprite);
		}
	}
}



// ������ʼ�¼�
bool DragModeGameWidget::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (m_nowTouchBlock)
	{
		return false;
	}
	auto pos = touch->getLocation();
	for (auto var : m_vecReadBlocks)
	{
		for (auto ob : var->data->GetBlocks())
		{
			auto nodePos = var->sprite->convertToNodeSpace(pos);
			if (ob.sprite->getBoundingBox().containsPoint(nodePos))
			{
				m_nowTouchBlock = var;
				m_nowTouchBlockStartPos = m_nowTouchBlock->sprite->getPosition();
				m_nowTouchBlock->sprite->runAction(Spawn::create(MoveBy::create(0.2f, Vec2(0, 50)), ScaleTo::create(0.2f, 2.0f), nullptr));

				return true;
			}
		}
	}
	return false;
}

// ��������
void DragModeGameWidget::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (!m_nowTouchBlock)
	{
		return;
	}
	auto diffpos = touch->getLocation() - touch->getPreviousLocation();
	m_nowTouchBlock->sprite->setPosition(m_nowTouchBlock->sprite->getPosition() + diffpos);
}

// ���������¼�
void DragModeGameWidget::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (!m_nowTouchBlock)
	{
		return;
	}
	for (auto var : m_nowTouchBlock->data->GetBlocks())
	{
		int row;
		int col;
		getGridxy(m_nowTouchBlock->sprite->convertToWorldSpace(var.sprite->getPosition()), row, col);
		if (isExistBlock(row, col) || isOutofGrid(row, col))
		{
			m_nowTouchBlock->sprite->setScale(1.0f);
			m_nowTouchBlock->sprite->stopAllActions();
			m_nowTouchBlock->sprite->setPosition(m_nowTouchBlockStartPos);
			m_nowTouchBlock = nullptr;
			return;
		}
	}
	for (auto var : m_nowTouchBlock->data->GetBlocks())
	{
		int row;
		int col;
		getGridxy(m_nowTouchBlock->sprite->convertToWorldSpace(var.sprite->getPosition()), row, col);
		addBlock(row, col, var);
	}
	for (auto iter = m_vecReadBlocks.begin(); iter != m_vecReadBlocks.end(); iter++)
	{
		if (*iter == m_nowTouchBlock)
		{
			m_vecReadBlocks.erase(iter);
			break;
		}
	}
	delete m_nowTouchBlock;
	m_nowTouchBlock = nullptr;

	//���õȴ�������
	if (m_vecReadBlocks.size() <= 0)
	{
		RestReadGroup();
	}


	//�����������п���������
	std::vector<int>			m_vecFullRow;
	std::map<int/*�к�*/, int/*��ǰ�еķ�����*/> mapRow;
	std::vector<BlockObject>::const_iterator cit;
	for (cit = m_vecBlocks.begin(); cit != m_vecBlocks.end(); ++cit)
	{
		if (++mapRow[cit->col] == RowCount)
		{
			m_vecFullRow.push_back(cit->col);
		}
	}

	for (auto var:m_vecFullRow)
	{
		for (auto it = m_vecBlocks.begin(); it != m_vecBlocks.end();)
		{
			if (var== it->col)
			{	
				removeBlock(it->row, it->col);
				it = m_vecBlocks.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	//����
	int size = m_vecReadBlocks.size();
	for (int i = 0; i < size;i++)
	{
		if (!isCouldPutTheBlockgroup(m_vecReadBlocks.at(i)->data))
		{
			size--;
		}
	}
if (size<=0)
{
	CCLOG("you are failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
}
}

bool DragModeGameWidget::isExistBlock(int row, int col)
{
	for (auto var : m_vecBlocks)
	{
		if (var.col == col&&var.row == row)
		{
			return true;
		}

	}
	return false;
}
bool DragModeGameWidget::isOutofGrid(int row, int col)
{
	if (row < 0 || row>9 || col < 0 || col>9)
	{
		return true;
	}
	return false;
}

void DragModeGameWidget::getGridxy(Vec2 in_Pos, int &out_Row, int &out_Col)
{
	Vec2 p = in_Pos - GridZeroPos;
	if (p.x<0||p.y<0)
	{
		out_Row = -1;
		out_Col = -1;
		return;
	}
	out_Row = p.x / GridSide;
	out_Col = p.y / GridSide;
}





bool DragModeGameWidget::isCouldPutTheBlockgroup(BlockGroup*group)
{
	bool isCould = false;
	for (int i = 0; i < RowCount;i++)
	{
		for (int j = 0; j < ColCount;j++)
		{
			int size = group->GetBlocks().size();
			for (auto var:group->GetBlocks())
			{
				int col = var.col + j;
				int row = var.row + i;
				if (isExistBlock(row,col)||isOutofGrid(row,col))
				{
					break;
				}
				else
				{
					size--;
				}
			}
			if (size==0)
			{
				return true;
			}
			else
			{
				continue;
			}
		}
	}
	return isCould;
}



void DragModeGameWidget::removeBlock(int row, int col)
{
	if (!isExistBlock(row, col))
	{
		return;
	}
	for (auto ite = m_vecBlocks.begin(); ite != m_vecBlocks.end(); ite++)
	{
		if (ite->col == col&&ite->row == row)
		{
			ite->sprite->removeFromParentAndCleanup(1);

			return;
		}

	}
}
void DragModeGameWidget::addBlock(int row, int col, BlockObject &block)
{
	if (isExistBlock(row, col))
	{
		return;
	}
	block.row = row;
	block.col = col;
	block.sprite->retain();
	block.sprite->removeFromParentAndCleanup(false);
	m_vecBlocks.push_back(block);
	refreshBlocks();
}

void DragModeGameWidget::refreshBlocks()
{
	for (auto var : m_vecBlocks)
	{
		var.sprite->setPosition(GridZeroPos + Vec2((var.row + 0.5)*GridSide, (var.col + 0.5)*GridSide));
		if (!var.sprite->getParent())
		{
			addChild(var.sprite, kTagZordePutedBlock);
		}
	}
}