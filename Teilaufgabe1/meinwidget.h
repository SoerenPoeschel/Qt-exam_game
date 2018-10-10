#include <QWidget>
#include <QtGui>
#include <QJsonObject>
#include "zeichenfeld.h"


class meinWidget : public QWidget
{
    Q_OBJECT

public:
    meinWidget(QWidget *parent = 0);

private:
    zeichenFeld *meinZeichenFeld;

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void start(void);
    void stop(void);
    void saveGame(void);
    void loadGame(void);
};
