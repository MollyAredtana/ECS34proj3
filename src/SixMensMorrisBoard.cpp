#include "SixMensMorrisBoard.h" 	  			 	 
#include <cctype>
#include <iostream>
#include <sstream>

CSixMensMorrisBoard::CSixMensMorrisBoard(){
    DTurn = SIX_MENS_MORRIS_PLAYER_R; // 当新设置一个板子的时候,一直以R开始
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS; Index++){ // SixPmensMorrisPlayers = 2
        DUnplacedPieces[Index] = SIX_MENS_MORRIS_PIECES; // setting the pieces 每个人6个
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){// 16
        DPositions[Index] = SIX_MENS_MORRIS_EMPTY;
        DPreviousPositions[Index] = SIX_MENS_MORRIS_EMPTY;
    }
}

CSixMensMorrisBoard::CSixMensMorrisBoard(char turn, const int unplaced[SIX_MENS_MORRIS_PLAYERS], const char positions[SIX_MENS_MORRIS_POSITIONS], const char previous[SIX_MENS_MORRIS_POSITIONS]){
    DTurn = turn; // 在这里给玩家的turn
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS; Index++){
        DUnplacedPieces[Index] = unplaced[Index];
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        DPositions[Index] = positions[Index];
        DPreviousPositions[Index] = previous[Index];
    }
}

bool CSixMensMorrisBoard::MillCreated(char player){
    int PotentialMills[8][3] = {{0x0, 0x1, 0x2},
                                {0x3, 0x4, 0x5},
                                {0xA, 0xB, 0xC},
                                {0xD, 0xE, 0xF},
                                {0x0, 0x6, 0xD},
                                {0x3, 0x7, 0xA},// should be 37A not 37F
                                {0x5, 0x8, 0xC},
                                {0x2, 0x9, 0xF}};
    for(int Index = 0; Index < 8; Index++){
        bool CurrentMill = true;
        bool PastMill = true;
        char CurrentFirst = DPositions[PotentialMills[Index][0]];  //currentfirst = potentialMill[0-7][0]
        // char PastFirst = DPreviousPositions[PotentialMills[Index][0]];
        if(CurrentFirst != player){//if current = past and current = player
            continue; // go back to the for loop
        }
        for(int Inner = 0; Inner < 3; Inner++ ){
            if(player != DPositions[PotentialMills[Index][Inner]]){
                CurrentMill = false;
                break;
            }
            if(player != DPreviousPositions[PotentialMills[Index][Inner]]){
                PastMill = false;
                //std::cout << "past" << PastMill << std::endl;
            }
        }
        //std::cout << "past should be false" << PastMill << std::endl;
        //std::cout << "current should be true" << CurrentMill << std::endl;

        if(CurrentMill and not PastMill){
            return true;
        }
    }
    return false;
}

bool CSixMensMorrisBoard::AdjacentPositions(int from, int to){
    int Adjacents[SIX_MENS_MORRIS_POSITIONS] = {0x0042, 0x0015, 0x0202, 0x0090,
                                                0x002A, 0x0110, 0x2081, 0x0448,
                                                0x1220, 0x8104, 0x0880, 0x5400,
                                                0x0900, 0x4040, 0xA800, 0x4200};
    
    return Adjacents[from] & (1<<to);
}

void CSixMensMorrisBoard::ResetBoard(){
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS; Index++){
        DUnplacedPieces[Index] = SIX_MENS_MORRIS_PIECES;
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        DPositions[Index] = SIX_MENS_MORRIS_EMPTY;
        DPreviousPositions[Index] = SIX_MENS_MORRIS_EMPTY;
    }
}

char CSixMensMorrisBoard::PlayerTurn() const{
    // std::cout << "  this is player turn " << DTurn << std::endl;
    return toupper(DTurn);
}

char CSixMensMorrisBoard::PlayerAtPosition(int position) const{
    // if((0 <= position) and (position <= SIX_MENS_MORRIS_POSITIONS)){
    if((0 <= position) and (position <= SIX_MENS_MORRIS_POSITIONS)){
        return DPositions[position];   
    }
    return '\0';
}

int CSixMensMorrisBoard::UnplacedPieces(char player) const{
    if(SIX_MENS_MORRIS_PLAYER_R == player){
        return DUnplacedPieces[0];
    }
    if(SIX_MENS_MORRIS_PLAYER_W == player){
        return DUnplacedPieces[1]; 
    }
    return -1;
}

