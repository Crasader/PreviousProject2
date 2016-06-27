#include "DragModeGameWidget.h"
#include "CommonFunction.h"
#include "Block/SpriteManager.h"
#include "utill/AnimationUtil.h"



enum
{
	kTagZordePutedBlock = 5
};

DragModeGameWidget::DragModeGameWidget()
	: m_nextGroup(NULL)
	,m_gameTouchType(Touch_Normal)
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

	auto girdBox = Sprite::createWithSpriteFrameName("dropModeBox.png");
	girdBox->setPosition(240, 800 - 77 - girdBox->getContentSize().height / 2);
	addChild(girdBox);

	//网格边缘24*21
	GridZeroPos = Vec2(girdBox->getPositionX() - girdBox->getContentSize().width / 2 + 24, girdBox->getPositionY() - girdBox->getContentSize().height / 2 + 21);

	///test 网格
	//auto draw = DrawNode::create();
	//addChild(draw,100);


	//for (int i = 0; i < 11; i++)
	//{
	//	draw->drawLine(Vec2(0, i * GridSide) + GridZeroPos, Vec2(RowCount*GridSide, i * GridSide) + GridZeroPos, Color4F::RED);
	//}
	//for (int i = 0; i < 11; i++)
	//{
	//	draw->drawLine(Vec2(i * GridSide, 0) + GridZeroPos, Vec2(0 + i * GridSide, ColCount*GridSide) + GridZeroPos, Color4F::RED);
	//}

	//创建分数
	auto scoreFrame = Sprite::createWithSpriteFrameName("scoreFrame.png");
	scoreFrame->setPosition(240, 800);
	scoreFrame->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	addChild(scoreFrame, 5);

	//初始化分数
	m_nScore = 0;
	m_scoreLabel = LabelAtlas::create("0", "scoreNum.png", 16, 25, '0');
	m_scoreLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	m_scoreLabel->setPosition(scoreFrame->getContentSize() / 2 + Size(0, 5));
	scoreFrame->addChild(m_scoreLabel);


	//添加已经消除多少行
	m_nLine = 0;
	auto cutLineFrame = Sprite::createWithSpriteFrameName("cutLineFrame.png");
	cutLineFrame->setPosition(480, 800);
	cutLineFrame->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
	addChild(cutLineFrame, 5);

	//添加标签
	m_labelLine = LabelAtlas::create(Value(m_nLine).asString(), "scoreNum.png", 16, 25, '0');
	m_labelLine->setPosition(cutLineFrame->getContentSize() / 2 + Size(0, 10));
	m_labelLine->setAnchorPoint(Point::ANCHOR_MIDDLE);
	cutLineFrame->addChild(m_labelLine);

	return true;
}


//刷新分数
void DragModeGameWidget::RefreshScore()
{
	m_scoreLabel->setString(Value(m_nScore).asString());
}
//刷新标签
void DragModeGameWidget::RefreshLine()
{

	m_labelLine->setString(Value(m_nLine).asString());
}

//重设分数
void DragModeGameWidget::ResetScore()
{
	m_nScore = 0;
	RefreshScore();
}


//消去方块获取分数
void DragModeGameWidget::AddScore(int cutLine)
{
	switch (cutLine)
	{
	case 1:
		m_nScore += 10;
		break;
	case 2:
		m_nScore += 30;
		break;
	case 3:
		//同上的疑问
		m_nScore += 60;
		break;
	case 4:
		m_nScore += 100;
		break;
	case 5:
		m_nScore += 150;
		break;
	case 6:
		m_nScore += 210;
		break;
	case 7:
		m_nScore += 280;
		break;
	default:
		break;
	}
	m_nLine += cutLine;
	RefreshScore();
	RefreshLine();
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
		group->sprite->setPosition(Vec2((i + 1) * 120, 100));
		group->sprite->setAnchorPoint(Point::ZERO);
		for (auto var : group->data->GetBlocks())
		{
			auto size = SpriteManager::GetInstance()->GetBlockSprite(1, true)->getContentSize();
			int rowSign = var.row == 0 ? 0 : var.row / abs(var.row);
			int colSign = var.col == 0 ? 0 : var.col / abs(var.col);
			var.sprite->setPosition(Vec2((var.row - 0.5*(rowSign))*size.width, (var.col - 0.5*(colSign))*size.height));
			group->sprite->addChild(var.sprite);

		}
		group->sprite->setScale(0.5);
	}
}



