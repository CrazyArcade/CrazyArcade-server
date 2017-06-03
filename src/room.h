#ifndef SERVER_ROOM_H
#define SERVER_ROOM_H

#include <cstdint>
#include "src/utils/objectid.h"
#include "src/utils/log.h"
#include "src/model/player.h"
#include "src/model/bubble.h"
#include "src/model/map.h"
#include <unordered_map>
#include <memory>

class Room {
public:
    static Room *getInstance() {
        static Room INSTANCE;
        INSTANCE.gameStatus = Status::PENDING;
        return &INSTANCE;
    }

    std::shared_ptr<Map> map;
    std::unordered_map<objectID, std::shared_ptr<Player>> playerList;
    std::unordered_map<objectID, std::shared_ptr<Bubble>> bubbleList;

    enum class Status : uint8_t {
        // wait player coming
                WAITING,
        // game starts, but some players is still loading.
                PENDING,
        // game starts
                START,
        // game over
                OVER
    };

    Room(Room const &) = delete;

    void operator=(Room const &) = delete;

    void setMap(const char *mapName) {
        setMap(std::string{mapName});
    }

    void setMap(const std::string &mapName) {
        try {
            map = std::make_shared<Map>(mapName);
            maxPlayer = currentPlayer = map->getMaxPlayer();
        } catch (std::invalid_argument e) {
            LOG_ERROR << mapName << " not found!";
            exit(1);
        }
    }

    std::shared_ptr<Player> onPlayerJoin();

    void onPlayerLeave(const objectID &id);

    void onPlayerPosChange(const objectID &id, int x, int y);

    std::shared_ptr<Bubble> onPlayerSetBubble(const objectID &playerID);

    void onPlayerStatusChange(std::shared_ptr<Player> player, Player::Status status);


    void gameLoop();

private:
    Room() {};
    Status gameStatus;

    int maxPlayer;
    int currentPlayer;

    void bubbleBoom(std::shared_ptr<Bubble> bubble);

};

#endif //SERVER_ROOM_H
