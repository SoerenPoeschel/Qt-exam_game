#include <QWidget>
#include <QtGui>
#include "zeichenfeld.h"

class meinWidget : public QWidget
{
    Q_OBJECT

public:
    meinWidget(QWidget *parent = 0);

private:

    zeichenFeld *meinZeichenFeld;

    std::chrono::time_point<std::chrono::system_clock> time_last_pressed;

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void start(void);
    void stop(void);
    /*hab gerade erst den private und die slots hinzugefügt, weil ich die while Schleife für
   die Avatar Bewegungen mit den Start/Pausefunktionen verknüpfen möchte,
   seitdem bekomme ich in zeichenfeld.h den Fehler "redifinition of 'class zeichenFeld'
   den Code dafür hatte ich aus zeichnen_und_bewegen 3*/
};
