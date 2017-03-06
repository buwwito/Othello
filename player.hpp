#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>

using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *randomMove();
    Move *Heuristic();
    Move *MiniMax(Side side, int ply);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board board;
private:
    Side side;
};

#endif
