#include <QApplication>
#include "game.h"

// main function for starting the game
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game *game = new Game();
    game->show();
    game->displayMainWindow();

    return a.exec();
}
