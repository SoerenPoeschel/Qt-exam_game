#include <QtGui>

#include "zeichenfeld.h"

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(170, 190, 250)));
    setAutoFillBackground(true);
    setMouseTracking(false);
}

zeichenFeld::~zeichenFeld()
{
    for (vector<QRect *>::iterator pos=rects.begin();pos!=rects.end();pos++)
        delete *pos;
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter;
    vector<QRect *>::iterator pos,start;

    painter.begin( this );
    painter.setPen( QPen(Qt::gray, 3) );
    painter.setBrush(QBrush(QColor(125, 243, 92), Qt::BDiagPattern)); //BDiagPattern um Avatar zu schraffieren
    if (rects.size()>1)
    {
        pos=rects.begin();
        for(;;)
        {
            start=pos;
            pos++;
            if (pos==rects.end()) break;
            painter.drawLine(**start,**pos);
        }
        painter.end();
    }

}
/*
void zeichenFeld::mouseMoveEvent(QMouseEvent *event)
{
    QPoint *point;

    point=new QPoint;
    point->setX(event->x());
    point->setY(event->y());
    points.push_back(point);

    update();
}*/

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{
    QRect *rect;
//if event: left arrow-> QRect::moveLeft(int x); if event: right arrow -> QRect::moveRight(int x)
    rect=new QRect;
    rect->setX(x);
    rect->setBottom(int (100));
    rect->setSize(QSize (10,10));
    rect->setBrush(QBrush);
    rects.push_back(rect);
    //nächster Versuch: QPoint wiederherstellen und Avatar mit [void QRect::moveCenter(const QPoint &position)] bewegen
    //dafür QPoint in ein QKeyEvent umschreiben
    //Vorher die genaue Funktion und den Sinn von QPoint erörtern/erfragen
    //Kompatibilität auf viele Objekte bedenken
    
    update();
}


