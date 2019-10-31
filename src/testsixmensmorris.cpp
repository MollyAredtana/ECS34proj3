#include <gtest/gtest.h> 	  			 	 
#include "SixMensMorrisBoard.h"

TEST(SixMensMorrisBoardTest, DefaultBoardTest){
    // Needs to test that default board is correct
    CSixMensMorrisBoard Board;  // create a board
    EXPECT_EQ(Board.ToString(), 
    ">RU:6 RC:0  WU:6 WC:0\no---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");

    EXPECT_EQ(std::string(Board), Board.ToString());
    EXPECT_EQ(Board.PlayerAtPosition(0), SIX_MENS_MORRIS_EMPTY); // it's empty

    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R); // check whose turn

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 6); // every player should have six pieces 
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 6); // as same as above

    // EXPECT_TRUE(Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0)); // place the first piece on the board, pos is 0
    // EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 0)); 
    // EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 1));
    // EXPECT_FALSE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_R)); // 还不到三个棋子不可以remove,而且不确定在不在
    // 一条线上
    
    EXPECT_EQ(Board.PlayerAtPosition(0), SIX_MENS_MORRIS_EMPTY); // just testing R is on the pos 0

    // EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W); // R turn passed , so W takes the turn
    // EXPECT_TRUE(Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1)); // place W on 1 so I can test MOVE()

    EXPECT_FALSE(Board.GameOver());
}

TEST(SixMensMorrisBoardTest, SetBoardTest){
    // Needs to test that setting board is correct
    
    char Turn = SIX_MENS_MORRIS_PLAYER_W;
    int Unplaced[SIX_MENS_MORRIS_PLAYERS] = {2, 3};
    char Positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R, SIX_MENS_MORRIS_PLAYER_W, SIX_MENS_MORRIS_PLAYER_R,
                                                 SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY,
                                                 SIX_MENS_MORRIS_PLAYER_W, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_PLAYER_W,
                                                 SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY,
                                                 SIX_MENS_MORRIS_PLAYER_R, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_PLAYER_R};
                                            
    char Previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_PLAYER_W, SIX_MENS_MORRIS_PLAYER_R,
                                                SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY,
                                                SIX_MENS_MORRIS_PLAYER_W, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_PLAYER_W,
                                                SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY,
                                                SIX_MENS_MORRIS_PLAYER_R, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_PLAYER_R};
    CSixMensMorrisBoard Board(Turn, Unplaced, Positions, Previous);

    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W); // check whose turn
    for (int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        EXPECT_EQ(Board.PlayerAtPosition(Index), Positions[Index]);
    }
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), Unplaced[0]);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), Unplaced[1]);
    EXPECT_FALSE(Board.GameOver());
    EXPECT_EQ(std::string(Board),
                            " RU:2 RC:0 >WU:3 WC:0\n"
                            "R---------W---------R      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "W----o         o----W\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "R---------o---------R\n");
    EXPECT_EQ(std::string(Board), Board.ToString());
    
}

TEST(SixMensMorrisBoardTest, ResetBoardTest){
    // Needs to test that resetting to default board is correct
    CSixMensMorrisBoard Board;
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);
    EXPECT_EQ(Board.PlayerAtPosition(0), SIX_MENS_MORRIS_PLAYER_R);


    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2);


    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 4);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 5);

    Board.ResetBoard();

    for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
    {
        if(Board.PlayerAtPosition(i) != SIX_MENS_MORRIS_EMPTY)
        {
            throw "reset has some problems";
        }
    }

    EXPECT_EQ(Board.UnplacedPieces('R'), 6);
    EXPECT_EQ(Board.UnplacedPieces('W'), 6);


    

}

TEST(SixMensMorrisBoardTest, PlacementTest){
    // Needs to test that normal placement is correct
    CSixMensMorrisBoard Board;  // create a board

    EXPECT_TRUE(Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0)); // place the first piece on the board, pos is 0
    EXPECT_EQ(Board.ToString(), 
    "RU:5 RC:1  >WU:6 WC:0\nR---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");
    EXPECT_EQ(std::string(Board), 
        "RU:5 RC:1  >WU:6 WC:0\nR---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");
    
    EXPECT_EQ(std::string(Board), Board.ToString());


    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 5); // already placed one, 5 left
    EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 0)); 
    EXPECT_TRUE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_R)); // 上面有东西可以remove, 说明R已经放过棋子了
    EXPECT_EQ(Board.PlayerAtPosition(0), SIX_MENS_MORRIS_PLAYER_R); // just testing R is on the pos 0

    EXPECT_FALSE(Board.Place(SIX_MENS_MORRIS_PLAYER_W, 0)); // already placed R on 0, so W can not be placed
    EXPECT_TRUE(Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1)); // placed W's first piece on pos 1
    EXPECT_EQ(Board.ToString(), 
    ">RU:5 RC:1  WU:5 WC:1\nR---------W---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");
    
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 5); // already placed one, 5 left
    EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 1)); 
    EXPECT_TRUE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_W)); // 上面有东西可以remove, 说明R已经放过棋子了
    EXPECT_EQ(Board.PlayerAtPosition(1), SIX_MENS_MORRIS_PLAYER_W); // just testing R is on the pos 0

}

TEST(SixMensMorrisBoardTest, PlacementMillTest){
    // Needs to test that placement creating a mill is correct with removal
    CSixMensMorrisBoard Board;  // create a board

    // first test

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 1);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 7);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2);
    // a mill
    EXPECT_TRUE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_R));
    EXPECT_TRUE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 6));
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 6);

    EXPECT_EQ(Board.ToString(), 
    ">RU:3 RC:3  WU:3 WC:2\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----W         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    Board.ResetBoard();

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);

    // no mill

    EXPECT_EQ(Board.ToString(), 
    ">RU:4 RC:2  WU:4 WC:2\nR---------W---------R     0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\nW----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    EXPECT_FALSE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_W));

}

TEST(SixMensMorrisBoardTest, MoveTest){
    // Needs to test that movement is correct
    CSixMensMorrisBoard Board;  // create a board
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 4);
    EXPECT_EQ(Board.ToString(), 
    ">RU:5 RC:1  WU:5 WC:1\nR---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 1)); // not sure about move is happening
    //after we have placed all the pieces or we can move whenever we want
    EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 2, 1));
    EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 0, 1));

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 1);// r 2
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);// w 2
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2);// r 3

    EXPECT_EQ(Board.ToString(), 
    "RU:3 RC:3  >WU:4 WC:2\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");

    // R created a mill
    EXPECT_TRUE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_R));
    EXPECT_TRUE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 4));

    EXPECT_EQ(Board.ToString(), 
    "RU:3 RC:3  >WU:4 WC:1\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 3);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 4);

    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 4);// w 3
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 6);// r 4
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 5);// w 4
    EXPECT_EQ(Board.ToString(), 
    ">RU:2 RC:4  WU:2 WC:3\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\nR----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    EXPECT_TRUE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_W));
    EXPECT_TRUE(Board.Remove(SIX_MENS_MORRIS_PLAYER_R, 2));

    EXPECT_EQ(Board.ToString(), 
    ">RU:2 RC:3  WU:2 WC:3\nR---------R---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\nR----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 2);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 2);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2); // R 5
    // create a mill

    EXPECT_EQ(Board.ToString(), 
    "RU:1 RC:4  >WU:2 WC:3\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\nR----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    EXPECT_TRUE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_R));
    EXPECT_TRUE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 5));

    EXPECT_EQ(Board.ToString(), 
    "RU:1 RC:4  >WU:2 WC:2\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\nR----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 5); // W 5
    // create a mill
    Board.CanRemove(SIX_MENS_MORRIS_PLAYER_W);
    Board.Remove(SIX_MENS_MORRIS_PLAYER_R, 6);

    EXPECT_EQ(Board.ToString(), 
    ">RU:1 RC:3  WU:1 WC:3\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");


    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 1);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 1);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 6); // R 6
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 9); // R 6

    EXPECT_EQ(Board.ToString(), 
    ">RU:0 RC:4  WU:0 WC:4\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\nR----o         o----W\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");
    

    if(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W) == Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R) == 0)
    {
        EXPECT_TRUE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 6));
        EXPECT_TRUE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 6, 7));

        EXPECT_TRUE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 5));
        EXPECT_TRUE(Board.Move(SIX_MENS_MORRIS_PLAYER_W, 5, 8));

        EXPECT_TRUE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 0));
        EXPECT_TRUE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 0, 6));

        EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 1));
        EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 1, 4));
    }



    // second test
    // EXPECT_EQ(Board.ToString(), 
    // "o---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");

    Board.ResetBoard();
    EXPECT_EQ(Board.ToString(), 
    ">RU:6 RC:0  WU:6 WC:0\no---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");

    EXPECT_EQ(Board.PlayerAtPosition(0), '\0');
    EXPECT_EQ(Board.PlayerAtPosition(2), '\0');

// 1
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);
//2
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);
//3
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 4);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 5);
//4
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 6);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 7);
//5
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 8);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 9);
    //6
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 10);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 11);

    // check unplaced pieces.

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 0);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 0);

    if(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R) == Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W) == 0)
    {
        // follow the player turn, R first
        EXPECT_TRUE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 6));
        EXPECT_TRUE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 6, 13));
        EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 6, 0));

        EXPECT_TRUE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 11));
        EXPECT_TRUE(Board.Move(SIX_MENS_MORRIS_PLAYER_W, 11, 12));
        EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_W, 9, 8));

    }
    else{
        throw "Unplaced piece is not right";
    }





}

