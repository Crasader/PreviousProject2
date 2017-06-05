package com.candy.futon;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;

import android.app.Activity;
import android.app.Service;
import android.graphics.Color;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.os.Handler;
import android.os.Message;
import android.os.Vibrator;
import android.util.Log;
import android.view.MotionEvent;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;

import com.andy.canvasgame.IGameApplication;
import com.andy.canvasgame.domain.ScheduledExecuteable;
import com.andy.canvasgame.service.GameConstantsService;
import com.andy.canvasgame.service.SoundService;
import com.andy.canvasgame.settings.GameSetting;
import com.andy.canvasgame.ui.AView;
import com.andy.canvasgame.ui.HoverListener;
import com.andy.canvasgame.ui.OnClickListener;
import com.andy.canvasgame.ui.ViewRoot;
import com.andy.canvasgame.util.AViewUtil;
import com.andy.canvasgame.util.BitmapSpliter;
import com.andy.canvasgame.util.MyGravity;
import com.andy.canvasgame.util.ToastUtil;
import com.andy.canvasgame.view.BlankView;
import com.andy.canvasgame.view.ButtonGroupView;
import com.andy.canvasgame.view.RectangleView;
import com.andy.canvasgame.view.TextAView;
import com.andy.pokergames.ddz.ai.ddzai.domain.Bomb80percentCardWasher;
import com.andy.pokergames.ddz.ai.ddzai.domain.CardType;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzAIPlayer;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzRoundInfo;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzTable;
import com.andy.pokergames.ddz.ai.ddzai.domain.DdzTableState;
import com.andy.pokergames.ddz.ai.ddzai.domain.HandCard;
import com.andy.pokergames.ddz.ai.ddzai.domain.ICardWasher;
import com.andy.pokergames.ddz.ai.ddzai.domain.IDdzOutComingEvent;
import com.andy.pokergames.ddz.ai.ddzai.domain.Poker;
import com.andy.pokergames.ddz.ai.ddzai.domain.PokerRank;
import com.andy.pokergames.ddz.ai.ddzai.log.AIEmptyLog;
import com.andy.pokergames.ddz.ai.ddzai.log.ILog;
import com.andy.pokergames.ddz.ai.ddzai.log.LogProxy;
import com.andy.pokergames.ddz.ai.ddzai.uitl.HandCardUtil;
import com.andy.pokergames.ddz.ai.hint.ClickCardHint;
import com.andy.pokergames.ddz.ai.hint.FollowCardHint;
import com.andy.pokergames.ddz.ai.hint.PlayCardHint;
import com.andy.pokergames.ddz.ai.hint.SlingCardHintUtil;
import com.candy.futon.activitys.GameActivity;
import com.candy.futon.ai.log.AIFileLog;
import com.candy.futon.domain.Bomb160percentCardWasher;
import com.candy.futon.domain.Bomb320percentCardWasher;
import com.candy.futon.domain.GameConfig;
import com.candy.futon.domain.GameRoom;
import com.candy.futon.domain.NoBombCardWasher;
import com.candy.futon.domain.PlayerInfo;
import com.candy.futon.domain.PrizePackageType;
import com.candy.futon.service.DownloadService;
import com.candy.futon.service.MarqueeUpdater;
import com.candy.futon.util.BaoxiangUtil;
import com.candy.futon.util.CoinChangeAnimationHelper;
import com.candy.futon.util.FireworkViewHelper;
import com.candy.futon.util.FirstSlingPointerHelper;
import com.candy.futon.util.HandCardSoundHelper;
import com.candy.futon.util.PlayResultPointAnimationHelper;
import com.candy.futon.util.RoundInfoHelper;
import com.candy.futon.util.PlayResultPointAnimationHelper.PlayResultPointAnimationListener;
import com.candy.futon.view.BaoxiangHint;
import com.candy.futon.view.BaoxiangView;
import com.candy.futon.view.BetAndMagView;
import com.candy.futon.view.CardNumberTitle;
import com.candy.futon.view.ClockAView;
import com.candy.futon.view.DdzGameView;
import com.candy.futon.view.ExtraPokerView;
import com.candy.futon.view.GameUIResource;
import com.candy.futon.view.GetPrize1KView;
import com.candy.futon.view.HandPokerView;
import com.candy.futon.view.ImageAView;
import com.candy.futon.view.ImageNumberAView;
import com.candy.futon.view.MarqueeTextAView;
import com.candy.futon.view.NZSView;
import com.candy.futon.view.NiZhenBangView;
import com.candy.futon.view.NinePatchAView;
import com.candy.futon.view.PicButtonView;
import com.candy.futon.view.PlayResultPointImageNumberAView;
import com.candy.futon.view.PlayerPlayedHandCardView;
import com.candy.futon.view.PlayerView;
import com.candy.futon.view.ProgressAView;
import com.candy.futon.view.RemainedPokerNumAView;
import com.candy.futon.view.SelfPlayedHandCardView;
import com.candy.futon.view.ShowHideTopActionButton;
import com.candy.futon.view.SlingPointerButtonGroupView;
import com.candy.futon.view.TopExtraPokerAndActionView;
import com.candy.futon.view.ViewPosition;
import com.candy.futon.view.GetPrize1KView.GetPrize1KViewAnimationFinishListener;
import com.candy.futon.view.HandPokerView.HandPokerChangedListener;
import com.poxiao.ddz.standalone.R;

public class GameEngine {

	private final static String TAG = "GameEngine";
	private Activity mContext;
	private DdzGameView mGameView;
	private Handler mHandler;
	private DdzTable mTable;
	private AtomicBoolean isInited = new AtomicBoolean(false);
	private static GameEngine instance;
	
	private PlayerView playerViewSelf, playerViewPrev, playerViewNext;
	private PicButtonView startBtn, goodStartBtn;
	private ImageAView goodStartImageView, goodStartLabelView;
	
	private BlankView startBtnGroup;
	private ImageNumberAView goodStartNumberView;
	private ImageAView goodStartNumberBgView;
	
	
	
	private HandPokerView handPokerView;
	private ExtraPokerView extraPokerView;
	private TopExtraPokerAndActionView topExtraPokerAndActionView;
	private DdzAIPlayer selfPlayer;
	
	private PicButtonView leftPlayerCallPointView, rightPlayerCallPointView, selfPlayerCallPointView;

	private PicButtonView leftPlayerPassView, rightPlayerPassView, selfPlayerPassView;
	
	
	private PlayerPlayedHandCardView nextPlayerPlayedHandCardView, prevPlayerPlayedHandCardView;
	private SelfPlayedHandCardView selfPlayedHandCardView;
	
	private RemainedPokerNumAView nextPlayerRemainedPokerView, prevPlayerRemainedPokerView;
	
	private TextAView nextPlayerNameView, prevPlayerNameView;
	
	private ClockAView nextPlayerClockView, prevPlayerClockView, currentClockView;
	
	private PicButtonView callZeroBtn, callOneBtn, callTwoBtn, callThreeBtn;
	
	private ButtonGroupView callLoadBtnGroup;
	
	private PicButtonView notFollowBtn, hintBtn, playCardBtn;
	
	private ButtonGroupView playCardBtnGroup;
	
	public final static int TOTAL_SECOND = 20;
	
	private List<HandCard> allPossibleHandCardList;
	
	private int currentHintHandCardIndex = 0;
	
	private PlayerInfo[] playerInfos;
	
	private GameRoom gameRoom = null;
	
	private PicButtonView back2LobbyBtn, settingBtn, qbskBtn, ddzBtn;
	
	private ProgressAView qbskProgress, ddzProgress;
	
	
	private BetAndMagView betView, magView;
	
	private ShowHideTopActionButton showHideTopAreaBtn;
	
	private ImageAView selfCoinView, leftCoinView, rightCoinView;
	
	private ImageNumberAView selfPointView, leftPointView, rightPointView;
	
	private final static long START_VIBRATE_MILLIS = 200;
	
	private boolean firstTime2GameEngine = true;
	
	private Boolean isPlayerWinLast = null;
	
	private SlingPointerButtonGroupView firstSlingPointerGroupView = null;
	
	private ImageAView sling2LeftView = null, sling2RightView = null, slingPointerView = null;
	
	private ImageAView btnHoverLightForBackView, btnHoverLightForSettingView, btnHoverLightForQbsk, btnHoverLightForDdz;
	
	
	
	
	private PicButtonView cardRemainderBtn = null;
	private ImageAView cardRemainderDetailTitle = null;
	private CardNumberTitle[] cardNumberTitles = new CardNumberTitle[PokerRank.values().length - 1];
	private ImageNumberAView[] cardNumberAViews = new ImageNumberAView[PokerRank.values().length - 1];
	private RectangleView[] cardNumberRectangles= new RectangleView[PokerRank.values().length - 1];
	private NinePatchAView cardRemainderBg = null;
	
	private boolean isRocketPossible = true;
	
	
	private NiZhenBangView niZhengBangView;
	
	
	private NZSView nzsView;
	
	
	private ImageAView[] fireworkViews = new ImageAView[NiZhenBangView.FIREWORK_ARCHORS.length];
	
	private GetPrize1KView getPrize1KView;
	
	private PlayResultPointImageNumberAView[] winImageNumberAViews = new PlayResultPointImageNumberAView[3], loseImageNumberAViews  = new PlayResultPointImageNumberAView[3];
	
	private PicButtonView chargeBtn;
	
	private boolean destroyed = false;
	
	private ImageAView cardRemainderCountBgView;
	
	private ImageNumberAView cardRemainderCountView;
	
	private ICardWasher defaultCardWasher;
	
	private ICardWasher goodStartCardWasher;
	
	private ICardWasher buyedGoodStartCardWasher;
	
	private ICardWasher normalCardWasher;
	
	private long lastActionTimeMilli = 0;
	
	
	private MarqueeTextAView marqueeTextView;
	
	private PicButtonView marqueenBg;
	
	private BaoxiangView baoxiangView;
	
	
	private BaoxiangHint baoxiangHint;
	
	public class CountDownScheduledTask extends ScheduledExecuteable{

		public CountDownScheduledTask(){
			this.delayMills = 1000;
		}
		
		private int currentSecond;
		
		@Override
		public void reset(){
			super.reset();
			currentSecond = TOTAL_SECOND;
		}
		
		@Override
		protected void run() {
			Log.d(TAG, "count down run");
			currentSecond -= 1;
			if(currentSecond == 0){
				this.pause();
			}
			onCountDownSecond(currentSecond);
		}
		
		@Override
		public boolean isFinished() {
			return false;
		}
	}
	
	public class FlashGoodStartBtnTask extends ScheduledExecuteable{
		
		private boolean isShow = true;
		
		public FlashGoodStartBtnTask(){
			this.delayMills = 500;
			this.repeatTimes = 100000;
		}

		@Override
		protected void run() {
			if(startBtnGroup.getAlpha() == 0){
				return;
			}
			goodStartImageView.setAlpha(isShow?0:AView.FULL_OPAQUE);
			isShow = !isShow;
			goodStartImageView.invalidate();
		}
		
		@Override
		public boolean isFinished() {
			return false;
		}
		
		
	}
	
	private CountDownScheduledTask countDownScheduledTask = new CountDownScheduledTask();
	
	private FlashGoodStartBtnTask flashGoodStartBtnTask = new FlashGoodStartBtnTask();
	
	private void onCountDownSecond(int currentSecond2) {
		SoundService.getInstance().play(mContext, "stimetick.ogg", true);
		currentClockView.setNumber(currentSecond2);	
		currentClockView.invalidate();
	}
	
