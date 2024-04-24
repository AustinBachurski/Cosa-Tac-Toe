#include "cosaGame.hpp"

#include <iostream>
#include <string>


int main()
{
    CosaGame game("./trace.txt");

    std::string input;

    while (game.gameRunning())
    {
        #ifdef _WIN32
        std::system("cls");
        #else
        std::system("clear");
        #endif

        std::cout << game.gameBoard();
        std::cout << game.gameMessage();

        std::cin >> input;
        game.runGameEngine(input);
    }
}
