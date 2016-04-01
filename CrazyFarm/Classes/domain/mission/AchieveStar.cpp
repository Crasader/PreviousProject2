#include "AchieveCell.h"
#include "AchieveStar.h"
bool AchieveStar::init(){

	for (int i = 0; i < 4;i++)
	{
		auto sp = Sprite::create();
		sp->setAnchorPoint(Point(0.5,0));
		addChild(sp);
		stars.push_back(sp);
	}
	return true;
}


void AchieveStar::setValue(int total, int finished)
{
	int i = 0;
	for (; i < total;i++)
	{
		if (i<=finished-1)
		{
			stars.at(i)->setTexture("star_light_1.png");
		}
		else 
		{
			stars.at(i)->setTexture("star_frame_1.png");
		}

		if (total-1==i)
		{
			if (total != finished)
			{
				stars.at(total - 1)->setTexture("star_frame_2.png");
			}
			else
			{
				stars.at(total - 1)->setTexture("star_light_2.png");
			}

		}
		
		stars.at(i)->setVisible(true);
	}
	for (; i < 4;i++)
	{
		stars.at(i)->setVisible(false);
	}

	

	switch (total)
	{
	case 1:
		stars.at(0)->setPosition(72, 0);
		break;
	case 2:
		stars.at(0)->setPosition(28, 0);
		stars.at(1)->setPosition(100, 0);
		break;
	case 3:
		stars.at(0)->setPosition(35, 0);
		stars.at(1)->setPosition(72, 0);
		stars.at(2)->setPosition(109, 0);
		break;
	case 4:
		stars.at(0)->setPosition(10, 0);
		stars.at(1)->setPosition(46, 0);
		stars.at(2)->setPosition(82, 0);
		stars.at(3)->setPosition(118, 0);
	default:
		break;
	}


}