	private IDdzOutComingEvent outComingEvent = new IDdzOutComingEvent() {
		
		@Override
		public void waitForPlay(DdzAIPlayer player, HandCard handCard) {
			
			/*
			 * 每次重新出牌的时候清空上次出的牌和不出的泡泡
			 */
			if(mTable.getLastHandCard() == null){
				nextPlayerPlayedHandCardView.setAlpha(0);
				prevPlayerPlayedHandCardView.setAlpha(0);
				selfPlayedHandCardView.setAlpha(0);
				hideAllPopActions();
				mGameView.getViewRoot().invalidate();
			}else{
				PicButtonView actionShowView = getPassViewByPosition(player);
				actionShowView.setAlpha(0);
				actionShowView.invalidate();
			}
			
			if(player == selfPlayer){
				//重置提示牌型
				currentHintHandCardIndex = 0;
				allPossibleHandCardList = null;
				
				Log.d(TAG, mContext.getString(R.string.your_turn_to_play));
				
				if(selfPlayer.getPokerList().size() == 1 && mTable.getLastHandCard() != null && mTable.getLastHandCard().getCardType() != CardType.SINGLE){
					autoPlayLastPoker();
				}else if(selfPlayer.getPokerList().size() <=3 && mTable.getLastHandCard() != null 
						&& mTable.getLastHandCard().getPokers().length > selfPlayer.getPokerList().size() 
						&& !isRocketPossible){
					Message toastMsg = mHandler.obtainMessage(GameActivity.MSG_SHOW_TOAST, mContext.getString(R.string.poker_num_more_than_self_auto_pass));
					toastMsg.sendToTarget();
					Runnable runnable = new Runnable(){
						@Override
						public void run() {
							try {
								Thread.sleep(500);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}
							playOrFollowCard(null, null);
						}
					};
					mGameView.runOnWorkThread(runnable);
				}else{
				
					isPickedPokerCanPlay();
					if(mTable.getLastHandCard() == null){
						notFollowBtn.setDisabled(true);
					}else{
						notFollowBtn.setDisabled(false);
					}
					playCardBtnGroup.setAlpha(AView.FULL_OPAQUE);
					playCardBtnGroup.invalidate();
				}
				if(mTable.getLastHandCard() !=null){
					getAllPossibleHandCardByHint(mTable.getLastHandCard());
					if(allPossibleHandCardList.isEmpty()){
//						Message toastMsg = mHandler.obtainMessage(GameActivity.MSG_SHOW_TOAST, "无更大牌型");
//						toastMsg.sendToTarget();
					}
				}
				
			}
		
			
			//TODO 显示倒计时时钟
			if(player == selfPlayer){
				selfPlayedHandCardView.setAlpha(0);
				selfPlayedHandCardView.invalidate();
				return;
			}
			if(player == mTable.getNextPlayer(selfPlayer)){
				nextPlayerPlayedHandCardView.setAlpha(0);
				nextPlayerClockView.setNumber(TOTAL_SECOND);
				nextPlayerClockView.setAlpha(AView.FULL_OPAQUE);
				nextPlayerPlayedHandCardView.invalidate();
				nextPlayerClockView.invalidate();
				currentClockView = nextPlayerClockView;
				countDownScheduledTask.reset();
				countDownScheduledTask.resume();
				
			}else{
				prevPlayerPlayedHandCardView.setAlpha(0);
				prevPlayerClockView.setNumber(TOTAL_SECOND);
				prevPlayerClockView.setAlpha(AView.FULL_OPAQUE);
				prevPlayerPlayedHandCardView.invalidate();
				prevPlayerClockView.invalidate();
				currentClockView = prevPlayerClockView;
				countDownScheduledTask.reset();
				countDownScheduledTask.resume();
				
				
			}
		}

		
		
		@Override
		public void waitForCallLoad(DdzAIPlayer player) {
			if(player == selfPlayer){
				Log.d(TAG, "轮到自己叫分");
				int childsCount = callLoadBtnGroup.getChildsCount();
				for(int i=0;i<childsCount;i++){
					if(i==0){
						continue;
					}
					PicButtonView btn = (PicButtonView)callLoadBtnGroup.getChilds().get(i);
					if(i<=mTable.getLastCallLoadPoint()){
						
						btn.setDisabled(true);
					}else{
						btn.setDisabled(false);
					}
				}
				callLoadBtnGroup.setAlpha(AView.FULL_OPAQUE);
				callLoadBtnGroup.invalidate();
			}
		}
		
		@Override
		public void roundOver(DdzAIPlayer player) {
			RoundInfoHelper.calcRoundInfo(mContext, mTable, gameRoom, playerInfos, player, selfPlayer);
			showWinLoseAnimation();
			
			
			
			IGameApplication application = (IGameApplication)mContext.getApplication();
			
			if(player == selfPlayer || (!player.isLoad() && !selfPlayer.isLoad())){
				application.playMusic("win.ogg");
				isPlayerWinLast = true;
				
			}else{
				application.playMusic("lose.ogg");
				isPlayerWinLast = false;
			}
			
			DdzAIPlayer nextPlayer = mTable.getNextPlayer(selfPlayer);
			DdzAIPlayer prevPlayer = mTable.getNextPlayer(nextPlayer);
			prevPlayerPlayedHandCardView.setAlpha(AView.FULL_OPAQUE);
			nextPlayerPlayedHandCardView.setAlpha(AView.FULL_OPAQUE);
			if(!nextPlayer.getPokerList().isEmpty()){
				nextPlayerPlayedHandCardView.setPokerList(nextPlayer.getPokerList());
			}
			if(!prevPlayer.getPokerList().isEmpty()){
				prevPlayerPlayedHandCardView.setPokerList(prevPlayer.getPokerList());
			}
			
			
			hideAllPopActions();
			mGameView.getViewRoot().invalidate();
			
			ILog logger = LogProxy.getInstance().getLogger();
			if(logger instanceof AIFileLog){
				AIFileLog aiFileLog = (com.candy.futon.ai.log.AIFileLog)logger;
				aiFileLog.flush2File();
			}
			
			GameConfig.getInstance().addPlayCount();
			GameConfig.getInstance().save(mContext);
			
			
			mHandler.sendEmptyMessage(GameActivity.MSG_ON_ROUND_OVER);
			
			int index = GameRoom.getGameRoomIndex(gameRoom);
			if(index == GameRoom.NORMAL_ROOMS.length){
				GameConfig.getInstance().exceedMaxRoom = true;
				GameConfig.getInstance().exploredRoomIndex = index;
				GameConfig.getInstance().save(mContext);
			}
			
			
			if(GameConfig.getInstance().getRemainReceivePrize(mContext) ==0){
				GameConfig.getInstance().baoxiangCount += 1;
				GameConfig.getInstance().lastReceivePrizeWinindex = playerInfos[0].getWin() + playerInfos[0].getLose();
				GameConfig.getInstance().save(mContext);
			}
			
			baoxiangView.updateBounds();
			
			ArrayList<Integer> payDialogIds = new ArrayList<Integer>();
			if(isPlayerWinLast && 
					((IFutonDdzApplication)application).getPlayerInfo().getPoint() >= GameConfig.JIUJI_THREADHOLD && 
					(GameConfig.getInstance().getOneTimePrizeShowed() || GameConfig.getInstance().isPrizeIndexMax())
					){
				//上一把弹出过1000救济这把弹出10元扣费，必须玩家当前银币还大于1000
				GameConfig.getInstance().clearPrizeIndex();
				GameConfig.getInstance().clearOneTimePrizeShowed();
				payDialogIds.add(GameActivity.MSG_SHOW_PAY_10_YUAN);
			}
			if(GameConfig.getInstance().isGoodStartNeedPay()){
				if(!GameConfig.getInstance().giveUserFreeGoodStart || 
						( GameConfig.getInstance().giveUserFreeGoodStart && isPlayerLastWin())
						){
					GameConfig.getInstance().giveUserFreeGoodStart = false;
					GameConfig.getInstance().clearGoodStart();
					GameConfig.getInstance().save(mContext);
					payDialogIds.add(GameActivity.MSG_SHOW_BUY_GOOD_START);
				}
			}
			if(!GameConfig.getInstance().payedUser && GameConfig.getInstance().needCheckPayPer50Round()){
				payDialogIds.add(GameActivity.MSG_SHOW_BEG_FOR_PAY_DIALOG);
			}
			if(GameConfig.getInstance().getRemaindGoodStartCount() <= 0 && isPlayerWinLast != null && !isPlayerLastWin() && GameConfig.getInstance().chargedUser){
				payDialogIds.add(GameActivity.MSG_SHOW_USER_FREE_GOOD_START);
			}
			if(!GameConfig.getInstance().isNotInContinusPrizeMode() && isPlayerLastWin()){
				
				boolean showPrize1K = true;
				if(GameConfig.getInstance().downGameRoomPrize1K){
					GameRoom temp = GameConfig.getInstance().getGameRoomWhenStart((int) playerInfos[0].getPoint());
					if(temp.minPoint > gameRoom.minPoint){
						GameConfig.getInstance().downGameRoomPrize1K = false;
						GameConfig.getInstance().clearPrizeIndex();
						showPrize1K = false;
					}
				}
				if(showPrize1K){
					GameConfig.getInstance().increasePrizeIndex();
					payDialogIds.add(GameActivity.MSG_SHOW_GET_PRIZE_PACKAGE);
				}
				
			}
			
			if(isPlayerWinLast != null && !isPlayerWinLast && !GameConfig.getInstance().firstLoseRevivePayShowed){
				GameConfig.getInstance().showedPay10Yuan = true;
				GameConfig.getInstance().firstLoseRevivePayShowed = true;
				GameConfig.getInstance().save(mContext);
				payDialogIds.add(GameActivity.MSG_SHOW_PAY_WHILE_FIRST_LOSE);
			}
			GameConfig.getInstance().payDialogIds = payDialogIds;
			
			mHandler.sendEmptyMessage(GameActivity.MSG_CHECK_PAY_DIALOG);
		}





		
		
		@Override
		public void playHandCard(DdzAIPlayer player, HandCard handCard) {
			updateCardRemainder();
			if(cardRemainderBg.isOpaque()){
				cardRemainderBg.invalidate();
			}
			
			//TODO 增加女性报牌声音
//			HandCardSoundHelper.playSoundByHandCard(false, mContext, handCard, true);
			HandCardSoundHelper.playEffectByHandCard(mContext, handCard);
			handlePlayOrFollowHandCard(player, handCard);
			
			
			
		}



		protected void playFrameAnimationByHandCard(HandCard handCard) {
			if(handCard == null){
				return;
			}
			
		}

		private void handlePlayOrFollowHandCard(DdzAIPlayer player,
				HandCard handCard) {
			playFrameAnimationByHandCard(handCard);
			/**
			 * 纪录下是否不再可能有火箭
			 */
			
			if(handCard != null && handCard.getCardType() == CardType.ROCKET){
				isRocketPossible = false;
			}else if(handCard != null && handCard.getCardType() == CardType.SINGLE && handCard.getHandCardRank() >= PokerRank.SMALL_JOKER.getRank()){
				isRocketPossible = false;
			}
			
			PicButtonView actionShowView = getPassViewByPosition(player);
			Poker[] pokers = null;
			if(handCard != null){
				pokers = handCard.getPokers();
				if(handCard.getCardType() == CardType.SING_STRAIGHT || handCard.getCardType() == CardType.DUAL_STRAIGHT){
					ArrayList<Poker> pokerList = new ArrayList<Poker>();
					Collections.addAll(pokerList, pokers);
					Collections.reverse(pokerList);
					pokers = pokerList.toArray(new Poker[pokerList.size()]);
				}
			}
			
			if(player == selfPlayer){
				if(handCard == null){
					selfPlayedHandCardView.setPokers(null);
				}else{
					selfPlayedHandCardView.setPokers(pokers);
					selfPlayedHandCardView.setAlpha(AView.FULL_OPAQUE);
				}
				selfPlayedHandCardView.invalidate();
			}else if(player == mTable.getNextPlayer(selfPlayer)){
				countDownScheduledTask.pause();
				countDownScheduledTask.reset();
				
				nextPlayerClockView.setAlpha(0);
				nextPlayerClockView.invalidate();
				if(handCard == null){
					nextPlayerPlayedHandCardView.setPokers(null);
				}else{
					nextPlayerPlayedHandCardView.setPokers(pokers);
					nextPlayerPlayedHandCardView.setAlpha(AView.FULL_OPAQUE);
				}
				nextPlayerPlayedHandCardView.invalidate();
			}else{
				countDownScheduledTask.pause();
				countDownScheduledTask.reset();
				
				prevPlayerClockView.setAlpha(0);
				prevPlayerClockView.invalidate();
				if(handCard == null){
					prevPlayerPlayedHandCardView.setPokers(null);
				}else{
					prevPlayerPlayedHandCardView.setAlpha(AView.FULL_OPAQUE);
					prevPlayerPlayedHandCardView.setPokers(pokers);
				}
				prevPlayerPlayedHandCardView.invalidate();
			}
			if(handCard == null){
				actionShowView.setAlpha(AView.FULL_OPAQUE);
				actionShowView.invalidate();
			}
			if(player == selfPlayer){
				return;
			}
			
			if(player == selfPlayer || handCard == null){
				
			}
			else if(player.getPokerList().size() == 1){
				SoundService.getInstance().play(mContext, "baojing1.ogg", true);
			}else if(player.getPokerList().size() == 2){
				SoundService.getInstance().play(mContext, "baojing2.ogg", true);
			}
			
			if(player == mTable.getNextPlayer(selfPlayer)){
				nextPlayerRemainedPokerView.setNumber(player.getPokerList().size());
				nextPlayerRemainedPokerView.setAlpha(AView.FULL_OPAQUE);
				nextPlayerRemainedPokerView.invalidate();
			}else{
				prevPlayerRemainedPokerView.setNumber(player.getPokerList().size());
				prevPlayerRemainedPokerView.setAlpha(AView.FULL_OPAQUE);
				prevPlayerRemainedPokerView.invalidate();
			}
		}
		
		@Override
		public void onDispatchCard() {
			
			AViewUtil.below(nextPlayerRemainedPokerView, playerViewNext, MyGravity.RIGHT);
			AViewUtil.below(prevPlayerRemainedPokerView, playerViewPrev, MyGravity.LEFT);
			updatePlayerPokerNum();
			
			
			updateNameView();
			updatePointViews();
		}

		private void updatePlayerPokerNum() {
			DdzAIPlayer nextPlayer = mTable.getNextPlayer(selfPlayer);
			DdzAIPlayer prevPlayer = mTable.getNextPlayer(nextPlayer);
			prevPlayerRemainedPokerView.setNumber(prevPlayer.getPokerList().size());
			nextPlayerRemainedPokerView.setNumber(nextPlayer.getPokerList().size());
			
			nextPlayerRemainedPokerView.setAlpha(AView.FULL_OPAQUE);
			prevPlayerRemainedPokerView.setAlpha(AView.FULL_OPAQUE);
			
			prevPlayerRemainedPokerView.invalidate();
			nextPlayerRemainedPokerView.invalidate();
		}
		
		@Override
		public void callLoad(DdzAIPlayer player, int point) {
			PicButtonView actionShowView = getCallPointViewByPosition(player);
			int textDrawId = 0;
			if(point == 3){
				SoundService.getInstance().play(mContext, "Order.ogg", true);
				textDrawId = R.drawable.text_three_point;
			}else if(point == 2){
				SoundService.getInstance().play(mContext, "Order.ogg", true);
				textDrawId = R.drawable.text_two_point;
			}else if(point == 1){
				SoundService.getInstance().play(mContext, "Order.ogg", true);
				textDrawId = R.drawable.text_one_point;
			}else if(point == 0){
				SoundService.getInstance().play(mContext, "NoOrder.ogg", true);
				textDrawId = R.drawable.text_zero_point;
			}
			actionShowView.setTextDrawable(textDrawId);
			actionShowView.setAlpha(AView.FULL_OPAQUE);
			actionShowView.invalidate();
		}

		

		@Override
		public void loadGen(DdzAIPlayer player) {
			updateCardRemainder();
			if(GameConfig.getInstance().isCardRemainderAvaliable()){
				showCardRemainder();
			}
			
			if(GameConfig.getInstance().isCardRemainderAvaliable() && !GameConfig.getInstance().cardRemainderBuyed){
				GameConfig.getInstance().increaseCardRemainderUseCount();
				GameConfig.getInstance().save(mContext);
			}else{
				GameConfig.getInstance().increaseCardRemainderNotPayCount();
			}
			
			hideAllPopActions();
			updatePlayerPokerNum();
			if(player == selfPlayer){
				handPokerView.onPokerListChanged();
			}
			betView.setNumber(mTable.getRoundInfo().getCallLoadPoint() * gameRoom.basePoint);
			magView.setNumber(gameRoom.baseMag);
			if(GameConfig.getInstance().showSlingCardAnimation){
			
				MyGravity.apply(MyGravity.CENTER_VERTICAL|MyGravity.RIGHT, firstSlingPointerGroupView.getBounds().width(), 
						firstSlingPointerGroupView.getBounds().height(), handPokerView.getBounds(), firstSlingPointerGroupView.getBounds());
				firstSlingPointerGroupView.calcButtonBounds();
				firstSlingPointerGroupView.setAlpha(AView.FULL_OPAQUE);
				FirstSlingPointerHelper.startAnimation(firstSlingPointerGroupView, handPokerView);
			}
			mGameView.getViewRoot().invalidate();
		}

		@Override
		public void followHandCard(DdzAIPlayer player, HandCard handCard) {
			if(handCard != null){
				updateCardRemainder();
				if(cardRemainderBg.isOpaque()){
					cardRemainderBg.invalidate();
				}
			}
			//TODO 增加女性报牌声音
			//HandCardSoundHelper.playSoundByHandCard(false, mContext, handCard, true);
			HandCardSoundHelper.playEffectByHandCard(mContext, handCard);
			handlePlayOrFollowHandCard(player, handCard);
		}

		@Override
		public void magChange(int mag) {
			
			updateMagView(mag);
		}
	};
	
