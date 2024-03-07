#include "cosaGame.hpp"

#include <algorithm>
#include <print>

CosaGame::CosaGame(const std::filesystem::path pathToTraceFile)
  : m_player{},
    m_traceFile{ pathToTraceFile, std::ios::out | std::ios::trunc },
    m_inputString{},
    m_target{},
    m_timeIndex{ 0 }
{
    initializeTraceFile();
    populateRulesTable();
    resetGame();
}

std::string CosaGame::gameBoard() const
{
    return 
        "|-----------------------------|\n"
        "|7        |8        |9        |\n"
        "|    " + std::string{m_gameBoard[6]} + "    |    " + std::string{m_gameBoard[7]} + "    |    " + std::string{m_gameBoard[8]} + "    |\n"
        "|         |         |         |\n"
        "|-----------------------------|\n"
        "|4        |5        |6        |\n"
        "|    " + std::string{m_gameBoard[3]} + "    |    " + std::string{m_gameBoard[4]} + "    |    " + std::string{m_gameBoard[5]} + "    |\n"
        "|         |         |         |\n"
        "|-----------------------------|\n"
        "|1        |2        |3        |\n"
        "|    " + std::string{m_gameBoard[0]} + "    |    " + std::string{m_gameBoard[1]} + "    |    " + std::string{m_gameBoard[2]} + "    |\n"
        "|         |         |         |\n"
        "|-----------------------------|\n";
}

std::string CosaGame::gameMessage() const
{
    return m_message;
}

bool CosaGame::drawConditionExists() const
{
    return std::ranges::none_of(m_gameBoard, [](char c)
            {
                return c == ' ';
            });
}

bool CosaGame::gameRunning() const
{
    return m_gameRunning;
}

bool CosaGame::isValidInput() const
{
    return m_inputString.size() == 1
        && m_inputString.front() >= '1'
        && m_inputString.front() <= '9';
}

bool CosaGame::isValidResponse() const
{
    return m_inputString.size() == 1
        && m_inputString.front() == 'y'
        || m_inputString.front() == 'Y'
        || m_inputString.front() == 'n'
        || m_inputString.front() == 'N';
}

bool CosaGame::isValidSelection() const
{
    return m_inputString.size() == 1
        && m_inputString.front() == 'x'
        || m_inputString.front() == 'X'
        || m_inputString.front() == 'o'
        || m_inputString.front() == 'O';
}

bool CosaGame::playAgain() const
{
    return m_inputString.front() == 'y' || m_inputString.front() == 'Y';
}

bool CosaGame::playerIsX() const
{
    return m_player == 'X';
}

void CosaGame::runGameEngine(const std::string& input)
{
    m_inputString = input;
    m_engineRunning = true;
    while (m_engineRunning && m_gameRunning)
    {
        if ((this->*(m_logic[m_timeIndex].state))())
        {
            (this->*(m_logic[m_timeIndex].trueProcedure))();
            traceTrue();
            m_timeIndex = m_logic[m_timeIndex].trueNext;
        }
        else
        {
            (this->*(m_logic[m_timeIndex].falseProcedure))();
            traceFalse();
            m_timeIndex = m_logic[m_timeIndex].falseNext;
        }
    }
}

bool CosaGame::targetSpaceEmpty() const
{
    return m_gameBoard[m_target] == ' ';
}

bool CosaGame::winConditionExists() const
{
    return std::ranges::any_of(m_match, [this](auto indexes)
            {
                return std::ranges::all_of(indexes, [this](int index)
                        {
                            return m_gameBoard[index] == m_player;
                        });
            });
}

void CosaGame::closeGame()
{
    m_gameRunning = false;
}

void CosaGame::ignore()
{
    return;
}

void CosaGame::placeSymbol()
{
    m_gameBoard[m_target] = m_player;
    // Engine remains ON.
}

void CosaGame::requestFreeSpace()
{
    m_message = "That space is already taken, please select an empty space.\n:> ";
    m_engineRunning = false;
}

