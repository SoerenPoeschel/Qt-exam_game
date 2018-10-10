#include <QWidget>
#include <QtGui>
#include <QJsonObject> //including the class for the save/load functions using json data format
#include "zeichenfeld.h"


class meinWidget : public QWidget
{
    Q_OBJECT

public:
    meinWidget(QWidget *parent = 0);

private:
    zeichenFeld *meinZeichenFeld; //child that handles the core game objects

protected:
    void keyPressEvent(QKeyEvent* event); //necessary to hand the KeyEvent over to zeichenFeld

private slots:
    void start(void); //begins the game
    void stop(void); //pauses the game
    void saveGame(void); //handles IO DataStream, using 'save' from zeichenFeld
    void loadGame(void); //handles IO DataStream, using 'load' from zeichenFeld
};