	public static GameEngine getInstance(){
		if(instance == null){
			instance = new GameEngine();
		}
		return instance;
	}
	
	protected void showWinLoseAnimation() {
		DdzRoundInfo roundInfo = mTable.getRoundInfo();
		PlayResultPointImageNumberAView[] currentPoints = new PlayResultPointImageNumberAView[3];
		currentPoints[0] = roundInfo.getPlayerPoint() > 0 ? winImageNumberAViews[0] :loseImageNumberAViews[0];
		currentPoints[1] = roundInfo.getRightPlayerPoint() > 0 ? winImageNumberAViews[1]:loseImageNumberAViews[1];
		currentPoints[2] = roundInfo.getLeftPlayerPoint() > 0 ? winImageNumberAViews[2]:loseImageNumberAViews[2];
		
		currentPoints[0].setNumber(roundInfo.getPlayerPoint());
		currentPoints[1].setNumber(roundInfo.getRightPlayerPoint());
		currentPoints[2].setNumber(roundInfo.getLeftPlayerPoint());
		
		MyGravity.apply(MyGravity.BOTTOM|MyGravity.LEFT,
				currentPoints[0].getBounds().width(), currentPoints[0].getBounds().height(), playerViewSelf.getBounds(), currentPoints[0].getBounds());
		MyGravity.apply(MyGravity.BOTTOM|MyGravity.RIGHT,
				currentPoints[1].getBounds().width(), currentPoints[1].getBounds().height(), playerViewNext.getBounds(), currentPoints[1].getBounds());
		MyGravity.apply(MyGravity.BOTTOM|MyGravity.LEFT,
				currentPoints[2].getBounds().width(), currentPoints[2].getBounds().height(), playerViewPrev.getBounds(), currentPoints[2].getBounds());
		
		for(int i=0;i<currentPoints.length;i++){
			currentPoints[i].setMargin(0, currentPoints[i].getBounds().height(), 0, 0);
		}
		
		PlayResultPointAnimationHelper.startAnimation(currentPoints,  - playerViewSelf.getBounds().height() - currentPoints[0].getBounds().height(), new PlayResultPointAnimationListener() {
			
			@Override
			public void onEnd() {
				updatePointViews();
				doShowStartBtn();
				mGameView.getViewRoot().invalidate();
			}
		});
	}

	protected void updateCardRemainder() {
		Map<PokerRank, Integer> pokerRankCountMap = new HashMap<PokerRank, Integer>();
		for(DdzAIPlayer player:mTable.getPlayers()){
			if(player == selfPlayer){
				continue;
			}
			for(Poker poker:player.getPokerList()){
				Integer count = pokerRankCountMap.get(poker.getPokerRank());
				if(count == null){
					count = 0;
				}
				count += 1;
				pokerRankCountMap.put(poker.getPokerRank(), count);
			}
		}
		for(int i=0;i<cardNumberAViews.length;i++){
			PokerRank pokerRank = PokerRank.values()[PokerRank.values().length - i - 1];
			Integer count = pokerRankCountMap.get(pokerRank);
			if(count == null){
				count = 0;
			}
			if(count == 0){
				cardNumberRectangles[i].setAlpha(AView.FULL_OPAQUE);
			}else{
				cardNumberRectangles[i].setAlpha(0);
			}
			cardNumberAViews[i].changeNumber(count);
		}
	}
	
	protected void clearCardRemainder(){
		for(int i=0;i<cardNumberAViews.length;i++){
			int count = 0;
			cardNumberRectangles[i].setAlpha(AView.FULL_OPAQUE);
			cardNumberAViews[i].changeNumber(count);
		}
	}

	protected void autoPlayLastPoker() {
		if(selfPlayer.getPokerList().size() != 1){
			throw new IllegalArgumentException();
		}
		Poker poker = selfPlayer.getPokerList().get(0);
		HandCard handCard = mTable.getLastHandCard();
		final long autoSleepTime = 1000;
		if(handCard == null || (handCard.getCardType() == CardType.SINGLE && handCard.getHandCardRank() <poker.getRank())){
			final HandCard singleHandCard = new HandCard();
			singleHandCard.setCardType(CardType.SINGLE);
			singleHandCard.setPokers(new Poker[]{poker});
			Runnable runnable = new Runnable(){
				@Override
				public void run() {
					try {
						Thread.sleep(autoSleepTime);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					// TODO Auto-generated method stub
					playOrFollowCard(singleHandCard, selfPlayer.getPokerList());
				}
			};
			mGameView.runOnWorkThread(runnable);
		}else{
			Runnable runnable = new Runnable(){
				@Override
				public void run() {
					try {
						Thread.sleep(autoSleepTime);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					// TODO Auto-generated method stub
					playOrFollowCard(null, null);
				}
			};
			mGameView.runOnWorkThread(runnable);
		}
		
	}

	protected void updateMagView(int mag) {
		magView.setNumber(mag * gameRoom.baseMag);
		magView.invalidate();
	}

	public void init(Activity context, DdzGameView gameView, Handler handler){
		if(mHandler != handler){
			mHandler = handler;
		}
		if(normalCardWasher == null){
			String defaultCardDataFile = GameConstantsService.getInstance().getGameFolderPath() + File.separator + "card.dat";
			normalCardWasher = new Bomb80percentCardWasher(defaultCardDataFile);
			goodStartCardWasher = new Bomb160percentCardWasher(defaultCardDataFile);
			buyedGoodStartCardWasher = new Bomb320percentCardWasher(defaultCardDataFile);
			defaultCardWasher = new NoBombCardWasher(defaultCardDataFile);
		}
		if(!isInited.compareAndSet(false, true)){
			Log.d(TAG, " re init game engine");
			if(this.mContext != context){
				Log.i(TAG, " game engine context changed, rebind");
				this.mContext = context;

			}
			if(this.mGameView != gameView){
				Log.i(TAG, "gameView changed, rebind");
				ViewRoot viewRoot = this.mGameView.getViewRoot();
				this.mGameView = gameView;
				viewRoot.setGameView(mGameView);
				this.mGameView.setViewRoot(viewRoot);
				this.mGameView.addScheduleTask(countDownScheduledTask);
				this.mGameView.addScheduleTask(flashGoodStartBtnTask);
			}
		}else{
			Log.d(TAG," init game engine");
			initViews(context, gameView);
			
		}
		this.drawViews();
		checkAndShowStartBtnOrGameTip();
	}


	private void drawViews(){
		DdzTableState tableState = mTable.getTableState();
		//TODO 根据桌子状态刷新
		this.mGameView.getViewRoot().invalidate();
	}
	
	private PlayerView getPlayerView(DdzAIPlayer player){
		if(player == selfPlayer){
			return playerViewSelf;
		}else if(player == mTable.getNextPlayer(selfPlayer)){
			return playerViewNext;
		}else{
			return playerViewPrev;
		}
	}
	
	private void hideAllPopActions() {
		leftPlayerCallPointView.setAlpha(0);
		rightPlayerCallPointView.setAlpha(0);
		selfPlayerCallPointView.setAlpha(0);
		
		leftPlayerPassView.setAlpha(0);
		rightPlayerPassView.setAlpha(0);
		selfPlayerPassView.setAlpha(0);
	}
	
	private void initViews(Activity context, DdzGameView gameView) {
		if(GameConfig.getInstance().showAILog){
			LogProxy.getInstance(new AIFileLog());
		}else{
			LogProxy.getInstance(new AIEmptyLog());
		}
//		
		this.mContext = context;
		this.mGameView = gameView;
		initDdzTableAndPlayers();
		
		
		handPokerView = new HandPokerView(this.mGameView.getViewRoot(), context, selfPlayer);
		handPokerView.setOnChangeListener(new HandPokerChangedListener(){
			@Override
			public void onChange() {
				isPickedPokerCanPlay();
			}
		});
		initTopActionView(context);
		topActionAreaBtnsUpdatePosition();
		
		mGameView.getViewRoot().setBackground(new BitmapDrawable(context.getResources(), GameUIResource.getInstance().loadBitMap(context.getResources(), R.drawable.game_bg)));
		
		countDownScheduledTask.pause();
		countDownScheduledTask.repeatTimes = 20;
		this.mGameView.addScheduleTask(countDownScheduledTask);
		
		this.mGameView.addScheduleTask(flashGoodStartBtnTask);
		
		this.mGameView.getViewRoot().addChild(handPokerView);
		this.mGameView.getViewRoot().addChild(topExtraPokerAndActionView);
		
		initBetAndMagView();
		
		initRemainedPokerView();
		
		initClockView();
		
		initNameView();
		
		
		initPlayerPlayedHandCardViews();
		
		initPlayCardBtns();
		
		
		initCallLoadBtns();

		initChargeBtn();
		initActionShows();
		
		
		
		initPointView();
		
		initSlingPointerView();
		
		initHoverLightView();
		
		initCardRemainder();
		
		initStartBtn();
		
		initGS_NZB_PRIZE1K_Animations();
		
		for(int i=0;i<winImageNumberAViews.length;i++){
			winImageNumberAViews[i] = new PlayResultPointImageNumberAView(mContext, R.drawable.yellow_num, 10, BitmapSpliter.HORIZONTAL);
			loseImageNumberAViews[i] = new PlayResultPointImageNumberAView(mContext, R.drawable.sliver_blue_num, 10, BitmapSpliter.HORIZONTAL);
			this.mGameView.getViewRoot().addChild(winImageNumberAViews[i]);
			this.mGameView.getViewRoot().addChild(loseImageNumberAViews[i]);
			winImageNumberAViews[i].setAlpha(0);
			loseImageNumberAViews[i].setAlpha(0);
		}
		
		
		
		

		marqueenBg = new PicButtonView(mContext, R.drawable.marquee_bg, -1, new OnClickListener() {
			
			@Override
			public void onClick(AView arg0, MotionEvent arg1) {
				clickBaoxiang();
				
			}

			
		});
		marqueeTextView = new MarqueeTextAView();
		marqueeTextView.setLimitHeight(marqueenBg.getBounds().height());
		marqueeTextView.setText("游戏累计玩5局就送3000银币，还有机会赢实物大奖，点击此处领取奖励");
		
		
		
		
		
		AViewUtil.below(marqueenBg, topExtraPokerAndActionView, MyGravity.CENTER);
		
		marqueeTextView.setLeftRight(marqueenBg.getBounds().left + ViewPosition.getInstance().MARQUEE_BG_PADDING_LEFT,
				marqueenBg.getBounds().right - ViewPosition.getInstance().MARQUEE_BG_PADDING_RIGHT);
		marqueenBg.addChild(marqueeTextView);
		marqueeTextView.setGravity(MyGravity.CENTER);
		mGameView.getViewRoot().addChild(marqueenBg);
		
		
		baoxiangView = new BaoxiangView(mContext, new OnClickListener() {
			
			@Override
			public void onClick(AView arg0, MotionEvent arg1) {
				clickBaoxiang();
			}
		});
		
		mGameView.getViewRoot().addChild(baoxiangView);
		baoxiangView.setGravity(MyGravity.BOTTOM|MyGravity.RIGHT);
		baoxiangView.updateBounds();
		
		
		baoxiangHint = new BaoxiangHint(mContext);
		mGameView.getViewRoot().addChild(baoxiangHint);
		AViewUtil.above(baoxiangHint, baoxiangView, MyGravity.RIGHT);
		
		baoxiangHint.setAlpha(0);
		
		
	}

	private void initChargeBtn() {
		chargeBtn = new PicButtonView(mContext, R.drawable.charge_btn_bg, R.drawable.charge_btn, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				mHandler.sendEmptyMessage(GameActivity.MSG_SHOW_CHARGE_DIALOG);
			}
		});
		
		
		
		mGameView.getViewRoot().addChild(chargeBtn);
		AViewUtil.toRightOf(chargeBtn, playerViewSelf, mGameView.getViewRoot());
		chargeBtn.setMargin(0, 0, 0, playerViewSelf.getBounds().height());
		if(GameConfig.getInstance().noCharge){
			chargeBtn.setAlpha(0);
		}
	}
	
