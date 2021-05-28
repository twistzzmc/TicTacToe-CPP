#include <gtest/gtest.h>

#include "../board.hpp"
#include "../board.cpp"

#include "../utils.hpp"
#include "../utils.cpp"

#include "../game.hpp"
#include "../human-player.hpp"
#include "../computer-player.hpp"


using namespace std;


TEST(BoardTest, EmptyInit) {
    Board emptyBoard;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            ASSERT_EQ(' ', emptyBoard.getField(i, j)) << " i=" << i << ", j=" << j;
}

TEST(BoardTest, MakingMoves) {
    Board board;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            ASSERT_TRUE(board.checkMoveValidity(i, j)) << " i=" << i << ", j=" << j;

    ASSERT_EQ(board.makeMove(0, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 0, 'O'), Board::MoveType::NOT_ALLOWED);
    ASSERT_EQ(board.makeMove(1, 1, ' '), Board::MoveType::NOT_ALLOWED);
    ASSERT_EQ(board.makeMove(1, 1, 'X'), Board::MoveType::WRONG_TURN);
    ASSERT_FALSE(board.checkMoveValidity(0, 0));

    ASSERT_EQ(board.makeMove(1, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 2, 'O'), Board::MoveType::WRONG_TURN);
}

TEST(BoardTest, PrintingEmptyBoard) {
    Board emptyBoard;
    ostringstream stream;

    const string emptyBoardASCII = "   |   |   \n"
                                  "———|———|———\n"
                                  "   |   |   \n"
                                  "———|———|———\n"
                                  "   |   |   \n";
    
    stream << emptyBoard;
    ASSERT_EQ(emptyBoardASCII, stream.str());
}

TEST(BoardTest, PrintingNonEmptyBoard) {
    Board board;
    ostringstream stream;

    const string boardASCII = " X |   | O \n"
                             "———|———|———\n"
                             "   | X |   \n"
                             "———|———|———\n"
                             "   | O |   \n";
    
    ASSERT_EQ(board.makeMove(0, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 2, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 1, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 1, 'O'), Board::MoveType::NORMAL);

    stream << board;
    ASSERT_EQ(boardASCII, stream.str());
}

TEST(BoardTest, WinningVertical) {
    Board board;

    /*
        "   |   | X \n"
        "———|———|———\n"
        " O | O | X \n"
        "———|———|———\n"
        "   |   | X \n";
    */

    ASSERT_EQ(board.makeMove(0, 2, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 2, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 0, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 2, 'X'), Board::MoveType::VICTORY);
}

TEST(BoardTest, WinningHorizontal) {
    Board board;

        /*
        " X |   |   \n"
        "———|———|———\n"
        " O | O | O \n"
        "———|———|———\n"
        " X |   | X \n";
    */

    ASSERT_EQ(board.makeMove(0, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 0, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 2, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 2, 'O'), Board::MoveType::VICTORY);
}

TEST(BoardTest, WinningBackward) {
    Board board;

    /*
        " O |   |   \n"
        "———|———|———\n"
        " X | O | X \n"
        "———|———|———\n"
        " X |   | O \n";
    */

    ASSERT_EQ(board.makeMove(1, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 2, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 2, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 0, 'O'), Board::MoveType::VICTORY);
}

TEST(BoardTest, WinningForward) {
    Board board;

    /*
        " O | O | X \n"
        "———|———|———\n"
        "   | X |   \n"
        "———|———|———\n"
        " X |   |   \n";
    */

    ASSERT_EQ(board.makeMove(1, 1, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 0, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 2, 'X'), Board::MoveType::VICTORY);
}

TEST(BoardTest, Draw) {
    Board board;

    /*
        " X | O | X \n"
        "———|———|———\n"
        " O | O | X \n"
        "———|———|———\n"
        " X | X | O \n";
    */

    ASSERT_EQ(board.makeMove(0, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 2, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 2, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 2, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 0, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 1, 'X'), Board::MoveType::DRAW);
}