void CosaGame::resetGame()
{
    m_gameBoard.fill(' ');
    m_message = "Welcome to Tic-Tac-Toe,"
        " please choose which player goes first: 'X' or 'O'.\n:> ";
    m_engineRunning = false;
}

void CosaGame::requestValidInput()
{
    m_message = "Input can only be a board space: '1', '2', '3', etc."
        "please enter a valid space.\n:> ";
    m_engineRunning = false;
}

void CosaGame::requestValidResponse()
{
    m_message = "Input can only be 'Y' or 'N', please enter a valid response.\n:> ";
    m_engineRunning = false;
}

void CosaGame::requestValidSelection()
{
    m_message = "Input can only be 'X' or 'O', please enter a valid option.\n:> ";
    m_engineRunning = false;
}

void CosaGame::setTargetValue()
{
    m_target = static_cast<int>(m_inputString.front() - '1');
    // Engine remains ON.
}

void CosaGame::setPlayerToX()
{
    m_player = 'X';
    m_message = "Player X' turn - select a space on the board (1-9).\n:> ";
    m_engineRunning = false;
}

void CosaGame::setPlayerToO()
{
    m_player = 'O';
    m_message = "Player O's turn - select a space on the board (1-9).\n:> ";
    m_engineRunning = false;
}

void CosaGame::setPlayerValue()
{
    m_player = std::toupper(m_inputString.front());
    m_message = "Player " + std::string{m_player} + "'s turn - select a space on the board (1-9).\n:> ";
    m_engineRunning = false;
}

void CosaGame::gameDraw()
{
    m_message = "The game is a draw, lame... Do you want to play again 'Y'/'N'?\n:> ";
    m_engineRunning = false;
}

void CosaGame::gameOver()
{
    m_message = "Game over, " + std::string{ m_player } + " wins."
        " Do you want to play again 'Y'/'N'?\n:> ";
    m_engineRunning = false;
}

void CosaGame::traceFalse()
{
    m_traceFile << "False     " << m_trace[m_timeIndex] << '\n';
    m_traceFile.flush();
}

void CosaGame::traceTrue()
{
    m_traceFile << "True      " << m_trace[m_timeIndex] << '\n';
    m_traceFile.flush();
}

void CosaGame::initializeTraceFile()
{
    m_traceFile <<
        "Introspective Trace for Tic-Tac-Toe\n"
        "                                                                                  True                            True                                False                               False\n"
        "Evaluation       Rule                             State                           Behavior                        Next                                Behavior                            Next                                Trace\n"
        "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    m_traceFile.flush();
}

void CosaGame::insertRule(Time index, func state, proc trueProcedure,
        Time trueNext, proc falseProcedure, Time falseNext, int trace)
{
    m_logic.at(static_cast<int>(index)).state = state;
    m_logic.at(static_cast<int>(index)).trueProcedure = trueProcedure;
    m_logic.at(static_cast<int>(index)).trueNext = static_cast<int>(trueNext);
    m_logic.at(static_cast<int>(index)).falseProcedure = falseProcedure;
    m_logic.at(static_cast<int>(index)).falseNext = static_cast<int>(falseNext);
    m_logic.at(static_cast<int>(index)).trace = trace;
}

