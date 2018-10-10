#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "zeichenfeld.h"
#define WIDTH 1000
#define HEIGHT 800
#define SQUARE_DIMENSION 50
#define X_OBJECT1 100
#define X_OBJECT2 500
#define X_OBJECT3 750

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(170, 190, 250)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    increment=0;
    increment_o1=0;
    phase=0;
    playerX=475;
    lastY1=50;
}

zeichenFeld::~zeichenFeld()
{
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter_player, painter_object1, painter_object2, painter_object3;
    QRect rect;

    int y1, y2, y3;

    painter_player.begin( this );
    painter_player.setClipRect(25,650,950,200); //Bereich in dem der painter zeichnet
    painter_player.setPen( QPen(Qt::gray, 1) ); //Rahmen des players
    painter_player.setBackground(QBrush(QColor(125, 243, 92)));
    //hab das mal hinzugefügt, weil ich denke, dass die Grundfarbe dann meine ist ¯\_(ツ)_/¯
    painter_player.setBrush(QBrush(QColor(125, 243, 92), Qt::BDiagPattern)); //BDiagPattern um Avatar zu schraffieren
    rect.setSize(QSize (50,50));

    rect.moveTo(playerX, 700);
    painter_player.drawRect(rect);

    painter_player.end();

//Hab den painter für das erste Object gebaut
    painter_object1.begin(this);

    y1=lastY1-50;

    painter_object1.drawEllipse(X_OBJECT1, y1,50,50);

    if (increment_o1)
        cout << "increment";
        switch(phase)
        {
        case 0:
            if (lastY1<300) lastY1=lastY1+4;
            else phase=1;
            break;
        case 1:
            if (lastY1==300) lastY1=100;
            else phase=2;
            break;
        case 2:
            if (lastY1>100) lastY1--;
            else phase=0;
            break;
        }

    painter_object1.end();

}

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{

//if event: left arrow-> QRect::moveLeft(int x); if event: right arrow -> QRect::moveRight(int x)
//Hab das mit start connected
    if(increment)
        switch (event->key()){
            case Qt::Key_Left: //auf application level überarbeiten
            case Qt::Key_A:
            //leftKey=1;
                playerX = playerX + 25 >= 0 ? playerX-15 : 0 ;
            break;
            case Qt::Key_Right: //auf application level überarbeiten
            case Qt::Key_D:
                //rightKey=1;
                playerX = playerX + SQUARE_DIMENSION + 25 <= WIDTH ? playerX + 15 : WIDTH - SQUARE_DIMENSION;
            break;
        default:
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


