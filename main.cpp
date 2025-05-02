#include <QApplication>
#include "maingamewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameWindow game; // Create an instance of your GameWindow
    game.show();     // Show the game window

    return a.exec(); // Start the application event loop
}