bool CSixMensMorrisBoard::GameOver() const{
    
    return DTurn != SIX_MENS_MORRIS_PLAYER_R and DTurn != SIX_MENS_MORRIS_PLAYER_W;
}

std::string CSixMensMorrisBoard::ToString() const{ // no problem inside
    std::stringstream OutStream;
    int CapturedR, CapturedW;    
    CapturedR = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[0];
    CapturedW = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[1];

    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_R){
            CapturedR--;  
             
        }
        else if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_W){
    
            CapturedW--;   
        }
    }
    // still need to figure out how to fix Dturn so it will change by itself
    // OutStream<<(DTurn == SIX_MENS_MORRIS_PLAYER_R ? ">RU:" : " RU:")<<DUnplacedPieces[0]<<" RC:"<<CapturedW<<(DTurn == SIX_MENS_MORRIS_PLAYER_W ? " >WU:" : "  WU:")<<DUnplacedPieces[1]<<" WC:"<<CapturedR<<std::endl;
    OutStream<<(DTurn == SIX_MENS_MORRIS_PLAYER_R ? ">RU:" : " RU:")<<DUnplacedPieces[0]<<" RC:"<<CapturedW<<(DTurn == SIX_MENS_MORRIS_PLAYER_W ? " >WU:" : "  WU:")<<DUnplacedPieces[1]<<" WC:"<<CapturedR<<std::endl;
    OutStream<<DPositions[0x0]<<"---------"<<DPositions[0x1]<<"---------"<<DPositions[0x2]<<"      0---1---2"<<std::endl;
    OutStream<<"|         |         |      | 3-4-5 |"<<std::endl;
    OutStream<<"|         |         |      6-7   8-9"<<std::endl;
    OutStream<<"|    "<<DPositions[0x3]<<"----"<<DPositions[0x4]<<"----"<<DPositions[0x5]<<"    |      | A-B-C |"<<std::endl;
    OutStream<<"|    |         |    |      D---E---F"<<std::endl;
    OutStream<<"|    |         |    |        LEGEND"<<std::endl;
    OutStream<<DPositions[0x6]<<"----"<<DPositions[0x7]<<"         "<<DPositions[0x8]<<"----"<<DPositions[0x9]<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    "<<DPositions[0xA]<<"----"<<DPositions[0xB]<<"----"<<DPositions[0xC]<<"    |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<DPositions[0xD]<<"---------"<<DPositions[0xE]<<"---------"<<DPositions[0xF]<<std::endl;
    
    return OutStream.str();
}

CSixMensMorrisBoard::operator std::string() const{
    std::stringstream OutStream;
    int CapturedR, CapturedW;
    
    CapturedR = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[0];
    CapturedW = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[1];

    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_R){
            CapturedR--;    // removed pieces from R
        }
        else if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_W){
            CapturedW--;   // removed pieces from W
        }
    }
    OutStream<<(DTurn == SIX_MENS_MORRIS_PLAYER_R ? ">RU:" : " RU:")<<DUnplacedPieces[0]<<" RC:"<<CapturedW<<(DTurn == SIX_MENS_MORRIS_PLAYER_W ? " >WU:" : "  WU:")<<DUnplacedPieces[1]<<" WC:"<<CapturedR<<std::endl;
    OutStream<<DPositions[0x0]<<"---------"<<DPositions[0x1]<<"---------"<<DPositions[0x2]<<"      0---1---2"<<std::endl;
    OutStream<<"|         |         |      | 3-4-5 |"<<std::endl;
    OutStream<<"|         |         |      6-7   8-9"<<std::endl;
    OutStream<<"|    "<<DPositions[0x3]<<"----"<<DPositions[0x4]<<"----"<<DPositions[0x5]<<"    |      | A-B-C |"<<std::endl;
    OutStream<<"|    |         |    |      D---E---F"<<std::endl;
    OutStream<<"|    |         |    |        LEGEND"<<std::endl;
    OutStream<<DPositions[0x6]<<"----"<<DPositions[0x7]<<"         "<<DPositions[0x8]<<"----"<<DPositions[0x9]<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    "<<DPositions[0xA]<<"----"<<DPositions[0xB]<<"----"<<DPositions[0xC]<<"    |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<DPositions[0xD]<<"---------"<<DPositions[0xE]<<"---------"<<DPositions[0xF]<<std::endl;
    
    return OutStream.str();
}

