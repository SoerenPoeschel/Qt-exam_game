#include "meinwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    meinWidget widget;
    widget.setGeometry(100, 100, 500, 355);
    widget.show();
    return app.exec();
}

//I created this project to solve one of the first tasks: to move the avatar square with the arrow keys
//In order to do so I will try to set up a QKeyEvent for the left arrow key and for the right arrow key
//but first I need to create the square
