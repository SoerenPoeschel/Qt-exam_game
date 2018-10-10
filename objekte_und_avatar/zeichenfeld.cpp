#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "zeichenfeld.h"
//#include <QApplication>
#include "makros.h"

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{

    setPalette(QPalette(QColor(170, 190, 250)));
    setAutoFillBackground(true);
    setMouseTracking(false);
    grabKeyboard(); //sorgt dafür

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    increment=0;
    increment_o1=0;
    increment_o2=0;
    increment_o3=0;
    increment_counter=0;
    phase=0;
    phase2=0;
    phase3=0;
    phase_counter=0;
    playerX=475;
    lastY1=50;
    lastY2=50;
    lastY3=50;
    counter=0;
    count=0;
    lifes=3;

    spielFeld.setCoords(50,100, WIDTH-50, HEIGHT-100);
}

zeichenFeld::~zeichenFeld()
{
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter_player, painter_object1, painter_object2, painter_object3, painter_counter, painter_lifes;
    QRect rect;//, spielFeld; //rect ist der Avatar, spielFeld soll das Clip Rect für die Objecte sein

    int y1, y2, y3;


    //spielFeld.setCoords(50,100, WIDTH-50, HEIGHT-100);

    painter_player.begin( this );
    painter_player.setClipRect(25,650,950,200); //Bereich in dem der painter zeichnet
    painter_player.setPen(QPen(Qt::gray, 1)); //Rahmen des players
    painter_player.setBrush(QBrush(QColor(125, 243, 92)));
    //hab das mal hinzugefügt, weil ich denke, dass die Grundfarbe dann meine ist ¯\_(ツ)_/¯
    painter_player.setBrush(QBrush(QColor(125, 243, 92), Qt::BDiagPattern)); //BDiagPattern um Avatar zu schraffieren
    rect.setSize(QSize (50,50));

    rect.moveTo(playerX, 700);
    painter_player.drawRect(rect);

    painter_player.end();

/*//Hab den painter für das erste Object gebaut
    painter_object1.begin(this);

    y1=lastY1-50;

    painter_object1.drawEllipse(X_OBJECT1, y1,50,50);
    painter_object1.setClipRect(spielFeld);

    if (increment_o1)
        switch(phase)
            /* eigentlich brauche ich den switch case nicht,
              es sollte möglich sein immer ein neues Objekt zu erstellen,
              wenn die clipRegion verlassen wurde

              also mache ich drawElipse und moveTo,
              das Konzept ist, dass nicht jedes mal der y Wert auf null gesetzt wird,
              sondern, dass der painter glöscht wird, wenn er nicht mehr im spielFeld ist
              und ein neuer bei null anfängt

              die Absicht ist dann halt, dass ich alle Gegenstände mit derselben Funktion in
                unterschiedlichen Geschwindigkeiten, an unterschiedlichen Positionen bewegen kann
            *
        {
        case 0:
            if (lastY1<HEIGHT) lastY1=lastY1+4;
            else phase=1;
            break;
        case 1:
            if (lastY1==HEIGHT) lastY1=100;
            else phase=2;
            break;
        case 2:
            if (lastY1>100) lastY1=lastY1-800;
            else phase=0;
            //cout << "also incrment ist an";
            break;
        }

    painter_object1.end();*/

    objekt1.update();

//zweites Objekt
    painter_object2.begin(this);

    y2=lastY2-50;


    painter_object2.drawRect(X_OBJECT2, y2,50,50);
    painter_object2.setClipRect(spielFeld);

    if (increment_o2)
        switch(phase2)
        {
        case 0:
            if (lastY2<HEIGHT) lastY2=lastY2+3;
            else phase2=1;
            break;
        case 1:
            if (lastY2==HEIGHT) lastY2=100;
            else phase2=2;
            break;
        case 2:
            if (lastY2>100) lastY2=lastY2-800;
            else phase2=0;
            //cout << "also incrment ist an";
            break;
        }

    painter_object2.end();

//drittes Objekt
    painter_object3.begin(this);
    y3=lastY3-50;

    painter_object3.drawChord(QRect(X_OBJECT3, y3, 50,50), 30*16, 120*16);//(X_OBJECT3, y3,50,50);
    painter_object3.setClipRect(spielFeld);

    if (increment_o3)
        switch(phase3)
        {
        case 0:
            if (lastY3<HEIGHT) lastY3=lastY3+7;
            else phase3=1;
            break;
        case 1:
            if (lastY3==HEIGHT) lastY3=100;
            else phase3=2;
            break;
        case 2:
            if (lastY3>100) lastY3=lastY3-800;
            else phase3=0;
            //cout << "also incrment ist an";
            break;
        }

    painter_object3.end();

    painter_counter.begin(this);
    painter_counter.setPen(QColor(222,22,2));


    painter_counter.drawText(10,20, QString::number(counter,10)); //number enables drawText to use an int as a string

            if(count<30)count++;                      //in order to make a 'slow' and readable counter, it only increases everytime count has increased from 0 to 30
             else{counter++; count=0;};

    painter_counter.end();

    if(lifes>0)
    {
        painter_lifes.begin(this);
        painter_lifes.setBrush(QBrush(QColor(222,22,2)));
        painter_lifes.setPen(QColor(222,22,2));

        if(lifes==3)
        {
            painter_lifes.drawEllipse(980,5,10,10);
            painter_lifes.drawEllipse(965,5,10,10);
            painter_lifes.drawEllipse(950,5,10,10);
        }
        else if(lifes==2)
        {
            painter_lifes.drawEllipse(980,5,10,10);
            painter_lifes.drawEllipse(965,5,10,10);
        }
        else if(lifes==1)
        {
            painter_lifes.drawEllipse(980,5,10,10);
        }


        painter_lifes.end();
    }

}

void zeichenFeld::keyPressEvent(QKeyEvent *event)
{

    QEvent::ShortcutOverride; //https://forum.qt.io/topic/26051/solved-priority-of-qkeysequence-over-keypressevent/8

//if event: left arrow-> QRect::moveLeft(int x); if event: right arrow -> QRect::moveRight(int x)
//Hab das mit start connected
    if(increment)
        switch (event->key()){
            case Qt::Key_Left: //auf application level überarbeiten
            case Qt::Key_Direction_L:
            case Qt::LeftArrow:
            case Qt::Key_A:
                //leftKey=1;
                playerX = playerX + 25 >= 0 ? playerX-15 : 0 ;
            break;
            case Qt::Key_Right: //auf application level überarbeiten
            case Qt::Key_Direction_R:
            case Qt::RightArrow:
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


