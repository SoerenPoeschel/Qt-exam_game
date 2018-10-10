#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "zeichenfeld.h"

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(170, 190, 250)));
    setAutoFillBackground(true);
    setMouseTracking(false);
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    increment=0;
    phase=0;
    playerX=475;
}

zeichenFeld::~zeichenFeld()
{
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter (this);
    QRect rect;
    //http://doc.qt.io/qt-5/qregion.html#details um den Bewegungsbereich fest zu legen
    /*etwa so:
    QRegion reg(QRect(00, 700, 1000, 100));

    painter.setClipRegion(reg);*/

    painter.begin( this );
    painter.setPen( QPen(Qt::gray, 1) );
    painter.setBrush(QBrush(QColor(125, 243, 92), Qt::BDiagPattern)); //BDiagPattern um Avatar zu schraffieren

    rect.setSize(QSize (50,50));

    if (increment)
        switch(phase)
        {
        case 0:
            if (leftKey)playerX--;
            else phase=1;
            break;
        case 1:
            if (rightKey) playerX++;
            else phase=2;
            break;
        case 2:
            if (noKey) playerX=playerX;
            else phase=0;
            break;
        }

    rect.moveTo(playerX, 700);
    painter.drawRect(rect);

    painter.end();

}

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{

//if event: left arrow-> QRect::moveLeft(int x); if event: right arrow -> QRect::moveRight(int x)
    switch (event->key()){
    case Qt::Key_Left:
        leftKey=1;
        break;
    case Qt::Key_Right:
        rightKey=1;
    default:
        //noKey=1;
        break;
    }
    //rect->setBrush(QBrush); //damit das Rechteck schraffiert ist, so wie hier funtkioniert es nicht,
    // weil QBrush keine Subclass von QRect ist, sondern ein Geschwister in QPeinter
    //soll ich dat janze vielleischt nur mit dem peenter und drawRect machen?
    //-> nö, weil dann kann ich evtl move Center nischt so praktisch benutzen
    ;

    //Wenn ich moveLeft mit dem Timer verknüpfe und drei Modi mache (x++,x-- und x=x) kann immer wieder ein neuer move befehl benutzt werden

    
    update();
}


