#include "player.hpp"

/*
"small changes"
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    board = Board();
    this->side = side;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    Side opponentsSide = WHITE;
    if(side == WHITE)
    {
        opponentsSide = BLACK;
    }
    board.doMove(opponentsMove, opponentsSide);
    if (board.hasMoves(side) == false)
    {
        return nullptr;
    }
    
    //Move *move = randomMove(); //make random move
    //Move *move = Heuristic(); //make move to beat SimplePlayer
    Move *move = MiniMax(side, 2); //make minimax move

    if(move == nullptr)
    {
        std::cerr << "nullptr" << std::endl;
        return nullptr;
    }
    std::cerr << "move is (" << move->getX() << ", " << move->getY() << ")" << std::endl;
    
    board.doMove(move, side);
    
    return move;

    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
}

Move *Player::randomMove() {
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Move *move = new Move(i, j);
            if(board.checkMove(move, side))
            {
                return move;
            }
        }
    }
    return nullptr;
}

Move *Player::Heuristic() {
    Move *Bestmove;
    bool canReturn = false;
    int BestMoveCount = board.countBlack()-board.countWhite();
    int curCount;
    if (side == WHITE)
    {
        BestMoveCount *= -1;
    }
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Move *move = new Move(i, j);
            if(board.checkMove(move, side))
            {
                Board tempBoard = board;
                tempBoard.doMove(move, side);
                curCount = tempBoard.countBlack()-tempBoard.countWhite();
                if (side == WHITE)
                {
                    curCount *=-1;
                }

                /*
                if ((j==7||j==0)||(i==7||i==0))
                {
                    curCount += 5;
                }
                */

                if (((j==7||j==0)&&(i==1||i==6))||((i==7||i==0)&&(j==1||j==6)))
                {
                    curCount -= 20;
                }                
                
                if ((i-j)==7||(i-j)==0||(i-j)==-7)
                {
                    curCount += 20;
                }

                if (curCount > BestMoveCount || canReturn == false)
                {
                    BestMoveCount = curCount;
                    Bestmove = move;
                    canReturn = true;
                }
            }
        }
    }
    if (canReturn)
    {
        return Bestmove;
    }
    return nullptr;
}

Move *Player::MiniMax(Side side, int ply) {
    //Move *Bestmove;
    std::vector<Move*> possibleMoves;
    std::vector<int> mins;
    Side oSide = WHITE;
    bool canReturn = false;
    if(side == WHITE)
    {
        oSide = BLACK;
    }
    
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Move *move = new Move(i, j);
            if(board.checkMove(move, side))
            {
                possibleMoves.push_back(move);
                canReturn = true;
            }
        }
    }

    for(size_t n = 0; n < possibleMoves.size(); n++)
    {
        Board tempBoard = board;
        tempBoard.doMove(possibleMoves[n], side);
        int min = 100000;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                Move *move = new Move(i, j);
                if(tempBoard.checkMove(move, oSide))
                {
                    tempBoard.doMove(move, oSide);
                    int curCount = tempBoard.countBlack()-tempBoard.countWhite();
                    if (side == WHITE)
                    {
                        curCount *= -1;
                    }
                    if (curCount < min)
                    {
                        min = curCount;
                    }
                }
            }
        }
        mins.push_back(min);
    }

    std::cerr<<std::endl;
    
    int max_move = -100000;
    int max_index = 0;
    for(size_t n = 0; n < possibleMoves.size(); n++)
    {
        if (mins[n] > max_move)
        {
            max_move = mins[n];
            max_index = n;
        }
    }
    if (canReturn)
    {
        return possibleMoves[max_index];
    }
    return nullptr;
}