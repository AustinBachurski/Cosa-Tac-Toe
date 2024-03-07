#include "cosaGame.hpp"

#include <iostream>
#include <print>
#include <string>


int main()
{
    CosaGame game("./trace.txt");

    std::string input;

    while (game.gameRunning())
    {
        std::system("cls");
        std::print("{0}", game.gameBoard());
        std::print("{0}", game.gameMessage());

        std::cin >> input;
        game.runGameEngine(input);
    }
}