bool CSixMensMorrisBoard::Place(char player, int where){  
// it still need to check the previous one, is it equal to the cur one
// since you can't keep placing the same player's pieces
    // bool checkR;
    // bool checkW;
    int R_count = 0; //  count R the pieces on the board
    int W_count = 0; //  count W the pieces on the board
    int R_NoMoves = 0;
    int W_NoMoves = 0;
    int UnplacedIndex = player == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;  //if R, then 0; no, then 1
    if((player == DTurn) and DUnplacedPieces[UnplacedIndex]){    //assume now is someone's turn, and DUnplacedPieces not 0
        if((0 <= where) and (where < SIX_MENS_MORRIS_POSITIONS)){//check the valid position
            if(SIX_MENS_MORRIS_EMPTY == DPositions[where]){ //check if position empty
                for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){ //make the current position as previous position
                    DPreviousPositions[Index] = DPositions[Index];       
                }
                DPositions[where] = player;   //place the piece
                DUnplacedPieces[UnplacedIndex]--;//unplacepiece --
                if ( not CanRemove(DTurn)){
                    DTurn = DTurn == SIX_MENS_MORRIS_PLAYER_R ? SIX_MENS_MORRIS_PLAYER_W : SIX_MENS_MORRIS_PLAYER_R;
                }

                if((UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R) == 0) and (UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W) == 0))
                {
                    for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
                    {
                        if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_R)
                        {
                            R_count++;
                        }
                        if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_W)
                        {
                            W_count++;
                        }
                    }
                    for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
                    {
                        if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_R)
                        {
                            if(!CanMove(DPositions[i], i))
                            {
                                R_NoMoves++;
                            }
                        }
                        else if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_W)
                        {
                            if(!CanMove(DPositions[i], i))
                            {
                                W_NoMoves++;
                            }
                        }
                    }

                    if(R_NoMoves == R_count)
                    {
                        // tolower(DTurn);
                        DTurn = 'w';
                        // std::cout << DTurn << std::endl;
                        GameOver();
                    }
                    else if(W_NoMoves == W_count)
                    {
                        // tolower(DTurn);
                        DTurn = 'r';
                        // std::cout << DTurn << std::endl;
                        GameOver();
                    }
                }
                            return true;
                        }
                    }
                }
    return false;
}

bool CSixMensMorrisBoard::CanRemove(char player){
    // if(GameOver())
    // {
    //     return false;
    // }
    return ((DTurn == player) and MillCreated(DTurn));
}

