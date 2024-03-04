#ifndef COSA_TAC_TOE_HPP
#define COSA_TAC_TOE_HPP

#include <array>
#include <string>

class CosaGame
{
public:
    CosaGame();
    void DrawBoard();
    void RunGameEngine();

private:
    // States
    bool isValidInput();
    bool isValidResponse();
    bool playAgain();
    bool targetSpaceEmpty();
    bool winConditionExists();

    // Behaviors
    void closeGame();
    void placeSymbol();
    void requestFreeSpace();
    void resetGameBoard();
    void requestValidInput();
    void requestValidResponse();
    void setPlayAgainResponse();
    void setTargetValue();
    void swapPlayerLabel();
    void wantToPlayAgain();

    // Game Members
    std::array<char, 9> m_gameBoard;
    char m_player;
    std::array<std::array<int, 3>, 8> m_match = {{
        { 0, 1, 2 },
        { 3, 4, 5 },
        { 6, 7, 8 },
        { 0, 3, 6 },
        { 1, 4, 7 },
        { 2, 5, 8 },
        { 0, 4, 8 },
        { 2, 4, 6 }
    }};

    // Cosa Members
    static constexpr int m_matrixRows = 7;
    std::string m_inputString;
    char m_playAgain;
    int m_target;
    int m_timeIndex;

    // Using Directives
    using func = bool (CosaGame::*)(void);
    using proc = void (CosaGame::*)(void);

    // Cosa Matrix
    struct tGame {
        func state;
        proc trueProcedure;
        int trueNext;
        proc falseProcedure;
        int falseNext;
        int trace;
    };

    std::array<tGame, m_matrixRows> m_logic;
    std::array<std::string, m_matrixRows> m_trace;

    // Matrix Indexes
    enum class Time
    {
        validateFirstInput,
        goFirst,
        validatePlacementInput,
        checkTargetSpace,
        checkForWin,
        validatePlayAgainResponse,
        playAgain,
    };

    // Initialization
    void insertRule(
            int index,
            func state,
            proc trueProcedure,
            int trueNext,
            proc falseProcedure,
            int falseNext,
            int trace);
    void populateRulesTable();
};

#endif
