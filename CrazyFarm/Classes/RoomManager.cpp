#include "RoomManager.h"

RoomManager* RoomManager::_instance = NULL;

RoomManager::RoomManager(){
    this->init();
}

void RoomManager::init(){
    // TODO
}

RoomManager* RoomManager::getInstance(){
    if(_instance == NULL){
        _instance = new RoomManager();
    }
    return _instance;
}

std::vector<RoomPlayer> RoomManager::initRoomConfig() {
    int userPosition = rand()%2;
    roomPlayers.clear();
    
    for(int i=0;i<4;i++) {
        if(i != userPosition) {
            RoomPlayer player ;
            player.setCoins(200);
            player.setDiamonds(0);
            player.setLevel(2);
            player.setPlayerState(RoomPlayer::PLAYERSTATE_NEW);
            player.setRoomPosition(i);
            player.setMaxTurretLevel(i+1);
            player.setUserName("player_n_20120");
            player.setAiType(0);
            player.setaiLevel(0);
            roomPlayers.push_back(player);
        }
        
    }
    return roomPlayers;
}

std::vector<RoomPlayer> RoomManager::updateRoomConfig() {
    
    int j = 0;
    for(int i=0;i<4;i++) {
        if(i != userPosition) {
            int needUpdate = rand()%100;
            if(roomPlayers.at(j).getPlayerState() == RoomPlayer::PLAYERSTATE_STANDUP) {
                if(needUpdate < 40) {
                    roomPlayers.at(j).setCoins(200);
                    roomPlayers.at(j).setDiamonds(0);
                    roomPlayers.at(j).setLevel(2);
                    roomPlayers.at(j).setPlayerState(RoomPlayer::PLAYERSTATE_NEW);
                    roomPlayers.at(j).setRoomPosition(i);
                    roomPlayers.at(j).setMaxTurretLevel(i+1);
                    roomPlayers.at(j).setUserName("player_u_40140");
                }
            }else {
                if(needUpdate < 10) {
                    roomPlayers.at(j).setCoins(200);
                    roomPlayers.at(j).setDiamonds(0);
                    roomPlayers.at(j).setLevel(2);
                    roomPlayers.at(j).setPlayerState(RoomPlayer::PLAYERSTATE_STANDUP);
                    roomPlayers.at(j).setRoomPosition(i);
                    roomPlayers.at(j).setMaxTurretLevel(i+1);
                    roomPlayers.at(j).setUserName("player_u_40140");
                }else {
                    roomPlayers.at(j).setPlayerState(RoomPlayer::PLAYERSTATE_KEEP);
                }
            }
            j++;
        }
        
    }
    return roomPlayers;
}



