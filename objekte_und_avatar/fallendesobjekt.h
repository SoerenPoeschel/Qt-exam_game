#ifndef FALLENDESOBJEKT_H
#define FALLENDESOBJEKT_H

#include <QWidget>
#include <QRect>
#include "makros.h"


class fallendesObjekt
{
public:
    fallendesObjekt(int speed, int x, QWidget* zeichenFeld, QRect spielFeld);
    void update();
private:
    int speed;
    int x;
    QWidget* zeichenfeld;
    QRect spielFeld;
    int lastY1 = 0;
    int phase = 0;
};

#endif // FALLENDESOBJEKT_H