TEST(SixMensMorrisBoardTest, MoveMillTest){
    // Needs to test that movement creating a mill is correct with removal
    CSixMensMorrisBoard Board;  // create a board
    // the correct version

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0); // 1
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 8);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 1); // 2
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 6);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 7); // 3
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 13); // 4
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 10);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 9); // 5
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 12);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 4); // 6
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 15);

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 0);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 0);

    // let's check move

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 9, 2);
    // should create a mill
    EXPECT_TRUE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 6));

     EXPECT_EQ(Board.ToString(), 
    "RU:0 RC:6  >WU:0 WC:5\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----R----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----R         W----o\n|    |         |    |\n|    |         |    |\n|    W----o----W    |\n|         |         |\n|         |         |\nR---------o---------W\n");



}
                                       
TEST(SixMensMorrisBoardTest, TwoPieceGameOverTest){
    // Needs to test that game over is correct when only two pieces left
    CSixMensMorrisBoard Board;

    EXPECT_EQ(Board.ToString(), 
    ">RU:6 RC:0  WU:6 WC:0\no---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |\n6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");
    
    int OnboardR = 0;
    int OnboardW = 0;

    // case 1 : opponents only have 2 pieces left

        // check how many pieces first
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 6);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 6);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);// 1
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);
    OnboardW++; // 1

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 1);// 2
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 4);
    OnboardW++; // 2

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2);// 3
    // create a mill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 3);
    OnboardW--; // 1

    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);
    OnboardW++; // 2

    EXPECT_EQ(Board.ToString(), 
    ">RU:3 RC:3  WU:3 WC:2\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |6-7   8-9\n|    W----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 3);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 3);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 9);// 4
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 6);
    OnboardW++; // 3

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 15);// 5
    // create a mill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 6);
    OnboardW--; // 2

    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 6);
    OnboardW++;// 3

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 13);// 6
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 7);
    OnboardW++;// 4

    EXPECT_EQ(Board.ToString(), 
    ">RU:0 RC:6  WU:0 WC:4\nR---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |6-7   8-9\n|    W----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nW----W         o----R\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\nR---------o---------R\n");

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 0);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 0);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 15, 14);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 4, 5);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 9, 15);
    // A mill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 6);
    OnboardW--;// 3

    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 5, 4);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 0, 6);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 4, 5);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 1, 0);
    // a mill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 3);
    OnboardW--; // 2

    if(OnboardW == 2)
    {
        std::cout << "  passed  2 piece over " << std::endl;
    }
    else{
        throw " Didn't pass the 2 piece over line 430 ";
    }

    EXPECT_TRUE(Board.GameOver());




}

TEST(SixMensMorrisBoardTest, NoMoveGameOverTest){
    // Needs to test that game over is correct when no movement allowed
    // case 2 : opponent doesn't have legal moves

    CSixMensMorrisBoard Board;

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);// 1
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 1);// 2
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 4);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2);// 3
    // create a  mill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 3);// 3

    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 3);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 3);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 9);// 4
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 8);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 15);// 5
    // a mill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 8);

    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 8);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 12);// 6
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 5);

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 0);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 0);

    if(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W) != 0)
    {
        throw "  unplaced tracking has some issue ";
    }

    // start moving

    if(Board.PlayerTurn() != SIX_MENS_MORRIS_PLAYER_R)
    {
        throw "  Player turn has some issue";
    }

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 0, 6);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 3, 7);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 1, 0);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 4, 1);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 15, 14);
    if(Board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 3))
    {
        throw "  CanMove has some problem  ";
    }
    else{
        std::cout << "  this function is fine !! YEAH!";
    }
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 3, 4);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 7, 3);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 8, 12);

    if(Board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 1) || Board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 4) || Board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 5) || Board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 8))
    {
        throw "  Can Move is not right   ";
    }
    else{
        std::cout << "   no problems " << std::endl;
    }

    EXPECT_TRUE(Board.GameOver());

}

TEST(SixMensMorrisBoardTest, BadParametersTest){
    // Needs to test that correct return upon bad parameters
    CSixMensMorrisBoard Board;
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);

    EXPECT_FALSE(Board.Place('Z', 2));
    EXPECT_FALSE(Board.Place(SIX_MENS_MORRIS_PLAYER_R, 88));

    EXPECT_EQ(Board.UnplacedPieces('Z'), -1);
    EXPECT_EQ(Board.PlayerAtPosition(-1), '\0');

    EXPECT_FALSE(Board.CanMove('Z', 0));
    EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 88));

    EXPECT_FALSE(Board.CanRemove('Z'));
    
    EXPECT_FALSE(Board.Move('Z', 0, 1));
    EXPECT_TRUE(Board.Move(SIX_MENS_MORRIS_PLAYER_W, 1, 2));
    EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_W, 2, 8));

    EXPECT_FALSE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 0));
    EXPECT_TRUE(Board.Remove(SIX_MENS_MORRIS_PLAYER_R, 0));
    EXPECT_FALSE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 88));









    
}

