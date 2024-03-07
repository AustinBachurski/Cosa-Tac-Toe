#ifndef COSA_TAC_TOE_HPP
#define COSA_TAC_TOE_HPP

#include <array>
#include <filesystem>
#include <fstream>
#include <string>

class CosaGame
{
public:
    CosaGame(std::filesystem::path pathToTraceFile);
    std::string gameBoard() const;
    std::string gameMessage() const;
    bool gameRunning() const;
    void runGameEngine(const std::string& input);

private:
    // Using Directives
    using func = bool (CosaGame::*)(void) const;
    using proc = void (CosaGame::*)(void);

    // Matrix Indexes
    enum class Time
    {
        validatePlayerSelection,
        nextPlayer,
        validatePlacementInput,
        checkTargetSpace,
        checkForWin,
        checkForDraw,
        validatePlayAgainResponse,
        playAgain,

    };

    // States
    bool drawConditionExists() const;
    bool isValidInput() const;
    bool isValidResponse() const;
    bool isValidSelection() const;
    bool playAgain() const;
    bool playerIsX() const;
    bool targetSpaceEmpty() const;
    bool winConditionExists() const;

    // Behaviors
    void closeGame();
    void gameDraw();
    void gameOver();
    void ignore();
    void placeSymbol();
    void requestFreeSpace();
    void resetGame();
    void requestValidInput();
    void requestValidResponse();
    void requestValidSelection();
    void setTargetValue();
    void setPlayerToX();
    void setPlayerToO();
    void setPlayerValue();
    void traceTrue();
    void traceFalse();

    // Initialization
    void initializeTraceFile();
    void insertRule(
            Time index,
            func state,
            proc trueProcedure,
            Time trueNext,
            proc falseProcedure,
            Time falseNext,
            int trace);
    void populateRulesTable();

    // Game Members
    std::array<char, 9> m_gameBoard;
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
    std::string m_message;
    char m_player;

    // Cosa Members
    static constexpr int m_matrixRows = 8;
    std::ofstream m_traceFile;
    bool m_gameRunning = true;
    std::string m_inputString;
    bool m_engineRunning = true;
    int m_target;
    int m_timeIndex;

    // Cosa Matrix Row
    struct tGame {
        func state;
        proc trueProcedure;
        int trueNext;
        proc falseProcedure;
        int falseNext;
        int trace;
    };

    // Cosa Matrix and Trace Table
    std::array<tGame, m_matrixRows> m_logic;
    std::array<std::string, m_matrixRows> m_trace;
};

#endif
