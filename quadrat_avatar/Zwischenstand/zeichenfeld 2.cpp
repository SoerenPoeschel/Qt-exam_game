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
}

zeichenFeld::~zeichenFeld()
{
    for (vector<QPoint *>::iterator pos=points.begin();pos!=points.end();pos++)
        delete *pos;
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter (this);
    vector<QPoint *>::iterator pos,start;

    painter.begin( this );
    painter.setPen( QPen(Qt::gray, 3) );
    painter.setBrush(QBrush(QColor(125, 243, 92), Qt::BDiagPattern)); //BDiagPattern um Avatar zu schraffieren

    if (points.size()>1)
    {
        pos=points.begin();
        for(;;)
        {
            start=pos;
            pos++;
            if (pos==points.end()) break;
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

// Ich kann zwar nicht genau sagen warum aber ich vermute mal, dass ich eine funktion für das KeyPressEvent und den Point, sowie eine für das Rechteck brauche, wenn ich an meiner Vorgehensweise festhalten will.
//Dem folgend würde ich weitere Punkte für die anderen Objekte machen, obwohl das wahrscheinlich nicht nötig ist
//Also nur get und set...

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{
    QPoint *point;

    point=new QPoint;
    point->setX(playerX /*if key==left x=x+z else if key==right x=x-z*/);
    point->setY(100/*bottom - where is it anyways?*/);
    //QKeyEvent as no member named "x", probably I need to make two events,
    // for right and left arrow and y is static btw
    points.push_back(point);



    QRect *rect;
//if event: left arrow-> QRect::moveLeft(int x); if event: right arrow -> QRect::moveRight(int x)
    rect=new QRect;
    //rect->setX();
    //rect->setBottom(int (100)); //wird beides nicht gebraucht, wenn das rect immer beim point ist, glaub ich
    rect->setSize(QSize (10,10));
    //rect->setBrush(QBrush); //damit das Rechteck schraffiert ist, so wie hier funtkioniert es nicht,
    // weil QBrush keine Subclass von QRect ist, sondern ein Geschwister in QPeinter
    //soll ich dat janze vielleischt nur mit dem peenter und drawRect machen?
    //-> nö, weil dann kann ich evtl move Center nischt so praktisch benutzen
    rect->center();
    rect->moveLeft(playerX);
    //Wenn ich moveLeft mit dem Timer verknüpfe und drei Modi mache (x++,x-- und x=x) kann immer wieder ein neuer move befehl benutzt werden
    //std::invoke(rect, point, **pos);
            //dit muss aus dem paintEvent gecalled werden glaube ich,
            //also halt über das struct myPoint in mehr maeuse5 ::load
            //bisher ist hier ja nur der vector QPoint aber wahrscheinlich brauche ich myPoint
            //das Problem könnte dann halt sein, dass ich einen QPoint für moveCenter brauche
            //also muss ich es irgendwie schaffen beides zu vereinbaren
            //die Sache ist ja, daseine Speichern/Laden Funktion im Programm sein soll, deshalb müssen diese Funktionen auch auf pos zugreifen können
            //in der Dokumentation steht (const QPoint &position) also muss der call evtl. mit einem & passieren, was die Fehlermeldung ja auch nahegelegt hat
    //wenn ick dat so laufen ließe wie da jetze is, würde dann nischt ein Balken jemalt werdön, weil dat rect ja nie jelöscht wörd????
    //?.push_back(rect);
    //nächster Versuch: QPoint wiederherstellen und Avatar mit [void QRect::moveCenter(const QPoint &position)] bewegen
    //dafür QPoint in ein QKeyEvent umschreiben
    //Vorher die genaue Funktion und den Sinn von QPoint erörtern/erfragen
    //Kompatibilität auf viele Objekte bedenken
    // ick will ein QPoint und ein QRect und in dem QRect soll die Position vom Point benutzt werden für moveCenter
    // Qpoint will ick mit den Feieltasten bewegen
    
    update();
}


