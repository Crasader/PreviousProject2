package com.xiao.fish.domain.fishnet.allnet;

import com.xiao.fish.domain.fishnet.FishingNet;
import com.xiao.fish.game.res.FishGameRes;

public class FishingNet1 extends FishingNet {

	public FishingNet1() {
		super();
		this.netType=1;
		this.width = 173;
		this.height = 163;
		this.fishNetBitmap=FishGameRes.KEY_GAME_NET_1;
	}

}