bool CSixMensMorrisBoard::CanMove(char player, int where){
    // if(GameOver())
    // {
    //     return false;
    // }
    if((SIX_MENS_MORRIS_PLAYER_R == player) or (SIX_MENS_MORRIS_PLAYER_W == player)){
        if((0 <= where) and (where < SIX_MENS_MORRIS_POSITIONS)){
            if(player == DPositions[where]){
                for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){     
                    if(SIX_MENS_MORRIS_EMPTY == (DPositions[Index]) and AdjacentPositions(Index, where)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool CSixMensMorrisBoard::Move(char player, int from, int to){

    int UnplacedIndex = player == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;
    // bool stop = false; //  give command which shows there is no more legal moves
    int R_count = 0; //  count R the pieces on the board
    int W_count = 0; //  count W the pieces on the board
    int R_NoMoves = 0;
    int W_NoMoves = 0;


    if(GameOver())
    {
        return false;
    }

    if((UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R) < 6) and (UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W) < 6))
    {
        for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
        {
            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_R)
            {
                ++R_count;
            }
            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_W)
            {
                ++W_count;
            }
        }
        for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
        {
            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_R)
            {
                if(!CanMove(DPositions[i], i))
                {
                    ++R_NoMoves;
                }
            }
            else if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_W)
            {
                // std::cout << DPositions[i] << "  " << i << std::endl;
                 if(!CanMove(DPositions[i], i))
                {
                    ++W_NoMoves;
                }
            }
        }
        if(R_NoMoves == R_count)
        {
            // tolower(DTurn);
            DTurn = 'w';
            // std::cout << DTurn << std::endl;
            GameOver();
        }
        else if(W_NoMoves == W_count)
        {
            // tolower(DTurn);
            DTurn = 'r';
            // std::cout << DTurn << std::endl;
            GameOver();
        }
    }

    if((player == DTurn) and (0 == DUnplacedPieces[UnplacedIndex])){
        if((0 <= from) and (from < SIX_MENS_MORRIS_POSITIONS)){
            if(player == DPositions[from]){
                if((0 <= to) and (to < SIX_MENS_MORRIS_POSITIONS) and (DPositions[to] == SIX_MENS_MORRIS_EMPTY) and AdjacentPositions(from, to)){
                    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
                        DPreviousPositions[Index] = DPositions[Index];       
                    }
                    DPositions[to] = player;
                    DPositions[from] = SIX_MENS_MORRIS_EMPTY;
                    if(not MillCreated(player)){
                        DTurn = DTurn == SIX_MENS_MORRIS_PLAYER_R ? SIX_MENS_MORRIS_PLAYER_W : SIX_MENS_MORRIS_PLAYER_R;
                    }
                    R_count = 0; //  count R the pieces on the board
                    W_count = 0; //  count W the pieces on the board
                    R_NoMoves = 0;
                    W_NoMoves = 0;

                    if((UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R) < 6) and (UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W) < 6))
                    {
                        for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
                        {
                            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_R)
                            {
                                R_count++;
                            }
                            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_W)
                            {
                                W_count++;
                            }
                        }
                        // std::cout << "------------------------" << std::endl;
                        for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
                        {
                            // std::cout << DPositions[i] << std::endl;
                            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_R)
                            {
                                if(!CanMove(DPositions[i], i))
                                {
                                    R_NoMoves++;
                                }
                            }
                            else if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_W)
                            {
                                if(!CanMove(DPositions[i], i))
                                {
                                    
                                    W_NoMoves++;
                                }
                            }
                        }
                        // std::cout << W_count << "  " << W_NoMoves << std::endl;
                        if(R_NoMoves == R_count)
                        {
                            // tolower(DTurn);
                            DTurn = 'w';
                            GameOver();
                        }
                        else if(W_NoMoves == W_count)
                        {
                            // tolower(DTurn);
                            DTurn = 'r';
                            GameOver();
                        }
                    }
                    return true;
                }
            }
        }
    }

    if((UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R) != 6) and (UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W) != 6))
    {
        for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
        {
            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_R)
            {
                R_count++;
            }
            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_W)
            {
                W_count++;
            }
        }
        for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
        {
            if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_R)
            {
                if(!CanMove(DPositions[i], i))
                {
                    R_NoMoves++;
                }
            }
            else if(DPositions[i] == SIX_MENS_MORRIS_PLAYER_W)
            {
                if(!CanMove(DPositions[i], i))
                {
                    W_NoMoves++;
                }
            }
        }

        if(R_NoMoves == R_count)
        {
            // tolower(DTurn);
            DTurn = 'w';
            GameOver();
        }
        else if(W_NoMoves == W_count)
        {
            // tolower(DTurn);
            DTurn = 'r';
            GameOver();
        }
    }
    
    return false;
}

bool CSixMensMorrisBoard::Remove(char player, int from){
    // if(GameOver())
    // {
    //     return false;
    // }
    if(CanRemove(DTurn)and (0 <= from) and (from < SIX_MENS_MORRIS_POSITIONS)){
        char OtherPlayer = DTurn == SIX_MENS_MORRIS_PLAYER_R ? SIX_MENS_MORRIS_PLAYER_W : SIX_MENS_MORRIS_PLAYER_R;
        if(DPositions[from] == OtherPlayer){
            for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
                DPreviousPositions[Index] = DPositions[Index];       
            }
            DPositions[from] = SIX_MENS_MORRIS_EMPTY;
            int UnplacedIndex = OtherPlayer == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;
            int PlayerCount = DUnplacedPieces[UnplacedIndex];

            for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
                if(DPositions[Index] == OtherPlayer){
                    PlayerCount++;
                }
            }
            if(PlayerCount <= 2){// if player count <= 2 which means it is keep tracking
            // of 2 pieces here
                DTurn = tolower(DTurn);
                return GameOver();
                // return false;
            }
            bool HasMove = false;
            for(int From = 0; From < SIX_MENS_MORRIS_POSITIONS; From++){
                if(DPositions[From] == OtherPlayer){
                    for(int To = 0; To < SIX_MENS_MORRIS_POSITIONS; To++){
                        if(From == To){
                            continue;    
                        }
                        if((SIX_MENS_MORRIS_EMPTY == DPositions[To]) and AdjacentPositions(From,To)){
                            HasMove = true;
                            break;
                        }
                    }
                    if(HasMove){
                        break;   
                    }
                }       
            }
            if(HasMove){
                DTurn = OtherPlayer;
            }
            else{
                DTurn = tolower(DTurn);   
            }
            return true;
        }
    }
    return false;
}