TEST(BoardTest, savingMoves) {
    Board board;

    /*
        " X | O | X \n"
        "———|———|———\n"
        " O | O | X \n"
        "———|———|———\n"
        " X | X | O \n";
    */

    ASSERT_EQ(board.makeMove(0, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(0, 2, 'X'), Board::MoveType::NORMAL);

    ASSERT_EQ(board.makeMove(0, 1, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 2, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 2, 'O'), Board::MoveType::NORMAL);

    ASSERT_EQ(board.makeMove(2, 0, 'X'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(1, 0, 'O'), Board::MoveType::NORMAL);
    ASSERT_EQ(board.makeMove(2, 1, 'X'), Board::MoveType::DRAW);

    pair<array<int, 2>, char> testMoves[] = { {{0, 0}, 'X'}, {{1, 1}, 'O'}, {{0, 2}, 'X'},
                                                        {{0, 1}, 'O'}, {{1, 2}, 'X'}, {{2, 2}, 'O'},
                                                        {{2, 0}, 'X'}, {{1, 0}, 'O'}, {{2, 1}, 'X'} };

    pair<array<int, 2>, char>* moves = board.getMoves();
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(moves[i].first[0], testMoves[i].first[0]);
        ASSERT_EQ(moves[i].first[1], testMoves[i].first[1]);
        ASSERT_EQ(moves[i].second, testMoves[i].second);
    }
}


TEST(ParseTest, LackingPlayer) {
    array<string, 3> emptyOptions = parseOptions(vector<string>{ });
    ASSERT_EQ(emptyOptions[0], "");
    ASSERT_EQ(emptyOptions[1], "Option --player not specified!");

    array<string, 3> optionsWithoutPlayer = parseOptions(vector<string>{ "-p2", "human", "-s", "p1" });
    ASSERT_EQ(optionsWithoutPlayer[0], "");
    ASSERT_EQ(optionsWithoutPlayer[1], "Option --player not specified!");
}

TEST(ParseTest, LackingArguments) {
    array<string, 3> optionsWithoutPlayerArgument = parseOptions(vector<string>{ "-s", "p1", "-p" });
    ASSERT_EQ(optionsWithoutPlayerArgument[0], "");
    ASSERT_EQ(optionsWithoutPlayerArgument[1], "--player argument not specified!");

    array<string, 3> optionsWithoutStartArgument = parseOptions(vector<string>{ "-p", "human", "-s" });
    ASSERT_EQ(optionsWithoutStartArgument[0], "");
    ASSERT_EQ(optionsWithoutStartArgument[1], "--start argument not specified!");

    array<string, 3> optionsWithoutSecondPlayerArgument = parseOptions(vector<string>{ "-p", "human", "--second-player" });
    ASSERT_EQ(optionsWithoutSecondPlayerArgument[0], "");
    ASSERT_EQ(optionsWithoutSecondPlayerArgument[1], "--second-player argument not specified!");
}

TEST(ParseTest, BadArguments) {
    array<string, 3> badPlayerArgument = parseOptions(vector<string>{ "-p", "hman", "-s", "p1" });
    ASSERT_EQ(badPlayerArgument[0], "");
    ASSERT_EQ(badPlayerArgument[1], "Bad option for --player: hman");

    array<string, 3> badStartArgument = parseOptions(vector<string>{ "-p", "human", "-s", "p" });
    ASSERT_EQ(badStartArgument[0], "");
    ASSERT_EQ(badStartArgument[1], "Bad option for --start: p");

    array<string, 3> badSecondPlayerArgument = parseOptions(vector<string>{ "-p", "human", "-p2", "ez" });
    ASSERT_EQ(badSecondPlayerArgument[0], "");
    ASSERT_EQ(badSecondPlayerArgument[1], "Bad option for --second-player: ez");
}

TEST(ParseTest, BadOptions) {
    array<string, 3> badOption = parseOptions(vector<string>{ "-p", "human", "-s", "p1", "--p2" });
    ASSERT_EQ(badOption[0], "");
    ASSERT_EQ(badOption[1], "Bad option: --p2");

    array<string, 3> noOptions = parseOptions(vector<string>{ });
    ASSERT_EQ(noOptions[0], "");
    ASSERT_EQ(noOptions[1], "Option --player not specified!");
}

TEST(ParseTest, onlyOneOption) {
    array<string, 3> oneOptionHuman = parseOptions(vector<string>{ "-p", "human" });
    ASSERT_EQ(oneOptionHuman[0], "human");
    ASSERT_EQ(oneOptionHuman[1], "None");
    ASSERT_EQ(oneOptionHuman[2], "None");

    array<string, 3> oneOptionComputer = parseOptions(vector<string>{ "-p", "easy" });
    ASSERT_EQ(oneOptionComputer[0], "easy");
    ASSERT_EQ(oneOptionComputer[1], "None");
    ASSERT_EQ(oneOptionComputer[2], "None");
}

TEST(ParseTest, twoPlayersOption) {
    array<string, 3> computerVsHuman = parseOptions(vector<string>{ "--player", "medium", "--second-player", "human" });
    ASSERT_EQ(computerVsHuman[0], "medium");
    ASSERT_EQ(computerVsHuman[1], "human");
    ASSERT_EQ(computerVsHuman[2], "None");

    array<string, 3> computerVsComputer = parseOptions(vector<string>{ "--player", "hard", "--second-player", "hard" });
    ASSERT_EQ(computerVsComputer[0], "hard");
    ASSERT_EQ(computerVsComputer[1], "hard");
    ASSERT_EQ(computerVsComputer[2], "None");

    array<string, 3> humanVsHuman = parseOptions(vector<string>{ "--player", "human", "-p2", "human" });
    ASSERT_EQ(humanVsHuman[0], "human");
    ASSERT_EQ(humanVsHuman[1], "human");
    ASSERT_EQ(humanVsHuman[2], "None");

    array<string, 3> humanVsComputer = parseOptions(vector<string>{ "--player", "human", "-p2", "hard" });
    ASSERT_EQ(humanVsComputer[0], "human");
    ASSERT_EQ(humanVsComputer[1], "hard");
    ASSERT_EQ(humanVsComputer[2], "None");
}

TEST(ParseTest, startOption) {
    array<string, 3> firstPlayerStarts = parseOptions(vector<string>{ "--player", "medium", "--second-player", "human", "--start", "p1" });
    ASSERT_EQ(firstPlayerStarts[0], "medium");
    ASSERT_EQ(firstPlayerStarts[1], "human");
    ASSERT_EQ(firstPlayerStarts[2], "p1");

    array<string, 3> secondPlayerStarts = parseOptions(vector<string>{ "--player", "medium", "--start", "p2" });
    ASSERT_EQ(secondPlayerStarts[0], "medium");
    ASSERT_EQ(secondPlayerStarts[1], "None");
    ASSERT_EQ(secondPlayerStarts[2], "p2");
}


TEST(GameTest, initGameWhoStarts) {
    Board board{ };
    Game<HumanPlayer, HumanPlayer> gameStartsNone{ board, HumanPlayer{ board }, HumanPlayer{ board }, "None" };
    ASSERT_TRUE(gameStartsNone.getPlayerTurn() == 1 || gameStartsNone.getPlayerTurn() == 2) << gameStartsNone.getPlayerTurn();

    Game<HumanPlayer, HumanPlayer> gameStartsP1{ board, HumanPlayer{ board }, HumanPlayer{ board }, "p1" };
    ASSERT_TRUE(gameStartsP1.getPlayerTurn() == 1) << gameStartsP1.getPlayerTurn();

    Game<HumanPlayer, HumanPlayer> gameStartsP2{ board, HumanPlayer{ board }, HumanPlayer{ board }, "p2" };
    ASSERT_TRUE(gameStartsP2.getPlayerTurn() == 2) << gameStartsP2.getPlayerTurn();
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
