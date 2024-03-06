#include "cosaGame.hpp"

#include <iostream>
#include <string>


int main()
{
    CosaGame game("./trace.txt");

    std::string input;

    while (game.gameRunning())
    {
        std::system("cls");
        std::cout << game.gameBoard();
        std::cout << game.gameMessage();

        std::cin >> input;
        game.runGameEngine(input);
    }
}
