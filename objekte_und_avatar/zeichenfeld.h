#ifndef ZEICHENFELD_H
#define ZEICHENFELD_H

#include <vector>
using namespace std;
#include <QWidget>
#include <QTimer>
#include "fallendesobjekt.h"
#include "makros.h"

class zeichenFeld : public QWidget //mann ey, warum bekomme ich da previously denfined/redifinition errors?
{
  // Q_OBJECT
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    void start(void) { timer->start(40); increment=1; increment_o1=1; increment_o2=1; increment_o3=1;}
    void stop(void) { timer->stop(); increment=0; increment_o1=0; increment_o2=0; increment_o3=0;}
    void keyPressEvent(QKeyEvent *event);


private:
    QTimer *timer;
    QRect spielFeld;

    int lifes;
    int playerX;
    int lastY1;
    int lastY2;
    int lastY3;
    int counter;
    int count;
    int increment;
    int increment_o1;
    int increment_o2;
    int increment_o3;
    int increment_counter;
    int phase;
    int phase2;
    int phase3;
    int phase_counter;

    fallendesObjekt objekt1 = fallendesObjekt(4, X_OBJECT1, this, spielFeld);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif
