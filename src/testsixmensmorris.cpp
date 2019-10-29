#include <gtest/gtest.h> 	  			 	 
#include "SixMensMorrisBoard.h"

TEST(SixMensMorrisBoardTest, DefaultBoardTest){
    // Needs to test that default board is correct
    CSixMensMorrisBoard Board;  // create a board
    EXPECT_EQ(Board.ToString(), 
    "o---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");

    EXPECT_EQ(Board.PlayerAtPosition(0), 'o'); // it's empty

    EXPECT_EQ(Board.PlayerTurn(), 'R'); // check whose turn

    EXPECT_EQ(Board.UnplacedPieces('R'), 6); // every player should have six pieces 
    EXPECT_EQ(Board.UnplacedPieces('W'), 6); // as same as above

    EXPECT_TRUE(Board.Place('R', 0)); // place the first piece on the board, pos is 0
    EXPECT_FALSE(Board.CanMove('R', 0)); 
    EXPECT_FALSE(Board.CanMove('R', 1));
    EXPECT_FALSE(Board.CanRemove('R')); // 还不到三个棋子不可以remove,而且不确定在不在
    // 一条线上
    
    EXPECT_EQ(Board.PlayerAtPosition(0), 'R'); // just testing R is on the pos 0

    EXPECT_EQ(Board.PlayerTurn(), 'W'); // R turn passed , so W takes the turn
    EXPECT_TRUE(Board.Place('W', 1)); // place W on 1 so I can test MOVE()

    EXPECT_FALSE(Board.Move('W', 1, 0));

    EXPECT_FALSE(Board.GameOver());
    EXPECT_FALSE(Board.CanRemove('W'));

    EXPECT_FALSE(Board.Remove('W', 1));

    Board.ResetBoard();
    // make sure reset is working
    EXPECT_EQ(Board.UnplacedPieces('R'), 6);
    EXPECT_EQ(Board.PlayerAtPosition(0), 'o'); // it's empty





    

    
}

TEST(SixMensMorrisBoardTest, SetBoardTest){
    // Needs to test that setting board is correct
    CSixMensMorrisBoard Board;

    // need to access the function CSixMensMorrisBoard(char, int ,...)
    
}

TEST(SixMensMorrisBoardTest, ResetBoardTest){
    // Needs to test that resetting to default board is correct
    CSixMensMorrisBoard Board;
    Board.Place('R', 0);
    Board.Place('W', 1);
    Board.Place('R', 2);

    EXPECT_EQ(Board.UnplacedPieces('R'), 4);
    EXPECT_EQ(Board.UnplacedPieces('W'), 5);

    Board.ResetBoard();

    EXPECT_EQ(Board.UnplacedPieces('R'), 6);
    EXPECT_EQ(Board.UnplacedPieces('W'), 6);


    

}

TEST(SixMensMorrisBoardTest, PlacementTest){
    // Needs to test that normal placement is correct
    CSixMensMorrisBoard Board;  // create a board

    EXPECT_TRUE(Board.Place('R', 0)); // place the first piece on the board, pos is 0
    EXPECT_EQ(Board.ToString(), 
    "R---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");
    
    EXPECT_EQ(Board.UnplacedPieces('R'), 5); // already placed one, 5 left
    EXPECT_FALSE(Board.CanMove('R', 0)); 
    EXPECT_TRUE(Board.CanRemove('R')); // 上面有东西可以remove, 说明R已经放过棋子了
    EXPECT_EQ(Board.PlayerAtPosition(0), 'R'); // just testing R is on the pos 0

    EXPECT_FALSE(Board.Place('W', 0)); // already placed R on 0, so W can not be placed
    EXPECT_TRUE(Board.Place('W', 1)); // placed W's first piece on pos 1
    EXPECT_EQ(Board.ToString(), 
    "R---------W---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");
    
    EXPECT_EQ(Board.UnplacedPieces('W'), 5); // already placed one, 5 left
    EXPECT_FALSE(Board.CanMove('W', 1)); 
    EXPECT_TRUE(Board.CanRemove('W')); // 上面有东西可以remove, 说明R已经放过棋子了
    EXPECT_EQ(Board.PlayerAtPosition(1), 'W'); // just testing R is on the pos 0

}

TEST(SixMensMorrisBoardTest, PlacementMillTest){
    // Needs to test that placement creating a mill is correct with removal
    CSixMensMorrisBoard Board;  // create a board

    // first test

    Board.Place('R', 0);
    Board.Place('W', 3);
    Board.Place('R', 1);
    Board.Place('W', 7);
    Board.Place('R', 2);
    Board.Place('W', 6);

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nW----W         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");

    // we have three piece on it, which means we create a mill

    EXPECT_TRUE(Board.CanRemove('R'));
    EXPECT_TRUE(Board.Remove('W', 6));

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----W         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    Board.ResetBoard();

    Board.Place('W', 0);
    Board.Place('R', 1);
    Board.Place('W', 2);
    Board.Place('R', 3);
    Board.Place('W', 6);

    EXPECT_EQ(Board.ToString(), 
    "W---------R---------W      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    R----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nW----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    EXPECT_FALSE(Board.CanRemove('W'));

    // second test

    Board.ResetBoard();

    Board.Place('R', 10);
    Board.Place('W', 1);
    Board.Place('R', 11);
    Board.Place('W', 7);
    Board.Place('R', 12);
    // create a mill

    EXPECT_TRUE(Board.CanRemove('R'));
    EXPECT_TRUE(Board.Remove('W', 1));

     EXPECT_EQ(Board.ToString(), 
    "o---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----W         o----o\n|    |         |    |\n|    |         |    |\n|    R----R----R    |\n|         |         |\n|         |         |\no---------o---------o");





}

TEST(SixMensMorrisBoardTest, MoveTest){
    // Needs to test that movement is correct
    CSixMensMorrisBoard Board;  // create a board
    Board.Place('R', 0);
    Board.Place('W', 4);
    EXPECT_EQ(Board.ToString(), 
    "R---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    EXPECT_FALSE(Board.CanMove('R', 1)); // not sure about move is happening
    //after we have placed all the pieces or we can move whenever we want
    EXPECT_FALSE(Board.Move('R', 2, 1));
    EXPECT_FALSE(Board.Move('R', 0, 1));

    Board.Place('R', 1);// r 2
    Board.Place('W', 3);// w 2
    Board.Place('R', 2);// r 3

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    // r created a mill
    EXPECT_TRUE(Board.CanRemove('R'));
    EXPECT_TRUE(Board.Remove('W', 4));

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    EXPECT_EQ(Board.UnplacedPieces('R'), 3);
    EXPECT_EQ(Board.UnplacedPieces('W'), 4);

    Board.Place('W', 4);// w 3
    Board.Place('R', 6);// r 4
    Board.Place('W', 5);// w 4
    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nR----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    EXPECT_TRUE(Board.CanRemove('W'));
    EXPECT_TRUE(Board.Remove('R', 2));

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nR----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    EXPECT_EQ(Board.UnplacedPieces('R'), 2);
    EXPECT_EQ(Board.UnplacedPieces('W'), 2);

    Board.Place('R', 2); // R 5
    // create a mill

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nR----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    EXPECT_TRUE(Board.CanRemove('R'));
    EXPECT_TRUE(Board.Remove('W', 5));

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nR----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    Board.Place('W', 5); // W 5
    // create a mill
    Board.CanRemove('W');
    Board.Remove('R', 6);

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    EXPECT_EQ(Board.UnplacedPieces('R'), 1);
    EXPECT_EQ(Board.UnplacedPieces('W'), 1);

    Board.Place('R', 6); // R 6
    Board.Place('W', 9); // R 6

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nR----o         o----W\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");
    

    if(Board.UnplacedPieces('W') == Board.UnplacedPieces('R') == 0)
    {
        EXPECT_TRUE(Board.CanMove('R', 6));
        EXPECT_TRUE(Board.Move('R', 6, 7));

        EXPECT_TRUE(Board.CanMove('W', 5));
        EXPECT_TRUE(Board.Move('W', 5, 8));

        EXPECT_TRUE(Board.CanMove('R', 0));
        EXPECT_TRUE(Board.Move('R', 0, 6));

        EXPECT_FALSE(Board.CanMove('R', 1));
        EXPECT_FALSE(Board.Move('R', 1, 4));
    }

    EXPECT_EQ(Board.ToString(), 
    "o---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    W----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nR----R         W----W\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


    // second test
    // EXPECT_EQ(Board.ToString(), 
    // "o---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");

    Board.ResetBoard();
    EXPECT_EQ(Board.ToString(), 
    "o---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |      6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");

    EXPECT_EQ(Board.PlayerAtPosition('R'), 'o');
    EXPECT_EQ(Board.PlayerAtPosition('W'), 'o');

// 1
    Board.Place('R', 0);
    Board.Place('W', 1);
//2
    Board.Place('R', 2);
    Board.Place('W', 3);
//3
    Board.Place('R', 4);
    Board.Place('W', 5);
//4
    Board.Place('R', 6);
    Board.Place('W', 7);
//5
    Board.Place('R', 8);
    Board.Place('W', 9);
    //6
    Board.Place('R', 10);
    Board.Place('W', 11);

    // check unplaced pieces.

    EXPECT_EQ(Board.UnplacedPieces('R'), 0);
    EXPECT_EQ(Board.UnplacedPieces('W'), 0);

    if(Board.UnplacedPieces('R') == Board.UnplacedPieces('W') == 0)
    {
        // follow the player turn, R first
        EXPECT_TRUE(Board.CanMove('R', 6));
        EXPECT_TRUE(Board.Move('R', 6, 13));
        EXPECT_FALSE(Board.Move('R', 6, 0));

        EXPECT_TRUE(Board.CanMove('W', 11));
        EXPECT_TRUE(Board.Move('W', 11, 12));
        EXPECT_FALSE(Board.Move('W', 9, 8));

    }
    else{
        throw "Unplaced piece is not right";
    }





}

TEST(SixMensMorrisBoardTest, MoveMillTest){
    // Needs to test that movement creating a mill is correct with removal
    CSixMensMorrisBoard Board;  // create a board
    // the correct version

    Board.Place('R', 0);
    Board.Place('W', 8);
    Board.Place('R', 1);
    Board.Place('W', 6);
    Board.Place('R', 2);
    Board.Place('W', 4);

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |\n6-7   8-9\n|    o----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nW----o         W----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");

    EXPECT_TRUE(Board.CanRemove('R'));
    EXPECT_TRUE(Board.Remove('W', 4));

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |\n6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nW----o         W----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");

    EXPECT_FALSE(Board.CanRemove('W'));
    EXPECT_FALSE(Board.Remove('R', 1));

    EXPECT_EQ(Board.ToString(), 
    "R---------o---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |\n6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nW----o         W----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");


}
                                       
TEST(SixMensMorrisBoardTest, TwoPieceGameOverTest){
    // Needs to test that game over is correct when only two pieces left
    CSixMensMorrisBoard Board;

    EXPECT_EQ(Board.ToString(), 
    "o---------o---------o      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |\n6-7   8-9\n|    o----o----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");
    
    int OnboardR = 0;
    int OnboardW = 0;

    // case 1 : opponents only have 2 pieces left

        // check how many pieces first
    EXPECT_EQ(Board.UnplacedPieces('R'), 6);
    EXPECT_EQ(Board.UnplacedPieces('W'), 6);

    Board.Place('R', 0);// 1
    Board.Place('W', 3);
    OnboardW++; // 1

    Board.Place('R', 1);// 2
    Board.Place('W', 4);
    OnboardW++; // 2

    Board.Place('R', 2);// 3
    // create a mill

    Board.Remove('W', 3);
    OnboardW--; // 1

    Board.Place('W', 3);
    OnboardW++; // 2

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |6-7   8-9\n|    o----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\no----o         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\no---------o---------o");

    EXPECT_EQ(Board.UnplacedPieces('R'), 3);
    EXPECT_EQ(Board.UnplacedPieces('W'), 3);

    Board.Place('R', 9);// 4
    Board.Place('W', 6);
    OnboardW++; // 3

    Board.Place('R', 15);// 5
    // create a mill

    Board.Remove('W', 6);
    OnboardW--; // 2

    Board.Place('W', 6);
    OnboardW++;// 3

    Board.Place('R', 13);// 6
    Board.Place('W', 7);
    OnboardW++;// 4

    EXPECT_EQ(Board.ToString(), 
    "R---------R---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |6-7   8-9\n|    W----W----o    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nW----W         o----R\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\nR---------o---------R");

    EXPECT_EQ(Board.UnplacedPieces('R'), 0);
    EXPECT_EQ(Board.UnplacedPieces('W'), 0);

    Board.Move('R', 15, 14);
    Board.Move('W', 4, 5);

    Board.Move('R', 9, 15);
    // A mill

    Board.Remove('W', 6);
    OnboardW--;// 3

    Board.Move('W', 5, 4);

    Board.Move('R', 0, 6);
    Board.Move('W', 4, 5);

    Board.Move('R', 1, 0);
    // a mill

    Board.Remove('W', 3);
    OnboardW--; // 2

    EXPECT_EQ(Board.ToString(), 
    "R---------o---------R      0---1---2\n|         |         |      | 3-4-5 |\n|         |         |6-7   8-9\n|    o----o----W    |      | A-B-C |\n|    |         |    |      D---E---F\n|    |         |    |\nR----W         o----o\n|    |         |    |\n|    |         |    |\n|    o----o----o    |\n|         |         |\n|         |         |\nR---------R---------R");
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

    Board.Place('R', 0);// 1
    Board.Place('W', 3);

    Board.Place('R', 1);// 2
    Board.Place('W', 4);

    Board.Place('R', 2);// 3
    // create a  mill

    Board.Remove('W', 3);// 3

    Board.Place('W', 3);

    EXPECT_EQ(Board.UnplacedPieces('R'), 3);
    EXPECT_EQ(Board.UnplacedPieces('W'), 3);

    Board.Place('R', 9);// 4
    Board.Place('W', 8);

    Board.Place('R', 15);// 5
    // a mill

    Board.Remove('W', 8);

    Board.Place('W', 8);

    Board.Place('R', 12);// 6
    Board.Place('W', 5);

    EXPECT_EQ(Board.UnplacedPieces('R'), 0);
    EXPECT_EQ(Board.UnplacedPieces('W'), 0);

    if(Board.UnplacedPieces('W') != 0)
    {
        throw "  unplaced tracking has some issue ";
    }

    // start moving

    if(Board.PlayerTurn() != 'R')
    {
        throw "  Player turn has some issue";
    }

    Board.Move('R', 0, 6);
    Board.Move('W', 3, 7);

    Board.Move('R', 1, 0);
    Board.Move('W', 4, 1);

    Board.Move('R', 15, 14);
    if(Board.CanMove('W', 3))
    {
        throw "  CanMove has some problem  ";
    }
    else{
        std::cout << "  this function is fine !! YEAH!";
    }
    Board.Move('W', 3, 4);

    Board.Move('R', 7, 3);
    Board.Move('W', 8, 12);

    if(Board.CanMove('W', 1) || Board.CanMove('W', 4) || Board.CanMove('W', 5) || Board.CanMove('W', 8))
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
    Board.Place('R', 0);
    Board.Place('W', 1);

    EXPECT_FALSE(Board.Place('Z', 2));
    EXPECT_FALSE(Board.Place('R', 88));

    EXPECT_EQ(Board.UnplacedPieces('Z'), -1);
    EXPECT_EQ(Board.PlayerAtPosition(-1), '\0');

    EXPECT_FALSE(Board.CanMove('Z', 0));
    EXPECT_FALSE(Board.CanMove('R', 88));

    EXPECT_FALSE(Board.CanRemove('Z'));
    
    EXPECT_FALSE(Board.Move('Z', 0, 1));
    EXPECT_TRUE(Board.Move('W', 1, 2));
    EXPECT_FALSE(Board.Move('W', 2, 8));

    EXPECT_FALSE(Board.Remove('Z', 0));
    EXPECT_TRUE(Board.Remove('R', 0));
    EXPECT_FALSE(Board.Remove('W', 88));









    
}

