#include <gtest/gtest.h> 	  			 	 
#include "SixMensMorrisBoard.h"

TEST(SixMensMorrisBoardTest, DefaultBoardTest){
    // Needs to test that default board is correct
    CSixMensMorrisBoard Board;  // create a board
    
    EXPECT_EQ(std::string(Board),
                            ">RU:6 RC:0  WU:6 WC:0\n"
                            "o---------o---------o      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");
    EXPECT_EQ(std::string(Board), Board.ToString());
    // basic checking here
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R); // check whose turn
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 6); // every player should have six pieces 
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 6); // as same as above

    int i = 0;
    while(i < SIX_MENS_MORRIS_POSITIONS)
    {
        EXPECT_EQ(Board.PlayerAtPosition(i), SIX_MENS_MORRIS_EMPTY);
        i++;
    }
        
    EXPECT_TRUE(Board.Place('R', 0));
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);

    EXPECT_TRUE(Board.CanMove('R', 0));  // want to double make sure 
    // that the only thing determines can it move or not
    // is not is it in the moving phase but is it's adjacent is empty or not
    EXPECT_FALSE(Board.Move('R', 0, 1));

    EXPECT_FALSE(Board.CanRemove('R'));
    EXPECT_FALSE(Board.CanRemove('W'));

    EXPECT_FALSE(Board.Remove('R', 0));
    EXPECT_FALSE(Board.Remove('W', 0));


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
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);
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
    EXPECT_EQ(Board.PlayerAtPosition(0), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(Board.ToString(), 
    " RU:5 RC:0 >WU:6 WC:0\nR---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");
    EXPECT_EQ(std::string(Board), 
    " RU:5 RC:0 >WU:6 WC:0\nR---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |        LEGEND\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o\n");
    EXPECT_EQ(std::string(Board), Board.ToString());


    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 5); // already placed one, 5 left
    EXPECT_EQ(Board.PlayerAtPosition(0), SIX_MENS_MORRIS_PLAYER_R); // just testing R is on the pos 0

    EXPECT_EQ(std::string(Board),
                            " RU:5 RC:0 >WU:6 WC:0\n"
                            "R---------o---------o      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");
    EXPECT_FALSE(Board.Place(SIX_MENS_MORRIS_PLAYER_W, 0)); // already placed R on 0, so W can not be placed
    EXPECT_TRUE(Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1)); // placed W's first piece on pos 1
    
    EXPECT_EQ(std::string(Board),
                            ">RU:5 RC:0  WU:5 WC:0\n"
                            "R---------W---------o      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");
    
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 5); // already placed one, 5 left
    EXPECT_EQ(Board.PlayerAtPosition(1), SIX_MENS_MORRIS_PLAYER_W); // just testing R is on the pos 0

    Board.Place('R', 15);

    EXPECT_EQ(std::string(Board),
                            " RU:4 RC:0 >WU:5 WC:0\n"
                            "R---------W---------o      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------R\n");
    Board.Place('W', 10);
    EXPECT_EQ(Board.ToString(),
                            ">RU:4 RC:0  WU:4 WC:0\n"
                            "R---------W---------o      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    W----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------R\n");
    EXPECT_EQ(std::string(Board), Board.ToString());
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
    EXPECT_TRUE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 7));
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 6);


    EXPECT_EQ(Board.ToString(),
                            ">RU:3 RC:1  WU:3 WC:0\n"
                            "R---------R---------R      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    W----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "W----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");

    Board.ResetBoard();

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 2);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 3);

    // no mill


    EXPECT_EQ(Board.ToString(),
                            ">RU:4 RC:0  WU:4 WC:0\n"
                            "R---------W---------R      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    W----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");

    EXPECT_FALSE(Board.CanRemove(SIX_MENS_MORRIS_PLAYER_W));

}

TEST(SixMensMorrisBoardTest, MoveTest){
    // Needs to test that movement is correct
    CSixMensMorrisBoard Board;  // create a board
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);

    EXPECT_EQ(Board.ToString(),
                            ">RU:5 RC:0  WU:5 WC:0\n"
                            "R---------W---------o      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");

    EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 1)); // not sure about move is happening
    //after we have placed all the pieces or we can move whenever we want
    EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 2, 1));
    EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 0, 1));

    Board.Place('R', 3);
    Board.Place('W', 2);

    Board.Place('R', 4);
    Board.Place('W', 5);

    Board.Place('R', 10);
    Board.Place('W', 7);

    EXPECT_EQ(Board.UnplacedPieces('R'), 2);
    EXPECT_EQ(Board.UnplacedPieces('R'), 2);

    Board.Place('R', 6);
    Board.Place('W', 13);

    Board.Place('R', 15);
    Board.Place('W', 9);

    EXPECT_EQ(Board.UnplacedPieces('R'), 0);
    EXPECT_EQ(Board.UnplacedPieces('W'), 0);

    EXPECT_EQ(Board.ToString(),
                            ">RU:0 RC:0  WU:0 WC:0\n"
                            "R---------W---------W      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    R----R----W    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "R----W         o----W\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    R----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "W---------o---------R\n");

    EXPECT_EQ(Board.ToString(), std::string(Board));

    // can move
    EXPECT_EQ(Board.PlayerAtPosition(15), SIX_MENS_MORRIS_PLAYER_R);

    EXPECT_TRUE(Board.CanMove('R', 15));
    EXPECT_TRUE(Board.Move('R', 15, 14));
    EXPECT_EQ(Board.PlayerAtPosition(15), SIX_MENS_MORRIS_EMPTY);
    EXPECT_EQ(Board.PlayerAtPosition(14), SIX_MENS_MORRIS_PLAYER_R);

    EXPECT_FALSE(Board.CanMove('R', 0));
    EXPECT_FALSE(Board.CanMove('W', 1));

    EXPECT_FALSE(Board.Move('R', 0, 1));
    EXPECT_FALSE(Board.Move('W', 1, 15));
    EXPECT_TRUE(Board.Move('W', 9, 8));
    EXPECT_FALSE(Board.CanMove('W',5));
    EXPECT_FALSE(Board.Move('W', 8, 9));

    EXPECT_EQ(Board.PlayerAtPosition(9), SIX_MENS_MORRIS_EMPTY);
    EXPECT_EQ(Board.PlayerAtPosition(8), SIX_MENS_MORRIS_PLAYER_W);


    EXPECT_EQ(Board.ToString(),
                            ">RU:0 RC:0  WU:0 WC:0\n"
                            "R---------W---------W      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    R----R----W    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "R----W         W----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    R----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "W---------R---------o\n");

    EXPECT_EQ(Board.ToString(), std::string(Board));

    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(Board.PlayerAtPosition(9), SIX_MENS_MORRIS_EMPTY);


    


}

TEST(SixMensMorrisBoardTest, MoveMillTest){
    // Needs to test that movement creating a mill is correct with removal
    CSixMensMorrisBoard Board;  // create a board
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);

    EXPECT_EQ(Board.ToString(),
                            ">RU:5 RC:0  WU:5 WC:0\n"
                            "R---------W---------o      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");

    EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 1)); // not sure about move is happening
    //after we have placed all the pieces or we can move whenever we want
    EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 2, 1));
    EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_R, 0, 1));

    Board.Place('R', 3);
    Board.Place('W', 2);

    Board.Place('R', 4);
    Board.Place('W', 5);

    Board.Place('R', 10);
    Board.Place('W', 7);

    EXPECT_EQ(Board.UnplacedPieces('R'), 2);
    EXPECT_EQ(Board.UnplacedPieces('R'), 2);

    Board.Place('R', 6);
    Board.Place('W', 13);

    Board.Place('R', 15);
    Board.Place('W', 9);

    EXPECT_EQ(Board.UnplacedPieces('R'), 0);
    EXPECT_EQ(Board.UnplacedPieces('W'), 0);

    EXPECT_EQ(Board.ToString(),
                            ">RU:0 RC:0  WU:0 WC:0\n"
                            "R---------W---------W      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    R----R----W    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "R----W         o----W\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    R----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "W---------o---------R\n");

    Board.Move('R', 10, 11);
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);
    Board.Move('W', 13, 14);

    EXPECT_EQ(Board.PlayerAtPosition(10), SIX_MENS_MORRIS_EMPTY);
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);
    
    Board.Move('R', 11, 10);
    EXPECT_EQ(Board.PlayerAtPosition(10), SIX_MENS_MORRIS_PLAYER_R);
    Board.Move('W', 14, 11);

    Board.Move('R', 6, 13);
    Board.Move('W', 9, 8);

    Board.Move('R', 13, 6);
    Board.Move('W', 11, 12);
    // checking 

    EXPECT_EQ(Board.PlayerAtPosition(12), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(Board.PlayerAtPosition(0), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(Board.PlayerAtPosition(1), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(Board.PlayerAtPosition(2), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(Board.PlayerAtPosition(3), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(Board.PlayerAtPosition(4), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(Board.PlayerAtPosition(5), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(Board.PlayerAtPosition(6), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(Board.PlayerAtPosition(7), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(Board.PlayerAtPosition(8), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(Board.PlayerAtPosition(15), SIX_MENS_MORRIS_PLAYER_R);
    // create a mill

    EXPECT_TRUE(Board.CanRemove('W'));
    EXPECT_TRUE(Board.Remove('R', 6));
    EXPECT_EQ(Board.PlayerAtPosition(6), SIX_MENS_MORRIS_EMPTY);

    EXPECT_EQ(Board.ToString(),
                            ">RU:0 RC:0  WU:0 WC:1\n"
                            "R---------W---------W      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    R----R----W    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----W         W----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    R----o----W    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------R\n");

// second test here





}
                                       
TEST(SixMensMorrisBoardTest, TwoPieceGameOverTest){
    // Needs to test that game over is correct when only two pieces left
    CSixMensMorrisBoard Board;
    EXPECT_FALSE(Board.GameOver());
    EXPECT_EQ(std::string(Board),
                            ">RU:6 RC:0  WU:6 WC:0\n"
                            "o---------o---------o      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    o----o----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");
    // int OnboardR = 0;
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

    EXPECT_EQ(std::string(Board),
                            ">RU:3 RC:1  WU:3 WC:0\n"
                            "R---------R---------R      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    W----W----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 3);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 3);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 9);// 4
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 6);
    OnboardW++; // 3
    EXPECT_FALSE(Board.GameOver());

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 15);// 5
    // create a mill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 6);
    OnboardW--; // 2

    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 6);
    OnboardW++;// 3

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 13);// 6
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 7);
    OnboardW++;// 4

    EXPECT_EQ(std::string(Board),
                            ">RU:0 RC:2  WU:0 WC:0\n"
                            "R---------R---------R      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    W----W----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "W----W         o----R\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "R---------o---------R\n");

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 0);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 0);
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 15, 14);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 7, 10);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 9, 15);
    // EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);    
    // amill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 4);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 3, 4);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 2, 9);
    EXPECT_TRUE(Board.Move(SIX_MENS_MORRIS_PLAYER_W, 4, 3));
    // std::cout << std::string(Board) << std::endl;

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 1, 2);
    // amill
    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 3);
    // std::cout << std::string(Board) << std::endl;
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

    EXPECT_EQ(std::string(Board),
                            ">RU:3 RC:1  WU:3 WC:0\n"
                            "R---------R---------R      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    W----W----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----o         o----o\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----o    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------o\n");
    EXPECT_EQ(std::string(Board), Board.ToString());

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 3);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 3);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 9);// 4
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 8);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 15);// 5
    // a mill

    Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 8);
    

    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 8);

    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 12);// 6
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 7);

    EXPECT_EQ(std::string(Board),
                            ">RU:0 RC:2  WU:0 WC:0\n"
                            "R---------R---------R      0---1---2\n"
                            "|         |         |      | 3-4-5 |\n"
                            "|         |         |      6-7   8-9\n"
                            "|    W----W----o    |      | A-B-C |\n"
                            "|    |         |    |      D---E---F\n"
                            "|    |         |    |        LEGEND\n"
                            "o----W         W----R\n"
                            "|    |         |    |\n"
                            "|    |         |    |\n"
                            "|    o----o----R    |\n"
                            "|         |         |\n"
                            "|         |         |\n"
                            "o---------o---------R\n");

    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R), 0);
    EXPECT_EQ(Board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 0);

    char thePositions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R, SIX_MENS_MORRIS_PLAYER_R, SIX_MENS_MORRIS_PLAYER_R,
                                                 SIX_MENS_MORRIS_PLAYER_W, SIX_MENS_MORRIS_PLAYER_W, SIX_MENS_MORRIS_EMPTY,
                                                 SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_PLAYER_W, SIX_MENS_MORRIS_PLAYER_W, SIX_MENS_MORRIS_PLAYER_R,
                                                 SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_PLAYER_R,
                                                 SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_EMPTY, SIX_MENS_MORRIS_PLAYER_R};

    for (int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        EXPECT_EQ(Board.PlayerAtPosition(Index), thePositions[Index]);
    }
    // start moving

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 15, 14);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 7, 10);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 0, 6);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 4, 5);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 1, 4);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 10, 11);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 6, 7);
    Board.Move(SIX_MENS_MORRIS_PLAYER_W, 11, 10);

    Board.Move(SIX_MENS_MORRIS_PLAYER_R, 14, 11);

    

    // std::cout << std::string(Board) << std::endl;


    EXPECT_TRUE(Board.GameOver());
    

    //

}

TEST(SixMensMorrisBoardTest, BadParametersTest){
    // Needs to test that correct return upon bad parameters
    CSixMensMorrisBoard Board;
    Board.Place(SIX_MENS_MORRIS_PLAYER_R, 0);
    Board.Place(SIX_MENS_MORRIS_PLAYER_W, 1);
    EXPECT_EQ(Board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);

    EXPECT_FALSE(Board.Place('Z', 2));
    EXPECT_FALSE(Board.Place(SIX_MENS_MORRIS_PLAYER_R, 88));

    EXPECT_EQ(Board.UnplacedPieces('Z'), -1);
    EXPECT_EQ(Board.PlayerAtPosition(-1), '\0');

    EXPECT_FALSE(Board.CanMove('Z', 0));
    EXPECT_FALSE(Board.CanMove(SIX_MENS_MORRIS_PLAYER_R, 88));

    EXPECT_FALSE(Board.CanRemove('Z'));

    
    EXPECT_FALSE(Board.Move('Z', 0, 1));

    EXPECT_FALSE(Board.Move(SIX_MENS_MORRIS_PLAYER_W, 2, 8));


    EXPECT_FALSE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 0));
    EXPECT_FALSE(Board.Remove(SIX_MENS_MORRIS_PLAYER_W, 88));

}

