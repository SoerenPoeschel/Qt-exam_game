#include "meinwidget.h"
// Qt5 add:
#include <QApplication>

//basierend auf zeichnen und bewegen 1.3

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    meinWidget w;
    w.setGeometry(100, 100, 500, 355);
    w.show();

    return a.exec();
}