// 触摸开始事件
bool DragModeGameWidget::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto pos = touch->getLocation();
	switch (m_gameTouchType)
	{
	case Touch_Normal:
	{
		if (m_nowTouchBlock)
		{
			return false;
		}

		for (auto var : m_vecReadBlocks)
		{
			for (auto ob : var->data->GetBlocks())
			{
				auto nodePos = var->sprite->convertToNodeSpace(pos);
				if (ob.sprite->getBoundingBox().containsPoint(nodePos))
				{
					m_nowTouchBlock = var;
					m_nowTouchBlockStartPos = m_nowTouchBlock->sprite->getPosition();
					m_nowTouchBlock->sprite->runAction(Spawn::create(MoveBy::create(0.2f, Vec2(0, 50)), ScaleTo::create(0.2f, 1.0f), nullptr));

					return true;
				}
			}
		}
		return false;
	}
	break;
	case Touch_SkillKnock:
		break;
	case Touch_SkillFill:
		break;
	default:
		break;
	}

}

// 触摸滑动
void DragModeGameWidget::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (m_gameTouchType == Touch_Normal)
	{
		if (!m_nowTouchBlock)
		{
			return;
		}
		auto diffpos = touch->getLocation() - touch->getPreviousLocation();
		m_nowTouchBlock->sprite->setPosition(m_nowTouchBlock->sprite->getPosition() + diffpos);
	}

}

