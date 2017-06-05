package com.candy.futon.domain;

import java.util.ArrayList;
import java.util.Collections;

import android.content.Context;

import com.poxiao.ddz.standalone.R;

public class DefaultPlayerGenerator implements IPlayerGenerator {

	private final static String[][] VIRTUAL_PLAYERS = new String[][]{
		{"做女人真无聊","左手戒的爱","醉酒戏红颜","最可爱的笨笨","紫懿菡萏","紫忆丶唯美忧伤",
		"紫星念月","紫欣蝶恋花","紫曦戥咝","紫殇风","紫色的花儿幸福","紫落朵朵","紫魂冰魄龙娃娃","姊、专属某人！",
		"唯美90后浪漫","唯独love晴","唯爱丿杜雷丝之夜灬卿爱",
		"为爱永堕","薇丶寐","微笑秒杀你","玩就要玩的痛快",
		"子轩丶无视一切","追女梦","追风残爱","装深沉扮成熟","转身一夜琉璃白",
		"专属ぅ傻苽の","拽拽小糖果","重走赌城","轾笔写忧伤","至此停留","直爱月",
		"执念染小落","执灬灬著","只想找一个真爱的人","真情颗栋","真的在乎迩","这「伤」谁懂",
		"召钱猫","在这个夏天等你","在爱河的哪一边等你","云中风吹月","缘梦殇",
		"缘De记忆",
		},
		{
		"缘♂梦纸鸢","遇￥赌$就赢","郁闷草儿","雨夜心残","雨夜撕心","羽天之梦","与雨共舞",
		"於约勒幸福","有一种爱叫执着","游曳在天空","游魂逝梦","悠悠兰月亮","幽幽踏江湖",
		"幽灵魔方","永不变痴心","永爱薰衣草","影在未来","尹沫香","翼龙芸","亦惜醉灬红颜",
		"遗弃丶呐断",
		"一梦★●","一颗有毒的糖果","一场烟花口半世谜离","一辈子de永恒","夜醉情",
		"夜丶独倚天伦","野蛮妞儿","野蛮公主","姚玉瑶』","烟雨红尘残梦断","烟羽天迹","血冥之妖艳",
		"许愿花树下的草","许诺爱倪","秀色迷人","悻感卟是鳋o","星星点月","星星的许诺","欣诺程福",
		"心※依然想你","我白俏佳人","唯美那情"		
		}
	};
	
	private final static int[][] VIRTUAL_PLAYER_HEAD_DRAWIDS = new int[][]{
		{R.drawable.head_1, R.drawable.head_3},
		{R.drawable.head_5, R.drawable.head_6}
	};

	public PlayerInfo[]  getTwoVirtualPlayerByGirlIndex(Context context){
		
		PlayerInfo[] playerInfos = new PlayerInfo[2];
		
		ArrayList<PlayerInfo> otherPlayers = new ArrayList<PlayerInfo>();
		for(int i=0;i<2;i++){
			String randomName = VIRTUAL_PLAYERS[i][(int)(VIRTUAL_PLAYERS[i].length *Math.random())];
			int randomHead = VIRTUAL_PLAYER_HEAD_DRAWIDS[i][(int) ((VIRTUAL_PLAYER_HEAD_DRAWIDS[i]).length * Math.random())];
			PlayerInfo temp = PlayerInfo.getRobotPlayerInfoByNickName(context, randomName);
			temp.setHeadDrawId(randomHead);
			temp.setGender(false);
			otherPlayers.add(temp);
			
		}
		Collections.shuffle(otherPlayers);
		
		for(int i=0;i<otherPlayers.size();i++){
			playerInfos[i] = otherPlayers.get(i);
		}
		return playerInfos;
	}
	

	

	

}
