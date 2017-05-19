#include <iostream>
#include "roomController.h"

std::shared_ptr<Player> RoomController::createPlayer() {
    auto player = Player::Factory();
    player->setPosition(APP::Vec2(0, 0));
    this->playerList.insert({player->getObjectID(), player});
    return player;
}

std::shared_ptr<Player> RoomController::getPlayerByObjectID(objectID id) {
    auto find = this->playerList.find(id);
    if (find == this->playerList.end()) {
        return nullptr;
    }
    return find->second;
}

void RoomController::deletePlayerByObjectID(objectID id) {
    this->playerList.erase(id);
}

void RoomController::updatePlayer() {
    for (auto &player : playerList) {
        player.second->update();
    }
}

void RoomController::update() {
    // if (gameStatus != Status::START) return;
    updatePlayer();
}