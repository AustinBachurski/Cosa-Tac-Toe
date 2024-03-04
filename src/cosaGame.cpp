#include "cosaGame.hpp"

#include <algorithm>

CosaGame::CosaGame()
  : m_player{},
    m_inputString{},
    m_playAgain{},
    m_target{},
    m_timeIndex{ static_cast<int>(Time::validateFirstInput) }
{
    populateRulesTable();
}

void CosaGame::DrawBoard()
{
}

void CosaGame::RunGameEngine()
{
}

bool CosaGame::isValidInput()
{
    // TODO
}

bool CosaGame::isValidResponse()
{
    // TODO
}

bool CosaGame::playAgain()
{
    return m_playAgain == 'Y';
}

bool CosaGame::targetSpaceEmpty()
{
    return m_gameBoard[m_target] == ' ';
}

bool CosaGame::winConditionExists()
{
    return std::ranges::any_of(m_match, [this](auto indexes)
            {
                return m_gameBoard[indexes[0]] == m_gameBoard[indexes[1]]
                && m_gameBoard[indexes[0]] == m_gameBoard[indexes[2]];
            });
}

void CosaGame::closeGame()
{
}

void CosaGame::placeSymbol()
{
}

void CosaGame::requestFreeSpace()
{
}

void CosaGame::resetGameBoard()
{
}

void CosaGame::requestValidInput()
{
}

void CosaGame::setTargetValue()
{
}

void CosaGame::swapPlayerLabel()
{
}

void CosaGame::wantToPlayAgain()
{
}

void CosaGame::insertRule(int index, func state, proc trueProcedure,
        int trueNext, proc falseProcedure, int falseNext, int trace)
{
}

void CosaGame::populateRulesTable()
{
}