// 触摸结束事件
void DragModeGameWidget::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	switch (m_gameTouchType)
	{
	case Touch_Normal:
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
				m_nowTouchBlock->sprite->setScale(0.5f);
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

		//重置等待区方块
		if (m_vecReadBlocks.size() <= 0)
		{
			RestReadGroup();
		}
		ReleaseBlocksOnFullLine();

	}
	break;
	case Touch_SkillKnock:
	case Touch_SkillFill:
	{
		auto startPos = touch->getPreviousLocation();
		auto endPos = touch->getLocation();
		if (startPos.distance(endPos) > 50)
		{
			return;
		}
		else
		{
			bool isUseScuess = false;
			if (m_gameTouchType == Touch_SkillFill)
			{
				isUseScuess =FillBlock(endPos);
			}
			else if (m_gameTouchType == Touch_SkillKnock)
			{
				isUseScuess =KnockBlock(endPos);
			}

			if (isUseScuess)
			{
				m_gameTouchType = Touch_Normal;
			}
		}
	}
	break;
	default:
		break;
	}


}
bool DragModeGameWidget::ReleaseBlocksOnFullLine()
{


	//计算消除整行可消除方块
	std::vector<BlockCutData>			m_vecFullLine;
	std::map<int, int> mapRow;

	std::vector<BlockCutData>            m_vecFullCol;
	std::map<int, int> mapCol;

	std::vector<BlockObject>::const_iterator cit;
	for (cit = m_vecBlocks.begin(); cit != m_vecBlocks.end(); ++cit)
	{
		if (++mapRow[cit->col] == RowCount)
		{
			BlockCutData data;
			data.index = cit->col;
			data.cutType = 2;
			m_vecFullLine.push_back(data);
		}
		if (++mapCol[cit->row] == ColCount)
		{
			BlockCutData data;
			data.index = cit->row;
			data.cutType = 1;
			m_vecFullLine.push_back(data);
		}
	}
	if (m_vecFullLine.size() > 0)
	{
		for (auto var : m_vecFullLine)
		{
			if (var.cutType == 2)
			{
				for (auto block : m_vecBlocks)
				{
					if (var.index == block.col)
					{
						float cy = block.sprite->getParent()->convertToWorldSpace(block.sprite->getPosition()).y;
						auto ani = Sprite::create();
						ani->setPosition(240, cy);
						addChild(ani, 5 + 1);
						ani->runAction(Sequence::createWithTwoActions(AnimationUtil::getInstance()->getAnimate("ani_xiaochu"), RemoveSelf::create(true)));
						break;
					}
				}
			}
			else
			{
				for (auto block : m_vecBlocks)
				{
					if (var.index == block.row)
					{
						float cx = block.sprite->getParent()->convertToWorldSpace(block.sprite->getPosition()).x;
						auto ani = Sprite::create();
						ani->setPosition(cx, 489);
						ani->setRotation(90);
						addChild(ani, 5 + 1);
						ani->runAction(Sequence::createWithTwoActions(AnimationUtil::getInstance()->getAnimate("ani_xiaochu"), RemoveSelf::create(true)));
						break;
					}
				}
			}

		}
		float dealy = AnimationUtil::getInstance()->getAnimate("ani_xiaochu")->getAnimation()->getDuration();
		runAction(Sequence::createWithTwoActions(DelayTime::create(dealy), CallFunc::create([=]
		{
			AddScore(m_vecFullLine.size());
			for (auto var : m_vecFullLine)
			{
				for (auto it = m_vecBlocks.begin(); it != m_vecBlocks.end();)
				{
					if ((var.index == it->col&&var.cutType == 2) || (var.index == it->row&&var.cutType == 1))
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
			CheckIsFailed();
		})));
		return true;
	}
	else
	{
		CheckIsFailed();
		return false;
	}
}
void DragModeGameWidget::CheckIsFailed()
{
	int size = m_vecReadBlocks.size();
	for (int i = 0; i < size; i++)
	{
		if (!isCouldPutTheBlockgroup(m_vecReadBlocks.at(i)->data))
		{
			size--;
		}
	}
	if (size <= 0)
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
	if (p.x < 0 || p.y < 0)
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
	for (int i = 0; i < RowCount; i++)
	{
		for (int j = 0; j < ColCount; j++)
		{
			int size = group->GetBlocks().size();
			for (auto var : group->GetBlocks())
			{
				int col = var.col + j;
				int row = var.row + i;
				if (isExistBlock(row, col) || isOutofGrid(row, col))
				{
					break;
				}
				else
				{
					size--;
				}
			}
			if (size == 0)
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
	if (block.sprite->getParent())
	{
		block.sprite->removeFromParentAndCleanup(false);
	}
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
void DragModeGameWidget::Restart()
{
	for (auto var : m_vecBlocks)
	{
		var.sprite->removeFromParentAndCleanup(1);
	}
	m_vecBlocks.clear();

	for (auto var : m_vecReadBlocks)
	{
		var->sprite->removeFromParentAndCleanup(1);
	}
	m_vecReadBlocks.clear();

	m_gameTouchType = Touch_Normal;
	RestReadGroup();
}

//技能
bool DragModeGameWidget::FillBlock(Vec2 pos)
{
	int row = -1;
	int col = -1;
	getGridxy(pos, row, col);
	if (isExistBlock(row, col))
	{
		return false;
	}

	BlockObject ob;
	ob.index = -1;
	ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(8);
	ob.col = col;
	ob.row = row;
	addBlock(ob.row, ob.col, ob);
	//检查是否消除
	ReleaseBlocksOnFullLine();
	return true;
}
bool DragModeGameWidget::KnockBlock(Vec2 pos)
{
	int row = -1;
	int col = -1;
	getGridxy(pos, row, col);
	for (auto iter = m_vecBlocks.begin(); iter != m_vecBlocks.end(); iter++)
	{
		if (iter->col == col&&iter->row == row)
		{
			iter->sprite->removeFromParentAndCleanup(1);
			m_vecBlocks.erase(iter);
			m_gameTouchType = Touch_Normal;
			return true;
		}
	}
	return false;
}