#include "DragModeGameWidget.h"
#include "CommonFunction.h"
#include "Block/SpriteManager.h"
#include "utill/AnimationUtil.h"
#include "Sqlite/DBManager.h"
#include "utill/SkillButton.h"
#include "utill/Audio.h"
#include "pay/PxPayMannger.h"
#define kTagBaseSkillButton 80
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
	case Touch_SkillKnock:
	case Touch_SkillFill:
		return true;
	default:
		return false;
	}

}

// 触摸滑动
void DragModeGameWidget::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	switch (m_gameTouchType)
	{
	case Touch_Normal:
	{
		if (!m_nowTouchBlock)
		{
			return;
		}
		auto diffpos = touch->getLocation() - touch->getPreviousLocation();
		m_nowTouchBlock->sprite->setPosition(m_nowTouchBlock->sprite->getPosition() + diffpos);
	}
		break;
	case Touch_SkillKnock:
	case Touch_SkillFill:
	{
		auto diffpos = touch->getLocation() - touch->getPreviousLocation();
		skillSp->setPosition(skillSp->getPosition() + diffpos);
		int row = -1;
		int col = -1;
		auto size = SpriteManager::GetInstance()->GetBlockSprite(1,true)->getContentSize();
		getGridxy(touch->getLocation(), row, col);
		if (m_gameTouchType == Touch_SkillKnock)
		{
			if (row < 2 || row >10 || col < 0 || col > 8)
			{
				rangeSp->setVisible(false);
			}
			else
			{
				rangeSp->setVisible(true);
				rangeSp->setPosition(GridZeroPos + Vec2((row - 1)*size.width, (col+1)*size.height));
			}
		}
		else if (m_gameTouchType == Touch_SkillFill)
		{
			if (col < 0 || col >9)
			{
				rangeSp->setVisible(false);
			}
			else
			{
				rangeSp->setVisible(true);
				rangeSp->setPosition(Vec2(240, GridZeroPos.y +(col + 0.5)*size.height));
			}
		}
	}
		break;
	default:
		break;
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
			switch (m_gameTouchType)
			{
			case Touch_SkillKnock:
				isUseScuess = KnockBlock(endPos, skillSp);
				break;
			case Touch_SkillFill:
				isUseScuess = FillBlock(endPos, skillSp);
				break;
			default:
				break;
			}
			endUsingSkill(isUseScuess);
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
		Audio::getInstance()->playSound(AUDIO_BLOCKCUTLINE);
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
	
		std::function<void(EventCustom* event)> fun = [=](EventCustom*event)
		{
			bool *ispaysucess = (bool*)(event->getUserData());
			CCLOG("pay test event point result = %d", *ispaysucess);
			if (!ispaysucess)
			{
				gameOver();
			}
			else
			{

				Revivi();
			}
		};

		int revivinum = DBManager::GetInstance()->GetSkillNum(83);
		if (revivinum > 0)
		{
			PxPayMannger::getInstance()->LaughPayLayer(5, this, fun);
		}
		else
		{
			PxPayMannger::getInstance()->LaughPayLayer(4, this, fun);
		}
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

Vec2 DragModeGameWidget::getPosByRowAndCol(int row, int col)
{
	return GridZeroPos + Vec2((row + 0.5)*GridSide, (col + 0.5)*GridSide);
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
bool DragModeGameWidget::FillBlock(Vec2 pos, Sprite*sp)
{
	//int row = -1;
	//int col = -1;
	//getGridxy(pos, row, col);
	//if (isExistBlock(row, col))
	//{
	//	return false;
	//}

	//BlockObject ob;
	//ob.index = -1;
	//ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(8);
	//ob.col = col;
	//ob.row = row;
	//addBlock(ob.row, ob.col, ob);
	////检查是否消除
	//ReleaseBlocksOnFullLine();
	//return true;



	int row = -1;
	int col = -1;
	getGridxy(pos, row, col);
	if (col < 0 || col > 9)
	{
		return false;
	}
	std::vector<BlockObject> obs;
	for (int i = 0; i < _boxMaxCol; i++)
	{

		if (!isExistBlock(i, col))
		{
			BlockObject ob;
			ob.index = -1;
			ob.sprite = SpriteManager::GetInstance()->GetBlockSprite(8,true);
			ob.col = col;
			ob.row = i;
			addChild(ob.sprite);
			obs.push_back(ob);
			addBlock(ob.row, ob.col, ob);
			ob.sprite->setVisible(false);
			m_vecBlocks.push_back(ob);
		}
	}
	//action 
	for (int i = 0; i < obs.size(); i++)
	{
		auto flowerBlock = obs.at(i);
		flowerBlock.sprite->runAction(Sequence::createWithTwoActions(DelayTime::create(flowerBlock.row*0.1f + 0.05f), CallFunc::create([=]{
			flowerBlock.sprite->setVisible(true);
			auto ani = Sprite::create();
			ani->setPosition(flowerBlock.sprite->getContentSize() / 2);
			flowerBlock.sprite->addChild(ani);
			ani->runAction(Sequence::createWithTwoActions(AnimationUtil::getInstance()->getAnimate("ani_flower"), RemoveSelf::create()));

		})));
	}
	Audio::getInstance()->playSound(AUDIO_PROPFILL);
	Vec2 startpos = getPosByRowAndCol(0, col);
	Vec2 endPos = getPosByRowAndCol(_boxMaxCol, col);
	auto magicClub = sp;
	magicClub->setPosition(startpos);
	magicClub->runAction(Sequence::create(MoveTo::create(1.0f, endPos), FadeOut::create(0.1f), DelayTime::create(0.3f), CallFunc::create([=]{
		magicClub->removeFromParentAndCleanup(1);
		ReleaseBlocksOnFullLine();

	}), nullptr));
	return true;
}
bool DragModeGameWidget::KnockBlock(Vec2 pos, Sprite*sp)
{
	//int row = -1;
	//int col = -1;
	//getGridxy(pos, row, col);
	//for (auto iter = m_vecBlocks.begin(); iter != m_vecBlocks.end(); iter++)
	//{
	//	if (iter->col == col&&iter->row == row)
	//	{
	//		iter->sprite->removeFromParentAndCleanup(1);
	//		m_vecBlocks.erase(iter);
	//		m_gameTouchType = Touch_Normal;
	//		return true;
	//	}
	//}
	//return false;

	///4*4
	int row = -1;
	int col = -1;
	getGridxy(pos, row, col);
	std::vector<BlockObject> obs;
	for (int i = row-1; i >= row - 2; i--)
	{
		for (int j = col+1; j >= col; j--)
		{
			for (auto iter = m_vecBlocks.begin(); iter != m_vecBlocks.end(); iter++)
			{
				if (iter->col == j&&iter->row == i)
				{
					obs.push_back(*iter);
					m_vecBlocks.erase(iter);
					break;
				}
			}
		}
	}
	if (obs.size() <= 0)
	{
		return false;
	}
	//do action
	//设置旋转点
	sp->setAnchorPoint(Point(0.5, 0.1));
	Audio::getInstance()->playSound(AUDIO_PROPKNOCK);
	sp->runAction(Sequence::create(Spawn::createWithTwoActions(ScaleTo::create(0.25f, 1.5f), RotateTo::create(0.25f, 30)), Spawn::createWithTwoActions(ScaleTo::create(0.5f, 1.0f), RotateTo::create(0.5f, 0)),
		CallFunc::create([=]{
		for (auto var : obs)
		{
			auto ani = Sprite::create();
			ani->runAction(AnimationUtil::getInstance()->getAnimate("ani_scrap"));
			ani->setPosition(var.sprite->getContentSize() / 2);
			var.sprite->addChild(ani);
			var.sprite->runAction(Sequence::createWithTwoActions(DelayTime::create(AnimationUtil::getInstance()->getAnimate("ani_scrap")->getDuration()), RemoveSelf::create(1)));
		}

	}), RemoveSelf::create(1), nullptr
		));
	return true;
}
void DragModeGameWidget::Revivi()
{
	DBManager::GetInstance()->SetSkillNum(83, DBManager::GetInstance()->GetSkillNum(83) - 1);
	//消去方块
	vector<BlockObject>::iterator it;

	for (it = m_vecBlocks.begin(); it != m_vecBlocks.end();)
	{
		if (it->col >4)
		{
			//消去满行的方块
			it->sprite->removeFromParentAndCleanup(true);
			it = m_vecBlocks.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool DragModeGameWidget::beginUsingSkill(int skillid)
{
	auto bt = getParent()->getChildByTag(skillid);
	auto db = DBManager::GetInstance();
	if (db->GetSkillNum(skillid) <= 0)
	{
		int eventid = skillid == 1 ? 6 : 7;
		std::function<void(EventCustom* event)> fun = [=](EventCustom*event)
		{
			bool *ispaysucess = (bool*)(event->getUserData());
			CCLOG("pay test event point result = %d", *ispaysucess);
		};
		PxPayMannger::getInstance()->LaughPayLayer(eventid, this, fun);
		return false;
	}
	if (skillid == 81)
	{
		skillSp = Sprite::createWithSpriteFrameName("hammer.png");
		skillSp->setPosition(bt->getPosition());
		addChild(skillSp, 10);
		rangeSp = Sprite::createWithSpriteFrameName("blockRange.png");
		rangeSp->setScale(2);
		addChild(rangeSp, 9);
		m_gameTouchType = Touch_SkillKnock;
	}
	else
	{
		skillSp = Sprite::createWithSpriteFrameName("skill_2.png");
		skillSp->setPosition(bt->getPosition());
		addChild(skillSp, 10);
		rangeSp = Sprite::createWithSpriteFrameName("fillRange.png");
		rangeSp->setScale(2);
		addChild(rangeSp, 9);
		m_gameTouchType = Touch_SkillFill;
	}


	auto skillframe = Sprite::createWithSpriteFrameName("skillingShade.png");
	skillframe->setPosition(240, 400);
	addChild(skillframe, 20, "skillframe");

	return true;

}

void DragModeGameWidget::endUsingSkill(bool isUsingsecuess)
{
	if (isUsingsecuess)
	{
		switch (m_gameTouchType)
		{
		case Touch_SkillKnock:
			ChangeNumOfSkillButoon(kTagBaseSkillButton + 1, -1);
			DBManager::GetInstance()->SetSkillNum(kTagBaseSkillButton + 1, DBManager::GetInstance()->GetSkillNum(kTagBaseSkillButton + 1) - 1);
			break;
		case Touch_SkillFill:
			ChangeNumOfSkillButoon(kTagBaseSkillButton + 2, -1);
			DBManager::GetInstance()->SetSkillNum(kTagBaseSkillButton + 2, DBManager::GetInstance()->GetSkillNum(kTagBaseSkillButton + 2) - 1);
			break;
		default:
			break;
		}
	}
	m_gameTouchType = Touch_Normal;
	rangeSp->removeFromParentAndCleanup(true);
	if (!isUsingsecuess)
	{
		skillSp->removeFromParentAndCleanup(1);
	}


	getChildByName("skillframe")->removeFromParentAndCleanup(1);

}

void DragModeGameWidget::ChangeNumOfSkillButoon(int skillid, int diffnum)
{
	auto bt = (SkillButton*)(getParent()->getChildByTag(skillid));
	bt->ChangeSkillNum(diffnum);
}

void DragModeGameWidget::gameOver()
{
	Audio::getInstance()->pauseBGM();
	Audio::getInstance()->playSound(AUDIO_GAMEFAILED);
	EventCustom _event(MSG_GAMEOVER);
	int*pScore = new int(m_nScore);
	_event.setUserData(pScore);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&_event);
	CC_SAFE_DELETE(pScore);
}