void CosaGame::populateRulesTable()
{
    // Cosa Matrix
    //                                                                           True                            True                                False                               False
    //          Rule                             State                           Behavior                        Next                                Behavior                            Next                                Trace
    insertRule( Time::validatePlayerSelection,   &CosaGame::isValidSelection,    &CosaGame::setPlayerValue,      Time::validatePlacementInput,       &CosaGame::requestValidSelection,   Time::validatePlayerSelection,      100    );

    insertRule( Time::nextPlayer,                &CosaGame::playerIsX,           &CosaGame::setPlayerToO,        Time::validatePlacementInput,       &CosaGame::setPlayerToX,            Time::validatePlacementInput,       300    );

    insertRule( Time::validatePlacementInput,    &CosaGame::isValidInput,        &CosaGame::setTargetValue,      Time::checkTargetSpace,             &CosaGame::requestValidInput,       Time::validatePlacementInput,       500    );
    insertRule( Time::checkTargetSpace,          &CosaGame::targetSpaceEmpty,    &CosaGame::placeSymbol,         Time::checkForWin,                  &CosaGame::requestFreeSpace,        Time::validatePlacementInput,       501    );
    insertRule( Time::checkForWin,               &CosaGame::winConditionExists,  &CosaGame::gameOver,            Time::validatePlayAgainResponse,    &CosaGame::ignore,                  Time::checkForDraw,                 502    );
    insertRule( Time::checkForDraw,              &CosaGame::drawConditionExists, &CosaGame::gameDraw,            Time::validatePlayAgainResponse,    &CosaGame::ignore,                  Time::nextPlayer,                   503    );

    insertRule( Time::validatePlayAgainResponse, &CosaGame::isValidResponse,     &CosaGame::ignore,              Time::playAgain,                    &CosaGame::requestValidResponse,    Time::validatePlayAgainResponse,    700    );
    insertRule( Time::playAgain,                 &CosaGame::playAgain,           &CosaGame::resetGame,           Time::validatePlayerSelection,      &CosaGame::closeGame,               Time::validatePlayerSelection,      702    );


    // Trace Messages

    m_trace.at(static_cast<int>(Time::validatePlayerSelection)) = 
        "       Time::validatePlayerSelection,   &CosaGame::isValidSelection,    &CosaGame::setPlayerValue,      Time::validatePlacementInput,       &CosaGame::requestValidSelection,   Time::validatePlayerSelection,      100";

    m_trace.at(static_cast<int>(Time::nextPlayer)) = 
        "       Time::nextPlayer,                &CosaGame::playerIsX,           &CosaGame::setPlayerToO,        Time::validatePlacementInput,       &CosaGame::setPlayerToX,            Time::validatePlacementInput,       300";

    m_trace.at(static_cast<int>(Time::validatePlacementInput)) = 
        "       Time::validatePlacementInput,    &CosaGame::isValidInput,        &CosaGame::setTargetValue,      Time::checkTargetSpace,             &CosaGame::requestValidInput,       Time::validatePlacementInput,       500";
    m_trace.at(static_cast<int>(Time::checkTargetSpace)) = 
        "       Time::checkTargetSpace,          &CosaGame::targetSpaceEmpty,    &CosaGame::placeSymbol,         Time::checkForWin,                  &CosaGame::requestFreeSpace,        Time::validatePlacementInput,       501";
    m_trace.at(static_cast<int>(Time::checkForWin)) = 
        "       Time::checkForWin,               &CosaGame::winConditionExists,  &CosaGame::gameOver,            Time::validatePlayAgainResponse,    &CosaGame::ignore,                  Time::checkForDraw,                 502";

    m_trace.at(static_cast<int>(Time::checkForDraw)) = 
        "       Time::checkForDraw,              &CosaGame::drawConditionExists, &CosaGame::gameDraw,            Time::validatePlayAgainResponse,    &CosaGame::ignore,                  Time::nextPlayer,                   503";

    m_trace.at(static_cast<int>(Time::validatePlayAgainResponse)) = 
        "       Time::validatePlayAgainResponse, &CosaGame::isValidResponse,     &CosaGame::ignore,              Time::playAgain,                    &CosaGame::requestValidResponse,    Time::validatePlayAgainResponse,    700";
    m_trace.at(static_cast<int>(Time::playAgain)) = 
        "       Time::playAgain,                 &CosaGame::playAgain,           &CosaGame::resetGame,           Time::validatePlayerSelection,      &CosaGame::closeGame,               Time::validatePlayerSelection,      702";
}

