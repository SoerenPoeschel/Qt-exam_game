#include <QtGui>

#include "zeichenFeld.h"

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    lastX=100;
    lastY=100;
    lastX2=300;
    lastY2=100;
    increment=0;
    phase=0;
    increment2=0;
    phase2=0;
}

zeichenFeld::~zeichenFeld()
{
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter, painter2;
    int x, x2, y, y2, width, width2, height, height2;

    x=lastX-25;
    y=lastY-25;
    x2=lastX2+50;
    y2=lastY2-25;

    painter.begin( this );
    //linke obere Ecke: Breite == Höhe == 50

   // painter.drawEllipse(x,y,50,50);
   painter.drawText(x,y,QString("¯\\_(ツ)_/¯"));

    if (increment)
        switch(phase)
        {
        case 0:
            if (lastY<300) lastY=lastY+4;
            else phase=1;
            break;
        case 1:
            if (lastY==300) lastY=100;
            else phase=2;
            break;
        case 2:
            if (lastY>100) lastY--;
            else phase=0;
            break;
        }

    painter.end();




    painter2.begin( this );
    //linke obere Ecke: Breite == Hoehe == 50


    painter2.drawRoundedRect(x2,y2,50,50,10,10);
    //painter2.drawEllipse(x2,y2,50,50);
    //painter2.drawText(x2,y2,QString("¯\_(ツ)_/¯"));
    //painter2.drawPie(x2,y2, 100, 100, 0, 2400);

    if (increment2)
        switch(phase2)
        {
        case 0:
            if (lastY2<300) lastY2=lastY2+5;
            else phase2=1;
            break;
        case 1:
            if (lastY2==300) lastY2=100;
            else phase2=2;
            break;
        case 2:
            if (lastY2>100) lastY2--;
            else phase2=0;
            break;
        }

    painter2.end();
}