	private void clickBaoxiang() {
		if(BaoxiangUtil.useBaoXiang(mContext)){
			mHandler.sendEmptyMessage(GameActivity.MSG_SHOW_TASK_REWARD_AND_INPUT_CELL_PHONE);
			baoxiangView.updateBounds();
		}else{
			
			baoxiangHint.setHintStr("再玩"+GameConfig.getInstance().getRemainReceivePrize(mContext)+"盘获得神秘奖励哦～");
			
		}
	}

	/**
	 * 高手，你真棒，1千礼包动画
	 */
	protected void initGS_NZB_PRIZE1K_Animations() {
		niZhengBangView = new NiZhenBangView(mContext);
		this.mGameView.getViewRoot().addChild(niZhengBangView);
		niZhengBangView.setGravity(MyGravity.CENTER_HORIZONTAL|MyGravity.BOTTOM);
		niZhengBangView.setMargin(0, 0, 0, NiZhenBangView.MARGIN_BOTTOM);
		niZhengBangView.updateBounds();
		niZhengBangView.setAlpha(0);
		
		
		
		
		
		getPrize1KView = new GetPrize1KView(mContext, mGameView.getViewRoot(), playerViewSelf.getBounds());
		mGameView.getViewRoot().addChild(getPrize1KView);
		getPrize1KView.setGravity(MyGravity.CENTER_HORIZONTAL|MyGravity.BOTTOM);
		getPrize1KView.setMargin(0, 0, 0, GetPrize1KView.MARGIN_BOTTOM);
		getPrize1KView.updateBounds();
		getPrize1KView.setAlpha(0);
		
		
		nzsView = new NZSView(mContext);
		mGameView.getViewRoot().addChild(nzsView);
		nzsView.setGravity(MyGravity.CENTER_HORIZONTAL|MyGravity.BOTTOM);
		nzsView.setMargin(0, 0, 0, NZSView.MARGIN_BOTTOM);
		nzsView.updateBounds();
		nzsView.setAlpha(0);
		
		
		
		int j= 0;
		for(int i=0;i<fireworkViews.length;i++){
			if(j>= FireworkViewHelper.FIRE_WORK_DRAW_ID.length){
				j = 0;
			}
			fireworkViews[i] = new ImageAView(mContext, FireworkViewHelper.FIRE_WORK_DRAW_ID[j]);
			j += 1;
			mGameView.getViewRoot().addChild(fireworkViews[i]);
			fireworkViews[i].setAlpha(0);
		}
	}

	protected void initTopActionView(Activity context) {
		topExtraPokerAndActionView = new TopExtraPokerAndActionView(context, this.mGameView.getViewRoot());
		settingBtn = new PicButtonView(context, R.drawable.setting_in_game, 0, new OnClickListener() {
			
			@Override
			public void onClick(AView v , MotionEvent e) {
				mHandler.sendEmptyMessage(GameActivity.MSG_SHOW_SETTING);
			}
		});
		back2LobbyBtn = new PicButtonView(context, R.drawable.back, 0, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				onBack2Lobby();
				
			}
		});
		
		settingBtn.setHoverListener(new HoverListener() {
			
			@Override
			public void onHover(boolean isHovered) {
				if(isHovered){
					btnHoverLightForSettingView.setAlpha(AView.FULL_OPAQUE);
				}else{
					btnHoverLightForSettingView.setAlpha(0);
				}
				btnHoverLightForSettingView.invalidate();
			}
		});
		
		back2LobbyBtn.setHoverListener(new HoverListener() {
			
			@Override
			public void onHover(boolean isHovered) {
				if(isHovered){
					btnHoverLightForBackView.setAlpha(AView.FULL_OPAQUE);
				}else{
					btnHoverLightForBackView.setAlpha(0);
				}
				btnHoverLightForBackView.invalidate();
			}
		});
		
		qbskBtn = new PicButtonView(context, R.drawable.qbsk_icon, 0, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				clickPromoteGame(1);
			}
		});
		
		ddzBtn = new PicButtonView(context, R.drawable.ddz_icon, 0, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				clickPromoteGame(0);
			}
		});
		
		qbskBtn.setHoverListener(new HoverListener() {
			
			@Override
			public void onHover(boolean isHovered) {
				if(isHovered){
					btnHoverLightForQbsk.setAlpha(AView.FULL_OPAQUE);
				}else{
					btnHoverLightForQbsk.setAlpha(0);
				}
				btnHoverLightForQbsk.invalidate();
			}
		});
		
		ddzBtn.setHoverListener(new HoverListener() {
			
			@Override
			public void onHover(boolean isHovered) {
				if(isHovered){
					btnHoverLightForDdz.setAlpha(AView.FULL_OPAQUE);
				}else{
					btnHoverLightForDdz.setAlpha(0);
				}
				btnHoverLightForDdz.invalidate();
			}
		});
		
		showHideTopAreaBtn = new ShowHideTopActionButton(context, R.drawable.top_action_area_up, 0, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				if(showHideTopAreaBtn.isShow()){
					topExtraPokerAndActionView.setMargin(0, -TopExtraPokerAndActionView.MARGIN_TOP_WHILE_HIDE, 0, 0);
					showHideTopAreaBtn.setButtonBgDrawable(R.drawable.top_action_area_up);
				}else{
					showHideTopAreaBtn.setButtonBgDrawable(R.drawable.top_action_area_down);
					topExtraPokerAndActionView.setMargin(0, TopExtraPokerAndActionView.MARGIN_TOP_WHILE_HIDE, 0, 0);
				}
				topActionAreaBtnsUpdatePosition();
				mGameView.getViewRoot().invalidate();
			}
		});
		
		
		ddzProgress = new ProgressAView(mContext, R.drawable.download_progress_bg_small, R.drawable.download_progress_small, ddzBtn.getBounds().width());
		qbskProgress = new ProgressAView(mContext, R.drawable.download_progress_bg_small, R.drawable.download_progress_small, qbskBtn.getBounds().width());
		
		ddzProgress.setAlpha(0);
		qbskProgress.setAlpha(0);
		
		extraPokerView = new ExtraPokerView(mContext, mTable);
		topExtraPokerAndActionView.addChild(extraPokerView);
		topExtraPokerAndActionView.addChild(settingBtn);
		topExtraPokerAndActionView.addChild(back2LobbyBtn);
		if(GameConfig.getInstance().noPromote){
			ddzBtn.setAlpha(0);
			qbskBtn.setAlpha(0);
		}
		topExtraPokerAndActionView.addChild(ddzBtn);
		topExtraPokerAndActionView.addChild(qbskBtn);
		topExtraPokerAndActionView.addChild(showHideTopAreaBtn);
		topExtraPokerAndActionView.addChild(ddzProgress);
		topExtraPokerAndActionView.addChild(qbskProgress);
	}
	
	private boolean isStartGameValid(){
		GameConfig.getInstance().payDialogIds = null;
		IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)mContext.getApplication();
		int currentPoint = futonDdzApplication.getPlayerInfo().getPoint();
		if(GameConfig.getInstance().isChargedMoney){
			GameConfig.getInstance().isChargedMoney = false;
			GameConfig.getInstance().changeGameRoom(currentPoint);
		}
		if(!GameConfig.getInstance().exceedMaxRoom && isPlayerWinLast != null){
			int index = GameRoom.getGameRoomIndex(gameRoom);
			
			if(isPlayerLastWin() && !GameConfig.getInstance().exceedMaxRoom){
				index = index + 1;
				GameConfig.getInstance().exploredRoomIndex = index;
				GameConfig.getInstance().save(mContext);
				GameConfig.getInstance().changeGameRoom(currentPoint);
				return true;
			}else if(!isPlayerLastWin()){
				if(!GameConfig.getInstance().firstLoseRevivePayShowed){
					GameConfig.getInstance().showedPay10Yuan = true;
					GameConfig.getInstance().firstLoseRevivePayShowed = true;
					GameConfig.getInstance().save(mContext);
					Message msg = mHandler.obtainMessage(GameActivity.MSG_SHOW_PAY_WHILE_FIRST_LOSE);
					msg.sendToTarget();
					return false;
				}
			}
		}
		
		
		
		/**
		 * 上一把输了，且已经探索完房间，才去检查银币是否足够
		 */
		if(this.isPlayerWinLast != null && !isPlayerWinLast && 
				GameConfig.getInstance().exceedMaxRoom && gameRoom.minPoint > currentPoint
				&& gameRoom.minPoint > GameRoom.NORMAL_ROOMS[0].minPoint
				&& !GameConfig.getInstance().showedPay10Yuan){
			showPay10Yuan(PrizePackageType.NORMAL);
			return false;
		}else if(currentPoint < GameConfig.JIUJI_THREADHOLD && !GameConfig.getInstance().showedPay10Yuan){
			showPay10Yuan(PrizePackageType.NORMAL);
			return false;
		}
		
		if(currentPoint < GameConfig.JIUJI_THREADHOLD){
			GameConfig.getInstance().setOneTimePrizeShowed();
			
			Message msg = mHandler.obtainMessage(GameActivity.MSG_SHOW_GET_PRIZE_PACKAGE);
			msg.sendToTarget();
			return false;
		}
		
		/**
		 * 上一把赢了，且已经探索完房间，检查是否可以升级房间
		 * 如果可以升级，改变房间，否则不改变房间
		 */
		if(this.isPlayerWinLast != null && isPlayerWinLast && 
				GameConfig.getInstance().exceedMaxRoom ){
			GameRoom gameRoom = GameConfig.getInstance().getGameRoomWhenStart(
					currentPoint);
			if(gameRoom.minPoint > GameEngine.getInstance().gameRoom.minPoint){
				GameConfig.getInstance().changeGameRoom(currentPoint);
			}
		}
		
		if(GameConfig.getInstance().isCardRemainderNeedPay()){
			GameConfig.getInstance().clearCardRemainderNotPayCount();
			GameConfig.getInstance().save(mContext);
			Message msg = mHandler.obtainMessage(GameActivity.MSG_BUY_CARD_REMAINDER);
			msg.sendToTarget();
			return false;
		}
		if(!GameConfig.getInstance().firstTimePrize){
			GameConfig.getInstance().firstTimePrize = true;
			GameConfig.getInstance().save(mContext);
			showPay10Yuan(PrizePackageType.KENG_FIRST_TIME);
			return true;
		}
		
		if(isPlayerLastWin() &&!GameConfig.getInstance().firstWin){
			GameConfig.getInstance().firstWin = true;
			GameConfig.getInstance().save(mContext);
			showPay10Yuan(PrizePackageType.KENG_FIRST_WIN);
			return true;
		}
		
		return true;
	}

	private void showPay10Yuan(PrizePackageType prizeType) {
		GameConfig.getInstance().showedPay10Yuan = true;
		
		Message msg = mHandler.obtainMessage(GameActivity.MSG_SHOW_PAY_10_YUAN);
		msg.arg1  = 1;
		msg.obj = prizeType;
		msg.sendToTarget();
	}
	
	protected boolean checkJiuji(){
		IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)mContext.getApplication();
		int currentPoint = futonDdzApplication.getPlayerInfo().getPoint();
		if(currentPoint < GameConfig.JIUJI_THREADHOLD){
			GameConfig.getInstance().setOneTimePrizeShowed();
			
			Message msg = mHandler.obtainMessage(GameActivity.MSG_SHOW_GET_PRIZE_PACKAGE);
			msg.sendToTarget();
			return false;
		}
		return true;
	}

	protected void initStartBtn() {
		startBtn = new PicButtonView(mContext, R.drawable.start_btn_normal, R.drawable.text_normal_start, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				if(GameConfig.getInstance().noCharge){
					if(!checkJiuji()){
						return;
					}
				}else if(!isStartGameValid()){
					return;
				}
				if(GameConfig.getInstance().getRemaindGoodStartCount() <= 0){
					mTable.setCardWasher(defaultCardWasher);
				}else{
					mTable.setCardWasher(normalCardWasher);
				}
				onStartGame();
			}
		});
		goodStartBtn = new PicButtonView(mContext, R.drawable.start_btn_normal, -1, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				if(GameConfig.getInstance().getRemaindGoodStartCount() <= 0){
					mHandler.sendEmptyMessage(GameActivity.MSG_SHOW_BUY_GOOD_START);
					return;
				}
				if(GameConfig.getInstance().noCharge){
					if(!checkJiuji()){
						return;
					}
				}else if(!isStartGameValid()){
					return;
				}
				GameConfig.getInstance().useGoodStart();
				GameConfig.getInstance().save(mContext);
				if(GameConfig.getInstance().buyGoodStart){
					mTable.setCardWasher(buyedGoodStartCardWasher);
				}else{
					mTable.setCardWasher(goodStartCardWasher);
				}
				onStartGame();
			}
		});
		
		startBtnGroup = new BlankView();
		startBtnGroup.setBounds(new Rect(0,0, startBtn.getBounds().width() + ViewPosition.getInstance().START_BTN_GROUP_PADDING + 
				goodStartBtn.getBounds().width(), 
				startBtn.getBounds().height()>goodStartBtn.getBounds().height()?startBtn.getBounds().height():goodStartBtn.getBounds().height()));
		this.mGameView.getViewRoot().addChild(startBtnGroup);
		
		startBtnGroup.setGravity(MyGravity.BOTTOM|MyGravity.CENTER_HORIZONTAL);
		startBtnGroup.setMargin(0, 0, 0, ViewPosition.getInstance().START_BTN_MARGIN_BOTTOM);
		
		startBtnGroup.addChild(startBtn);
		startBtnGroup.addChild(goodStartBtn);
		
		startBtn.setGravity(MyGravity.LEFT|MyGravity.CENTER_VERTICAL);
		goodStartBtn.setGravity(MyGravity.RIGHT |MyGravity.CENTER_VERTICAL);
		
		goodStartImageView = new ImageAView(mContext, R.drawable.start_btn_good);
		goodStartLabelView = new ImageAView(mContext, R.drawable.text_good_start);
		
		goodStartImageView.setBounds(new Rect(goodStartBtn.getBounds()));
		goodStartLabelView.setBounds(new Rect(goodStartBtn.getBounds()));
		
		startBtnGroup.addChild(goodStartImageView);
		startBtnGroup.addChild(goodStartLabelView);
		
		goodStartNumberView = new ImageNumberAView(mContext, R.drawable.good_start_num, 10, BitmapSpliter.HORIZONTAL);
		goodStartNumberBgView = new ImageAView(mContext, R.drawable.good_start_num_bg);
		startBtnGroup.addChild(goodStartNumberBgView);
		startBtnGroup.addChild(goodStartNumberView);
		goodStartNumberBgView.setGravity(MyGravity.RIGHT|MyGravity.BOTTOM);
		updateGoodStartNumber();
	}

	public void updateGoodStartNumber() {
		goodStartNumberView.setNumber(GameConfig.getInstance().getRemaindGoodStartCount());
		MyGravity.apply(MyGravity.CENTER, goodStartNumberView.getBounds().width(), 
				goodStartNumberView.getBounds().height(), goodStartNumberBgView.getBounds(), goodStartNumberView.getBounds());
	}

	

	private void initCardRemainder() {
		this.cardRemainderBtn = new PicButtonView(mContext, R.drawable.card_remainder_title, -1, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				if(!GameConfig.getInstance().isCardRemainderAvaliable()){
					mHandler.sendEmptyMessage(GameActivity.MSG_BUY_CARD_REMAINDER);
				}else{
					if(cardRemainderBg.getAlpha() == 0){
						cardRemainderBg.setAlpha(AView.FULL_OPAQUE);
					}else{
						cardRemainderBg.setAlpha(0);
					}
					cardRemainderBg.invalidate();
				}
			}
		});
		this.cardRemainderBg = new NinePatchAView(mContext, R.drawable.card_remainder_bg);
		
		for(int i = 0;i<cardNumberAViews.length;i++){
			cardNumberAViews[i] = new ImageNumberAView(mContext, R.drawable.white_number, 10, BitmapSpliter.VERTICAL);
			cardNumberAViews[i].setNumber(0);
			
			int index = PokerRank.values().length - 1 -i;
			cardNumberTitles[i] = new CardNumberTitle(mContext, PokerRank.values()[index]);
			
			
			cardNumberRectangles[i] = new RectangleView();
			cardNumberRectangles[i].setColor(Color.argb(153, 150, 150, 150));
			
		}
		ButtonGroupView buttonGroupView = new ButtonGroupView(Arrays.asList(cardNumberTitles), 0, ButtonGroupView.HORIZIONAL);
		this.mGameView.getViewRoot().addChild(cardRemainderBtn);
		cardRemainderBtn.setGravity(MyGravity.BOTTOM|MyGravity.LEFT);
		cardRemainderBtn.setMargin(ViewPosition.getInstance().CARD_REMAINDER_BTN_MARGINX, 0, 0, ViewPosition.getInstance().CARD_REMAINDER_BTN_MARGINY);
		ImageAView cardNumTitle = new ImageAView(mContext, R.drawable.remaind_card_num_text);
		ImageAView pokerTitle = new ImageAView(mContext, R.drawable.card_remainder_poker_title);
		
		cardRemainderBg.setBounds(new Rect(0,0,buttonGroupView.getBounds().width() + ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_LEFT + ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_RIGHT + 
				cardNumTitle.getBounds().width()
				, buttonGroupView.getBounds().height() + ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_TOP
				 + ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_BOTTOM + cardNumTitle.getBounds().height() 
				 +ViewPosition.getInstance().CARD_REMAINDER_BG_EXPANDING_HEIGHT));
		AViewUtil.toRightOf(cardRemainderBg, cardRemainderBtn, mGameView.getViewRoot());
		
		buttonGroupView.setGravity(MyGravity.LEFT|MyGravity.TOP);
		cardRemainderBg.addChild(pokerTitle);
		cardRemainderBg.addChild(cardNumTitle);
		
		
		pokerTitle.setGravity(MyGravity.LEFT|MyGravity.TOP);
		pokerTitle.setMargin(ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_LEFT, 
				ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_TOP, 0, 0);
		
		cardNumTitle.setGravity(MyGravity.LEFT|MyGravity.BOTTOM);
		cardNumTitle.setMargin(ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_LEFT, 0, 0, 
				ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_BOTTOM);
		
		cardRemainderBg.addChild(buttonGroupView);
		buttonGroupView.setGravity(MyGravity.RIGHT|MyGravity.TOP);
		buttonGroupView.setMargin(0, 
				ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_TOP, ViewPosition.getInstance().CARD_REMAINDER_BG_PADDING_RIGHT, 0);

		for(int i=0;i<cardNumberAViews.length;i++){
			cardRemainderBg.addChild(cardNumberAViews[i]);
			AViewUtil.below(cardNumberAViews[i], cardNumberTitles[i], MyGravity.CENTER);
			cardNumberAViews[i].setMargin(0, ViewPosition.getInstance().CARD_REMAINDER_CARD_NUM_MARGIN_TOP,
					0, 0);
			cardNumberRectangles[i].setBounds(new Rect(cardNumberTitles[i].getBounds().left,
					cardNumberTitles[i].getBounds().top - ViewPosition.getInstance().CARD_REMAINDER_CARD_NUM_FG_EXPANDING_TOP,
					cardNumberTitles[i].getBounds().right,
					cardNumberAViews[i].getBounds().bottom + ViewPosition.getInstance().CARD_REMAINDER_CARD_NUM_FG_EXPANDING_BOTTOM));
			cardNumberRectangles[i].setAlpha(0);
			cardRemainderBg.addChild(cardNumberRectangles[i]);
			
		}
		
		mGameView.getViewRoot().addChild(cardRemainderBg);
		
		this.cardRemainderBtn.setAlpha(AView.FULL_OPAQUE);
		this.cardRemainderBg.setAlpha(0);
		
		this.cardRemainderCountBgView = new ImageAView(mContext, R.drawable.card_remainder_count_bg);
		this.cardRemainderCountView = new ImageNumberAView(mContext, R.drawable.card_remainder_count_num, 10, BitmapSpliter.HORIZONTAL);
		
		this.cardRemainderBtn.addChild(cardRemainderCountBgView);
		this.cardRemainderCountBgView.addChild(cardRemainderCountView);
		cardRemainderCountBgView.setGravity(MyGravity.RIGHT|MyGravity.TOP);
		cardRemainderCountBgView.setAlpha(0);
		
		updateCardRemainderCountViews();
	}
	
	private void updateCardRemainderCountViews() {
		if(GameConfig.getInstance().cardRemainderBuyed || !GameConfig.getInstance().isCardRemainderAvaliable()){
			cardRemainderCountBgView.setAlpha(0);
		}else if(GameConfig.getInstance().isCardRemainderAvaliable()){
			cardRemainderCountView.setNumber(GameConfig.getInstance().getCardRemainderFreeCount());
			cardRemainderCountView.setGravity(MyGravity.CENTER);
			cardRemainderCountBgView.setAlpha(AView.FULL_OPAQUE);
			cardRemainderCountBgView.invalidate();
		}
	}

	public void showCardRemainder(){
		if(!GameConfig.getInstance().isCardRemainderAvaliable()){
			this.cardRemainderBg.setAlpha(0);
		}else{
			this.cardRemainderBg.setAlpha(AView.FULL_OPAQUE);
		}
		updateCardRemainderCountViews();
		this.cardRemainderBg.invalidate();
	}

	private void initHoverLightView() {
		this.btnHoverLightForBackView = new ImageAView(mContext, R.drawable.btn_hover_light_2);
		this.btnHoverLightForSettingView = new ImageAView(mContext, R.drawable.btn_hover_light_2);
		this.btnHoverLightForDdz = new ImageAView(mContext, R.drawable.btn_hover_light_2);
		this.btnHoverLightForQbsk  = new ImageAView(mContext, R.drawable.btn_hover_light_2);
		updateHoverLightViewPosition();
		this.mGameView.getViewRoot().addChild(btnHoverLightForBackView);
		this.mGameView.getViewRoot().addChild(btnHoverLightForDdz);
		this.mGameView.getViewRoot().addChild(btnHoverLightForSettingView);
		mGameView.getViewRoot().addChild(btnHoverLightForQbsk);
		this.btnHoverLightForBackView.setAlpha(0);
		this.btnHoverLightForSettingView.setAlpha(0);
		this.btnHoverLightForDdz.setAlpha(0);
		this.btnHoverLightForQbsk.setAlpha(0);
	}

	protected void updateHoverLightViewPosition() {
		if(this.btnHoverLightForBackView == null){
			return;
		}
		MyGravity.apply(MyGravity.CENTER|MyGravity.BOTTOM, this.btnHoverLightForBackView.getBounds().width(), 
				this.btnHoverLightForBackView.getBounds().height(), 
				back2LobbyBtn.getBounds(), btnHoverLightForBackView.getBounds());
		MyGravity.apply(MyGravity.CENTER|MyGravity.BOTTOM, this.btnHoverLightForSettingView.getBounds().width(), 
				this.btnHoverLightForSettingView.getBounds().height(), 
				settingBtn.getBounds(), btnHoverLightForSettingView.getBounds());
		
		MyGravity.apply(MyGravity.CENTER|MyGravity.BOTTOM, this.btnHoverLightForDdz.getBounds().width(), 
				this.btnHoverLightForDdz.getBounds().height(), 
				ddzBtn.getBounds(), btnHoverLightForDdz.getBounds());
		
		MyGravity.apply(MyGravity.CENTER|MyGravity.BOTTOM, this.btnHoverLightForQbsk.getBounds().width(), 
				this.btnHoverLightForQbsk.getBounds().height(), 
				qbskBtn.getBounds(), btnHoverLightForQbsk.getBounds());
	}

	private void initSlingPointerView() {
		if(GameConfig.getInstance().showSlingCardAnimation){
			this.sling2LeftView = new ImageAView(mContext, R.drawable.sling2left);
			this.sling2RightView = new ImageAView(mContext, R.drawable.sling2right);
			this.slingPointerView = new ImageAView(mContext, R.drawable.sling_pointer);
			
			List<AView> buttonList = new ArrayList<AView>();
			buttonList.add(sling2LeftView);
			buttonList.add(slingPointerView);
			buttonList.add(sling2RightView);
			this.firstSlingPointerGroupView = new SlingPointerButtonGroupView(buttonList , 0, ButtonGroupView.HORIZIONAL);
			this.firstSlingPointerGroupView.setGravity(MyGravity.LEFT);
			this.firstSlingPointerGroupView.setHandPokerView(handPokerView);
			firstSlingPointerGroupView.setAlpha(0);
			this.mGameView.getViewRoot().addChild(firstSlingPointerGroupView);
			
		}
	}

	

	private void initNameView() {
		this.nextPlayerNameView = new TextAView();
		this.prevPlayerNameView = new TextAView();
		this.mGameView.getViewRoot().addChild(nextPlayerNameView);
		this.mGameView.getViewRoot().addChild(prevPlayerNameView);
		updateNameView();
	}
	
	private void updateNameView(){
		this.nextPlayerNameView.setText(playerInfos[1].getNickName());
		this.prevPlayerNameView.setText(playerInfos[2].getNickName());
		if(mTable.getTableState() == DdzTableState.WAIT){
			AViewUtil.below(nextPlayerNameView, this.playerViewNext, MyGravity.RIGHT);
			AViewUtil.below(prevPlayerNameView, this.playerViewPrev, MyGravity.LEFT);
		}else{
			nextPlayerNameView.setGravity(MyGravity.RIGHT|MyGravity.TOP);
			AViewUtil.toLeftOf(nextPlayerNameView, nextPlayerRemainedPokerView, this.mGameView.getViewRoot());
			AViewUtil.toRightOf(prevPlayerNameView, prevPlayerRemainedPokerView, this.mGameView.getViewRoot());
		}
	}

	public void onBack2Lobby() {
		String tip = null;
		if(!GameConfig.getInstance().showPromoteWhenQuit && mTable != null && 
				(mTable.getTableState() == DdzTableState.BILL || mTable.getTableState() == DdzTableState.WAIT)){
			mHandler.sendEmptyMessage(GameActivity.MSG_BACK2LOBBY);
			doQuitGame();
			return;
		}
		if(mTable != null && mTable.getTableState() == DdzTableState.BILL || mTable.getTableState() == DdzTableState.WAIT){
			
		}else{
			tip = mContext.getString(R.string.honney);
			tip += mContext.getString(R.string.must_quit_lose)+calcForceQuitLosePoint() + mContext.getString(R.string.coin);
		}
		Message msg = mHandler.obtainMessage(GameActivity.MSG_PROMOTE_QUIT, tip);
		msg.sendToTarget();
	}

	/**
	 * 仅仅是退出游戏的逻辑
	 */
	public void doQuitGame() {
		
		Log.d("GameEngine","call system exit.");
		System.exit(0);
		
	}
	
	/**
	 * 强制退出扣8倍底分
	 * @return
	 */
	private int calcForceQuitLosePoint(){
		int point =  gameRoom.basePoint * 8;
		if(point > playerInfos[0].getPoint()){
			point = playerInfos[0].getPoint();
		}
		return point;
	}

	private PicButtonView getPassViewByPosition(DdzAIPlayer player) {
		
		DdzAIPlayer nextPlayer = null;
		if(player == selfPlayer){
			return selfPlayerPassView;
		}else{
			nextPlayer = mTable.getNextPlayer(selfPlayer);
		}
		if(nextPlayer != null){
			if(nextPlayer == player){
				return rightPlayerPassView;
			}else{
				return leftPlayerPassView;
			}
		}
		throw new IllegalArgumentException();
	}
	
	private PicButtonView getCallPointViewByPosition(DdzAIPlayer player) {
		
		DdzAIPlayer nextPlayer = null;
		if(player == selfPlayer){
			return selfPlayerCallPointView;
		}else{
			nextPlayer = mTable.getNextPlayer(selfPlayer);
		}
		if(nextPlayer != null){
			if(nextPlayer == player){
				return rightPlayerCallPointView;
			}else{
				return leftPlayerCallPointView;
			}
		}
		throw new IllegalArgumentException();
	}
	
	private void initActionShows() {
		
		leftPlayerCallPointView = new PicButtonView(mContext, R.drawable.bubble_left_for_call_point, R.drawable.text_one_point, null);
		rightPlayerCallPointView = new PicButtonView(mContext, R.drawable.bubble_right_for_call_point, R.drawable.text_one_point, null);
		selfPlayerCallPointView = new PicButtonView(mContext, R.drawable.bubble_left_for_call_point, R.drawable.text_one_point, null);
		
		leftPlayerPassView = new PicButtonView(mContext, R.drawable.bubble_left_for_pass, R.drawable.text_pass, null);
		rightPlayerPassView = new PicButtonView(mContext, R.drawable.bubble_right_for_pass, R.drawable.text_pass, null);
		selfPlayerPassView = new PicButtonView(mContext, R.drawable.bubble_left_for_pass, R.drawable.text_pass, null);
		
		
		
		AViewUtil.toLeftOf(rightPlayerCallPointView, playerViewNext.getPlayerBgBounds(), playerViewNext.getGravity(), mGameView.getViewRoot());
		AViewUtil.toRightOf(leftPlayerCallPointView, playerViewPrev.getPlayerBgBounds(), mGameView.getViewRoot());
		AViewUtil.toRightOf(selfPlayerCallPointView, playerViewSelf, mGameView.getViewRoot());
		
		AViewUtil.toLeftOf(rightPlayerPassView, playerViewNext.getPlayerBgBounds(), playerViewNext.getGravity(), mGameView.getViewRoot());
		AViewUtil.toRightOf(leftPlayerPassView, playerViewPrev.getPlayerBgBounds(), mGameView.getViewRoot());
		AViewUtil.toRightOf(selfPlayerPassView, playerViewSelf, mGameView.getViewRoot());
		
		rightPlayerPassView.setMargin(0, 0, ViewPosition.getInstance().ACTION_SHOW_MARGIN_LEFT, 
				ViewPosition.getInstance().PASS_VIEW_MARGIN_BOTTOM);
		leftPlayerPassView.setMargin(ViewPosition.getInstance().ACTION_SHOW_MARGIN_LEFT, 0, 0, 
				ViewPosition.getInstance().PASS_VIEW_MARGIN_BOTTOM);
		selfPlayerPassView.setMargin(ViewPosition.getInstance().ACTION_SHOW_MARGIN_LEFT, 0, 0, 
				ViewPosition.getInstance().PASS_VIEW_MARGIN_BOTTOM);
		
		
		rightPlayerCallPointView.setMargin(0, 0, ViewPosition.getInstance().ACTION_SHOW_MARGIN_LEFT, 
				ViewPosition.getInstance().CALL_LOAD_MARGIN_BOTTOM);
		leftPlayerCallPointView.setMargin(ViewPosition.getInstance().ACTION_SHOW_MARGIN_LEFT, 0, 0, 
				ViewPosition.getInstance().CALL_LOAD_MARGIN_BOTTOM);
		selfPlayerCallPointView.setMargin(ViewPosition.getInstance().ACTION_SHOW_MARGIN_LEFT, 0, 0, 
				ViewPosition.getInstance().CALL_LOAD_MARGIN_BOTTOM);
		
		hideAllPopActions();
		
		mGameView.getViewRoot().addChild(leftPlayerCallPointView);
		mGameView.getViewRoot().addChild(rightPlayerCallPointView);
		mGameView.getViewRoot().addChild(selfPlayerCallPointView);
		
		mGameView.getViewRoot().addChild(leftPlayerPassView);
		mGameView.getViewRoot().addChild(rightPlayerPassView);
		mGameView.getViewRoot().addChild(selfPlayerPassView);
	}

	/**
	 * 在initNameView之后调用
	 */
	private void initPointView() {
		selfCoinView = new ImageAView(mContext, R.drawable.coin_in_game);
		leftCoinView = new ImageAView(mContext, R.drawable.coin_in_game);
		rightCoinView = new ImageAView(mContext, R.drawable.coin_in_game);
		
		this.mGameView.getViewRoot().addChild(selfCoinView);
		this.mGameView.getViewRoot().addChild(leftCoinView);
		this.mGameView.getViewRoot().addChild(rightCoinView);
		
		selfPointView = new ImageNumberAView(mContext, R.drawable.point_number, 10, BitmapSpliter.HORIZONTAL);
		leftPointView = new ImageNumberAView(mContext, R.drawable.point_number, 10, BitmapSpliter.HORIZONTAL);
		rightPointView = new ImageNumberAView(mContext, R.drawable.point_number, 10, BitmapSpliter.HORIZONTAL);
		
		AViewUtil.below(selfCoinView, playerViewSelf, MyGravity.LEFT);
		this.mGameView.getViewRoot().addChild(selfPointView);
		this.mGameView.getViewRoot().addChild(leftPointView);
		this.mGameView.getViewRoot().addChild(rightPointView);
		updatePointViews();
		
		
	}

	private void updatePointViews() {
		
		if(mTable.getTableState() == DdzTableState.WAIT){
			AViewUtil.below(leftCoinView, prevPlayerNameView, MyGravity.LEFT);
			AViewUtil.below(rightCoinView, nextPlayerNameView, MyGravity.RIGHT);
		}else{
			AViewUtil.below(leftCoinView, prevPlayerRemainedPokerView, MyGravity.LEFT);
			AViewUtil.below(rightCoinView, nextPlayerRemainedPokerView, MyGravity.RIGHT);
		}
		selfPointView.setNumber(playerInfos[0].getPoint());
		rightPointView.setNumber(playerInfos[1].getPoint());
		leftPointView.setNumber(playerInfos[2].getPoint());
		
		rightPointView.setGravity(MyGravity.RIGHT | MyGravity.TOP);
		
		AViewUtil.toLeftOf(rightPointView, rightCoinView, mGameView.getViewRoot());
		AViewUtil.toRightOf(selfPointView, selfCoinView, mGameView.getViewRoot());
		AViewUtil.toRightOf(leftPointView, leftCoinView, mGameView.getViewRoot());
		
	}
	
	public void updateTopActionArea(){
		topExtraPokerAndActionView.resetBg(mContext);
		topActionAreaBtnsUpdatePosition();
		mGameView.getViewRoot().invalidate();
	}

	public void topActionAreaBtnsUpdatePosition() {
		showHideTopAreaBtn.setGravity(MyGravity.BOTTOM|MyGravity.CENTER);
		showHideTopAreaBtn.setMargin(0, 0, 0, TopExtraPokerAndActionView.SHOW_HIDE_BUTTON_MARGIN_BOTTOM);
		extraPokerView.setGravity(MyGravity.CENTER_HORIZONTAL|MyGravity.TOP);
		extraPokerView.setMargin(TopExtraPokerAndActionView.EXTRA_POKER_MARGIN_LEFT, TopExtraPokerAndActionView.EXTRA_POKER_MARGIN_TOP, 0, 0);
		
		if(GameConfig.getInstance().noPromote){
			back2LobbyBtn.setGravity(MyGravity.RIGHT|MyGravity.TOP);
			back2LobbyBtn.setMargin(0, TopExtraPokerAndActionView.ACTION_MARGIN_TOP, TopExtraPokerAndActionView.RIGHT_ACTION_MARGIN_RIGHT_WHILE_ONLY_2_ACTION, 0);
			settingBtn.setGravity(MyGravity.LEFT|MyGravity.TOP);
			settingBtn.setMargin(TopExtraPokerAndActionView.LEFT_ACTION_MARGIN_LEFT_WHILE_ONLY_2_ACTION, TopExtraPokerAndActionView.ACTION_MARGIN_TOP, 0, 0);
			qbskBtn.setAlpha(0);
			ddzBtn.setAlpha(0);
			qbskProgress.setAlpha(0);
			ddzProgress.setAlpha(0);
		}else{
		
		
			settingBtn.setGravity(MyGravity.RIGHT|MyGravity.TOP);
			settingBtn.setMargin(0, TopExtraPokerAndActionView.ACTION_MARGIN_TOP, TopExtraPokerAndActionView.RIGHT_ACTION_MARGIN_RIGHT2, 0);
			back2LobbyBtn.setGravity(MyGravity.RIGHT|MyGravity.TOP);
			back2LobbyBtn.setMargin(0, TopExtraPokerAndActionView.ACTION_MARGIN_TOP, TopExtraPokerAndActionView.RIGHT_ACTION_MARGIN_RIGHT, 0);
			ddzBtn.setAlpha(AView.FULL_OPAQUE);
			qbskBtn.setAlpha(AView.FULL_OPAQUE);
			ddzBtn.setGravity(MyGravity.LEFT|MyGravity.TOP);
			ddzBtn.setMargin(TopExtraPokerAndActionView.LEFT_ACTION_MARGIN_LEFT, TopExtraPokerAndActionView.ACTION_MARGIN_TOP, 0, 0);
			qbskBtn.setGravity(MyGravity.LEFT|MyGravity.TOP);
			qbskBtn.setMargin(TopExtraPokerAndActionView.LEFT_ACTION_MARGIN_LEFT2, TopExtraPokerAndActionView.ACTION_MARGIN_TOP, 0, 0);
			
			
			
			AViewUtil.below(qbskProgress, qbskBtn, MyGravity.CENTER);
			AViewUtil.below(ddzProgress, ddzBtn, MyGravity.CENTER);
		
			qbskProgress.setMargin(0, 0, 0, qbskProgress.getBounds().height());
			ddzProgress.setMargin(0, 0, 0, ddzProgress.getBounds().height());
			
			for(int i=0;i<DownloadService.PROMOTE_GAMES.length;i++){
				GamePackageInfo gameInfo = DownloadService.PROMOTE_GAMES[i];
				if(DownloadService.getInstance().isInProgress(gameInfo)){
					this.updateDownloadProgress(gameInfo, DownloadService.getInstance().getCurrentProgress(i));
				}
			}
		}
		updateHoverLightViewPosition();
	}



	private void initBetAndMagView() {
		betView = new BetAndMagView(mContext, R.drawable.bet_point);
		magView = new BetAndMagView(mContext, R.drawable.mag);
		
		betView.setParent(this.mGameView.getViewRoot());
		magView.setParent(this.mGameView.getViewRoot());
		
		betView.setGravity(MyGravity.TOP|MyGravity.LEFT);
		magView.setGravity(MyGravity.RIGHT|MyGravity.TOP);
		
		AViewUtil.below(betView, topExtraPokerAndActionView, MyGravity.LEFT);
		AViewUtil.below(magView, topExtraPokerAndActionView, MyGravity.RIGHT);
		
		betView.setMargin(BetAndMagView.MARGIN_LEFT, BetAndMagView.MARGIN_TOP, 0, 0);
		magView.setMargin(0, BetAndMagView.MARGIN_TOP, BetAndMagView.MARGIN_RIGHT, 0);
		
		this.mGameView.getViewRoot().addChild(betView);
		this.mGameView.getViewRoot().addChild(magView);
	}

	private void initClockView() {
		nextPlayerClockView = new ClockAView(mContext, playerViewNext, mGameView.getViewRoot(), false);
		prevPlayerClockView = new ClockAView(mContext, playerViewPrev, mGameView.getViewRoot(), true);
		this.mGameView.getViewRoot().addChild(nextPlayerClockView);
		this.mGameView.getViewRoot().addChild(prevPlayerClockView);
	}

	private void initRemainedPokerView() {
		nextPlayerRemainedPokerView = new RemainedPokerNumAView(mContext);
		prevPlayerRemainedPokerView = new RemainedPokerNumAView(mContext);
		this.mGameView.getViewRoot().addChild(nextPlayerRemainedPokerView);
		this.mGameView.getViewRoot().addChild(prevPlayerRemainedPokerView);
	}

	private void updateDdzTableAndPlayers(){
		getUpdatePlayerInfo();
		selfPlayer = new DdzAIPlayer(playerInfos[0].getNickName(), 0, true);
		DdzAIPlayer farmer1 = new DdzAIPlayer(playerInfos[1].getNickName(),1,false);
		DdzAIPlayer farmer2 = new DdzAIPlayer(playerInfos[2].getNickName(),2,false);
		DdzAIPlayer players[] = new DdzAIPlayer[]{selfPlayer, farmer1, farmer2};
		mTable.setPlayers(players);
		playerViewSelf.setPlayer(selfPlayer, selfPlayer, playerInfos[0]);
		playerViewNext.setPlayer(farmer1, selfPlayer, playerInfos[1]);
		playerViewPrev.setPlayer(farmer2, selfPlayer, playerInfos[2]);
		handPokerView.setPlayer(selfPlayer);
	}
	
	private void initDdzTableAndPlayers() {
		
		getUpdatePlayerInfo();
		selfPlayer = new DdzAIPlayer(playerInfos[0].getNickName(), 0, true);
		DdzAIPlayer farmer1 = new DdzAIPlayer(playerInfos[1].getNickName(),1,false);
		DdzAIPlayer farmer2 = new DdzAIPlayer(playerInfos[2].getNickName(),2,false);
		DdzAIPlayer players[] = new DdzAIPlayer[]{selfPlayer, farmer1, farmer2};
		mTable = new DdzTable(players);
		mTable.setDdzOutComingEvent(outComingEvent);
		mTable.setSleepTimeMin(1000);
		mTable.setSleepTimeMax(3000);
		mTable.setCardWasher(normalCardWasher);
		playerViewSelf =  new PlayerView(mGameView.getViewRoot(), selfPlayer, selfPlayer, playerInfos[0], mContext);
		playerViewNext = new PlayerView(mGameView.getViewRoot(), farmer1, selfPlayer, playerInfos[1],mContext);
		playerViewPrev = new PlayerView(mGameView.getViewRoot(), farmer2, selfPlayer, playerInfos[2],mContext);
		
		this.mGameView.getViewRoot().addChild(playerViewSelf);
		this.mGameView.getViewRoot().addChild(playerViewNext);
		this.mGameView.getViewRoot().addChild(playerViewPrev);
	}

	protected void showPlayerInfo(PlayerInfo playerInfo, float x, float y) {
		String name = playerInfo.getNickName();
		Message obtainMessage = mHandler.obtainMessage(GameActivity.MSG_SHOW_USER_INFO, name);
		obtainMessage.arg1 = (int)x;
		obtainMessage.arg2 = (int)y;
		mHandler.sendMessage(obtainMessage);
	}

	private void getUpdatePlayerInfo() {
		
		boolean needChange = false;
		if(playerInfos == null){
			needChange = true;
		}else if(playerInfos != null){
			for(int i=1;i<playerInfos.length;i++){
				if(playerInfos[i] != null && playerInfos[i].getPoint() < PlayerInfo.ROBOT_DEFAULT_POINT /2){
					needChange = true;
				}
			}
		}
		
		if(!needChange){
			return;
		}
		
		IFutonDdzApplication application = (IFutonDdzApplication)mContext.getApplication();
		PlayerInfo[] twoPlayers = null;
		twoPlayers = application.getPlayerGenerator().getTwoVirtualPlayerByGirlIndex(mContext);
		playerInfos = new PlayerInfo[]{application.getPlayerInfo(), twoPlayers[0], twoPlayers[1]};
		for(int i=0;i<playerInfos.length;i++){
			Log.d(TAG, playerInfos[i].toString());
		}
		
	}

	private void initPlayerPlayedHandCardViews() {
		nextPlayerPlayedHandCardView = new PlayerPlayedHandCardView(mContext, mGameView.getViewRoot(), PlayerPlayedHandCardView.RIGHT);
		prevPlayerPlayedHandCardView = new PlayerPlayedHandCardView(mContext, mGameView.getViewRoot(), PlayerPlayedHandCardView.LEFT);
		selfPlayedHandCardView = new SelfPlayedHandCardView(mContext);
		
		selfPlayedHandCardView.setAlpha(0);
		nextPlayerPlayedHandCardView.setAlpha(0);
		prevPlayerPlayedHandCardView.setAlpha(0);
		
		this.mGameView.getViewRoot().addChild(nextPlayerPlayedHandCardView);
		this.mGameView.getViewRoot().addChild(prevPlayerPlayedHandCardView);
		this.mGameView.getViewRoot().addChild(selfPlayedHandCardView);
	}

	private void initPlayCardBtns(){
		notFollowBtn = new PicButtonView(mContext, R.drawable.button_normal, R.drawable.text_not_play, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				if(mTable.getLastHandCard() == null){
					ToastUtil.resultNotify(mContext, "轮到你出牌，请出牌");
					return;
				}
				
				handPokerView.rePick();
				playOrFollowCard(null, null);
			}
		});
		
		hintBtn = new PicButtonView(mContext, R.drawable.button_normal, R.drawable.text_hint, new OnClickListener() {
	
			@Override
			public void onClick(AView v, MotionEvent e) {
				doPlayHint();
				
			}
		});
		playCardBtn = new PicButtonView(mContext, R.drawable.button_normal, R.drawable.text_play_card, new OnClickListener() {
	
			@Override
			public void onClick(AView v, MotionEvent e) {
				List<Poker> pickedPokers = handPokerView.getPickedPokers();
				if(pickedPokers.isEmpty()){
					ToastUtil.resultNotify(mContext, "请选择你要出的牌");
					return;
				}
				Log.d(TAG, "pickedPokers:" + pickedPokers);
				final HandCard handCard = HandCardUtil.getHandCardByPokers(pickedPokers, mTable.getLastHandCard());
				if(handCard == null){
					SoundService.getInstance().play(mContext, "sfailout.ogg", true);
					ToastUtil.resultNotify(mContext, "你选择的牌不符合规则，请重选");
					return;
				}
				
				playOrFollowCard(handCard, pickedPokers);
			}
		});
		
		notFollowBtn.setHoverDrawable(R.drawable.button_hover);
		hintBtn.setHoverDrawable(R.drawable.button_hover);
		playCardBtn.setHoverDrawable(R.drawable.button_hover);
		
		notFollowBtn.setDisableDrawable(R.drawable.button_disabled);
		hintBtn.setDisableDrawable(R.drawable.button_disabled);
		playCardBtn.setDisableDrawable(R.drawable.button_disabled);
		
		notFollowBtn.setTextDiableDrawable(R.drawable.text_not_play_disabled);
		hintBtn.setTextDiableDrawable(R.drawable.text_hint_disabled);
		playCardBtn.setTextDiableDrawable(R.drawable.text_play_card_disabled);
		
		ArrayList<AView> buttonList = new ArrayList<AView>();
		buttonList.add(notFollowBtn);
		buttonList.add(hintBtn);
		buttonList.add(playCardBtn);
		playCardBtnGroup = new ButtonGroupView(buttonList, ViewPosition.getInstance().SELF_PLAYER_BUTTONS_PADDING, ButtonGroupView.HORIZIONAL);
		playCardBtnGroup.setAlpha(0);
		this.mGameView.getViewRoot().addChild(playCardBtnGroup);
		playCardBtnGroup.setGravity(MyGravity.BOTTOM|MyGravity.CENTER);
		playCardBtnGroup.setMargin(0, 0, 0, ViewPosition.getInstance().SELF_PLAYER_BUTTONS_MARGIN_BOTTOM);
	}
	
	protected void doPlayHint() {
		HandCard handCard = mTable.getLastHandCard();
		getAllPossibleHandCardByHint(handCard);
		if(allPossibleHandCardList.isEmpty()){
			this.playCardBtn.setDisabled(true);
			this.playCardBtn.invalidate();
			this.handPokerView.rePick();
			playOrFollowCard(null, null);
			return;
		}
		if(currentHintHandCardIndex >= allPossibleHandCardList.size()){
			currentHintHandCardIndex = 0;
		}
		HandCard hintCard = allPossibleHandCardList.get(currentHintHandCardIndex);
		handleHintHandCard(hintCard);
		currentHintHandCardIndex += 1;
		return;
	}

	protected void getAllPossibleHandCardByHint(HandCard handCard) {
		if(allPossibleHandCardList == null){
			if(handCard == null){
				allPossibleHandCardList = PlayCardHint.getAllPossibleHandCardByArray(selfPlayer.getPokerList());
			}else{
				allPossibleHandCardList = FollowCardHint.getAllPossibleHandCard(selfPlayer.getPokerList(), handCard);
			}
		}
	}

	public void clickCardHint(Poker[] clickedPokers){
		HandCard handCard = mTable.getLastHandCard();
		HandCard hintCard = null;
		if(handCard == null){
			hintCard = ClickCardHint.getPlayClickHint(clickedPokers, selfPlayer.getPokerList());
		}else{
			hintCard = ClickCardHint.getFollowClickHint(clickedPokers, selfPlayer.getPokerList(), handCard);
		}
		if(hintCard != null){
			handPokerView.rePick();
			handPokerView.chosePokers(hintCard.getPokers());
		}
	}
	
	public HandCard flingCardHint(List<Poker> flingPokers){
		HandCard handCard = mTable.getLastHandCard();
		HandCard hintCard = null;
		if(handCard == null){
			hintCard = SlingCardHintUtil.getSlingHandCardHint(flingPokers);
		}else{
			hintCard = SlingCardHintUtil.getSlingHandCardHint(flingPokers, handCard);
		}
		return hintCard;
	}
	
	private void handleHintHandCard(HandCard handCard) {
		this.handPokerView.rePick();
		this.handPokerView.chosePokers(handCard.getPokers());
		this.playCardBtn.setDisabled(false);
		this.playCardBtn.invalidate();
	}

	private void initCallLoadBtns() {
		callZeroBtn = new PicButtonView(mContext, R.drawable.button_normal, R.drawable.text_zero_point, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				callLoadBtnGroup.setAlpha(0);
				callLoadBtnGroup.invalidate();
				Runnable runnable = new Runnable(){

					@Override
					public void run() {
						mTable.callLoad(selfPlayer, 0);
					}
				};
				mGameView.runOnWorkThread(runnable);
				
			}
		});
		callOneBtn = new PicButtonView(mContext, R.drawable.button_normal, R.drawable.text_one_point, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				callLoadBtnGroup.setAlpha(0);
				callLoadBtnGroup.invalidate();
				Runnable runnable = new Runnable(){

					@Override
					public void run() {
						mTable.callLoad(selfPlayer, 1);
					}
					
				};
				mGameView.runOnWorkThread(runnable);
				
			}
		});
		
		callTwoBtn = new PicButtonView(mContext, R.drawable.button_normal, R.drawable.text_two_point, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				callLoadBtnGroup.setAlpha(0);
				callLoadBtnGroup.invalidate();
				Runnable runnable = new Runnable(){

					@Override
					public void run() {
						mTable.callLoad(selfPlayer, 2);	
					}
				};
				mGameView.runOnWorkThread(runnable);
			}
		});
		
		callThreeBtn = new PicButtonView(mContext, R.drawable.button_normal, R.drawable.text_three_point, new OnClickListener() {
			
			@Override
			public void onClick(AView v, MotionEvent e) {
				callLoadBtnGroup.setAlpha(0);
				callLoadBtnGroup.invalidate();
				Runnable runnable = new Runnable(){

					@Override
					public void run() {
						mTable.callLoad(selfPlayer, 3);						
					}
					
				};
				mGameView.runOnWorkThread(runnable);
			}
		});
		
		callZeroBtn.setHoverDrawable(R.drawable.button_hover);
		callOneBtn.setHoverDrawable(R.drawable.button_hover);
		callTwoBtn.setHoverDrawable(R.drawable.button_hover);
		callThreeBtn.setHoverDrawable(R.drawable.button_hover);
		
		callZeroBtn.setDisableDrawable(R.drawable.button_disabled);
		callOneBtn.setDisableDrawable(R.drawable.button_disabled);
		callTwoBtn.setDisableDrawable(R.drawable.button_disabled);
		callThreeBtn.setDisableDrawable(R.drawable.button_disabled);
		
		ArrayList<AView> buttonList = new ArrayList<AView>();
		buttonList.add(callZeroBtn);
		buttonList.add(callOneBtn);
		buttonList.add(callTwoBtn);
		buttonList.add(callThreeBtn);
		
		this.callLoadBtnGroup = new ButtonGroupView(buttonList, ViewPosition.getInstance().SELF_PLAYER_BUTTONS_PADDING, ButtonGroupView.HORIZIONAL);
		callLoadBtnGroup.setAlpha(0);
		this.mGameView.getViewRoot().addChild(callLoadBtnGroup);
		callLoadBtnGroup.setGravity(MyGravity.BOTTOM|MyGravity.CENTER);

		callLoadBtnGroup.setMargin(ViewPosition.getInstance().CALL_LOAD_BTNS_MARGIN_LEFT_IN_SMALL_SCREEN, 0, 0, ViewPosition.getInstance().SELF_PLAYER_BUTTONS_MARGIN_BOTTOM);
	}
	
	public void onStartGame(){
		Log.d(TAG, "start game ");
		isRocketPossible = true;
		
		if(!GameConfig.getInstance().isCardRemainderAvaliable()){
			this.cardRemainderBg.setAlpha(0);
		}
		IGameApplication application = (IGameApplication)mContext.getApplication();
		application.playMusic("normal.mp3");
		if(!firstTime2GameEngine){
			updateDdzTableAndPlayers();
			//TODO update game room here
		}else{
			firstTime2GameEngine = false;
		}
		
		checkRoomChange();
		
		GameConfig.getInstance().showedPay10Yuan = false;
		updateCardRemainderCountViews();
		
		
		clearCardRemainder();
		
		
		
		for(int i=0;i<winImageNumberAViews.length;i++){
			winImageNumberAViews[i].setAlpha(0);
			loseImageNumberAViews[i].setAlpha(0);
		}
		
		
		extraPokerView.clearChilds();
		for(int i=1;i<playerInfos.length;i++){
			if(playerInfos[i].getPoint() < gameRoom.minPoint){
				playerInfos[i].setPoint(PlayerInfo.ROBOT_DEFAULT_POINT);
			}
		}
		updatePointViews();
		SoundService.getInstance().play(mContext, "sstart.ogg", true);
		if(GameSetting.getInstance().isEnableVibrate() && !GameSetting.getInstance().isEnableSaveBattery()){
			 Vibrator vib = (Vibrator) mContext.getSystemService(Service.VIBRATOR_SERVICE);
			 vib.vibrate(START_VIBRATE_MILLIS);
		}
		this.handPokerView.rePick();
		startBtnGroup.setAlpha(0);
		mTable.reset();
		
		betView.setNumber(0);
		magView.setNumber(0);
		
		selfPlayedHandCardView.setAlpha(0);
		nextPlayerPlayedHandCardView.setAlpha(0);
		prevPlayerPlayedHandCardView.setAlpha(0);
		nextPlayerRemainedPokerView.setNumber(0);
		prevPlayerRemainedPokerView.setNumber(0);
		mTable.dispatchCard();
		
		handPokerView.onPokerListChanged();
		this.mGameView.getViewRoot().invalidate();
		Runnable runnable = new Runnable() {
			
			@Override
			public void run() {
				mTable.pullTheTrigger();
			}
		};
		this.mGameView.runOnWorkThread(runnable);
		
	}

	private void checkRoomChange() {
		if(isPlayerWinLast != null && GameConfig.getInstance().getRoomChange() != null && GameConfig.getInstance().getRoomChange()[0] != null &&
				GameConfig.getInstance().getRoomChange()[1] != null && GameConfig.getInstance().getRoomChange()[0] != GameConfig.getInstance().getRoomChange()[1]){
			if(isPlayerLastWin() && GameConfig.getInstance().getRoomChange()[0].minPoint < GameConfig.getInstance().getRoomChange()[1].minPoint){
				boolean showFirstGS = Math.random() > 0.5;
				
				niZhengBangView.setRoomChangeParam(true, GameConfig.getInstance().getRoomChange()[0].basePoint, GameConfig.getInstance().getRoomChange()[1].basePoint);
				niZhengBangView.startSelfAnimation();
				
				
			}else if(!isPlayerLastWin() && GameConfig.getInstance().getRoomChange()[0].minPoint > GameConfig.getInstance().getRoomChange()[1].minPoint){
				boolean showNZS = Math.random() > 0.5;
				nzsView.setRoomChangeParam(false, GameConfig.getInstance().getRoomChange()[0].basePoint, GameConfig.getInstance().getRoomChange()[1].basePoint);
				nzsView.startSelfAnimation();
				
				if(!GameConfig.getInstance().getOneTimePrizeShowed()){
					GameConfig.getInstance().downGameRoomPrize1K = true;
					GameConfig.getInstance().clearPrizeIndex();
					GameConfig.getInstance().increasePrizeIndex();
				}
			}
			if(GameConfig.getInstance().downGameRoomPrize1K &&
						GameConfig.getInstance().getRoomChange()[0].minPoint < GameConfig.getInstance().getRoomChange()[1].minPoint){
					GameConfig.getInstance().clearPrizeIndex();
					GameConfig.getInstance().downGameRoomPrize1K = false;
			}
		}
		GameConfig.getInstance().clearRoomChange();
	}
	
	private void isPickedPokerCanPlay() {
		List<Poker> pickedPokers = handPokerView.getPickedPokers();
		if(pickedPokers.isEmpty()){
			playCardBtn.setDisabled(true);
		}else{
			HandCard handCard = HandCardUtil.getHandCardByPokers(pickedPokers, mTable.getLastHandCard());
			if(handCard == null){
				playCardBtn.setDisabled(true);
			}else{
				playCardBtn.setDisabled(false);
			}
		}
		playCardBtn.invalidate();
	}


	private void playOrFollowCard(final HandCard handCard, List<Poker>pickedPokers) {
		playCardBtnGroup.setAlpha(0);
		if(pickedPokers != null){
			handPokerView.playPokers(pickedPokers);
		}
		mGameView.getViewRoot().invalidate();
		Runnable runnable = new Runnable(){

			@Override
			public void run() {
				if(mTable.getLastHandCard() == null){
					mTable.playCard(selfPlayer, handCard);
				}else{
					mTable.followCard(selfPlayer, handCard);
				}
			}
		};
		mGameView.runOnWorkThread(runnable);
	}

	private GameEngine(){
		
	}

	public void setGameRoom(GameRoom gameRoom) {
		this.gameRoom = gameRoom;
	}
	
	public static void destroy(){
		
		if(instance == null){
			return;
		}
		instance.destroyed = true;
		instance.mTable.setDdzOutComingEvent(null);
		instance = null;
	}

	public void forceQuit() {
		if(mTable != null && mTable.getTableState() == DdzTableState.BILL || mTable.getTableState() == DdzTableState.WAIT){
			mHandler.sendEmptyMessage(GameActivity.MSG_BACK2LOBBY);
			destroy();
			doQuitGame();
			return;
		}
		
		int point = calcForceQuitLosePoint();
		playerInfos[0].setPoint(playerInfos[0].getPoint() - point);
		PlayerInfo.savePlayerInfo(mContext, playerInfos[0]);
		
		mHandler.sendEmptyMessage(GameActivity.MSG_BACK2LOBBY);
		destroy();
		doQuitGame();
	}

	public GameRoom getGameRoom() {
		return gameRoom;
	}
	
	public void checkAndShowStartBtnOrGameTip(){
		if(mTable.getTableState() != DdzTableState.WAIT &&mTable.getTableState() != DdzTableState.BILL){
			return;
		}
		mHandler.sendEmptyMessage(GameActivity.MSG_SHOW_START_BTN);
	}
	
	public void doShowStartBtn(){
		if(this.isInited.get()){
			updateGoodStartNumber();
			startBtnGroup.setAlpha(AView.FULL_OPAQUE);
			startBtnGroup.invalidate();
			flashGoodStartBtnTask.reset();
			flashGoodStartBtnTask.resume();
			
		}
	}
	
	public boolean isPlayerLastWin(){
		return this.isPlayerWinLast != null && this.isPlayerWinLast;
	}
	
	public void playGetPrizeAnimation(){
		this.getPrize1KView.startSelfAnimation(fireworkViews, new GetPrize1KViewAnimationFinishListener() {
			
			@Override
			public void onEnd() {
				IFutonDdzApplication application = (IFutonDdzApplication)mContext.getApplication();
				application.addCoin2Hero(-1000, false);
				application.addCoin2Hero(1000, true);
				GameConfig.getInstance().changeGameRoom(application.getPlayerInfo().getPoint());
			}
		});
	}

	public void updateDownloadProgress(GamePackageInfo gameInfo, int progress) {
		if(destroyed || ddzProgress == null || qbskProgress == null){
			return;
		}
		if(gameInfo == GamePackageInfo.DDZ){
			ddzProgress.setAlpha(AView.FULL_OPAQUE);
			ddzProgress.setProgress(progress);
		}else if(gameInfo == GamePackageInfo.ERMJ){
			qbskProgress.setAlpha(AView.FULL_OPAQUE);
			qbskProgress.setProgress(progress);
		}
	}

	public void hideDownloadProgress(GamePackageInfo gameInfo){
		if(destroyed || ddzProgress == null || qbskProgress == null){
			return;
		}
		if(gameInfo == GamePackageInfo.DDZ){
			ddzProgress.setAlpha(0);
			ddzProgress.invalidate();
		}else if(gameInfo == GamePackageInfo.ERMJ){
			qbskProgress.setAlpha(0);
			qbskProgress.invalidate();
		}
		
	}
	
	protected void clickPromoteGame(int index) {
		Message msg = mHandler.obtainMessage(GameActivity.MSG_CHECK_PROMOTE_GAME, index, 0);
		msg.sendToTarget();
		
	}
	
	public void startCoinAnimation(int currentCoin, int deltaCoin){
		CoinChangeAnimationHelper.startAnimation(selfPointView, currentCoin, deltaCoin, new AnimationListener(){

			@Override
			public void onAnimationStart(Animation animation) {
				
			}

			@Override
			public void onAnimationEnd(Animation animation) {
				AViewUtil.toRightOf(selfPointView, selfCoinView, mGameView.getViewRoot());
			}

			@Override
			public void onAnimationRepeat(Animation animation) {
				
			}
			
		});
	}
	
	public void invalidate(){
		this.mGameView.getViewRoot().invalidate();
	}
	
	public PicButtonView getQbskBtn() {
		return qbskBtn;
	}
	
	public Activity getContext() {
		return mContext;
	}
	
	public void updateLastActionTimeMilli() {
		lastActionTimeMilli = System.currentTimeMillis();
	}
	
	public boolean usePauseToolong(int timeMilli){
		if(lastActionTimeMilli <= 0){
			return false;
		}
		if(System.currentTimeMillis() - lastActionTimeMilli > timeMilli){
			updateLastActionTimeMilli();
			return true;
		}
		return false;
	}
	
	public void updateMarquee(){
		String marquee = MarqueeUpdater.getInstance().getMarquee();
		if(marquee != null && marquee.length() != 0){
			this.marqueeTextView.setText(marquee);
			marqueeTextView.setGravity(MyGravity.CENTER);
			invalidate();
		}
		
		
		
	}
}
