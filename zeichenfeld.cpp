#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "zeichenfeld.h"
//#include <QApplication>
#define WIDTH 1000
#define HEIGHT 800
#define SQUARE_DIMENSION 50
#define X_OBJECT1 100
#define X_OBJECT2 475
#define X_OBJECT3 850



zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
        // don't know where to use this fix either:   QWidgetLineControl::processShortcutOverrideEvent(QKeyEvent *ke);
        //got it from https://wiki.qt.io/ShortcutOverride
    //doesn't do it, probably wrong place setFocusPolicy(Qt::FocusPolicy (0x8)); //storng Focus in order to get the arrow keys
    //QApplication::setNavigationModeQt::NavigationModeCursorAuto;//supposed to make the navigation not use arrow keys any more
    //only works on embedded Linux https://doc.qt.io/qt-5/qapplication.html#setNavigationMode
    setPalette(QPalette(QColor(170, 190, 250)));
    setAutoFillBackground(true);
    setMouseTracking(false);
    grabKeyboard(); //sorgt dafür, dass zeichenFeld auch die Eingaben der Pfailtasten bekommt

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
}

zeichenFeld::~zeichenFeld()
{
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter_player, painter_object1, painter_object2, painter_object3, painter_counter, painter_lifes;
    QRect rect, spielFeld; //rect ist der Avatar, spielFeld soll das Clip Rect für die Objecte sein

    int y1, y2, y3;


    spielFeld.setCoords(50,100, WIDTH-50, HEIGHT-100); //defintion of the QRect in which the falling objects painters will draw

    painter_player.begin( this );
    painter_player.setClipRect(25,650,950,200); //setting the square in which the painter_player will draw
    painter_player.setPen(QPen(Qt::gray, 1)); //frame of the player
    painter_player.setBrush(QBrush(QColor(125, 243, 92)));
    painter_player.setBrush(QBrush(QColor(125, 243, 92), Qt::BDiagPattern)); //BDiagPattern to hatch the player rectangle
    rect.setSize(QSize (50,50));

    rect.moveTo(playerX, 700);
    painter_player.drawRect(rect);

    painter_player.end();

//Fallling Objects using macros for their x coordinates	
//Erstes Objekt	
    painter_object1.begin(this);

    y1=lastY1-50;

    painter_object1.drawEllipse(X_OBJECT1, y1,50,50);
    painter_object1.setClipRect(spielFeld);

    if (increment_o1)
        switch(phase)
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
            if (lastY1>100) lastY1=lastY1-800; //placing the object on top again
            else phase=0;
            break;
        }

    painter_object1.end();

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
            break;
        }

    painter_object3.end();
	
//counter of the players "progress"
    painter_counter.begin(this);
    painter_counter.setPen(QColor(222,22,2));


    painter_counter.drawText(10,20, QString::number(counter,10)); //number enables drawText to use an int as a string

            if(count<30)count++;                      //in order to make a 'slow' and readable counter, it only increases everytime count has increased from 0 to 30
             else{counter++; count=0;};

    painter_counter.end();

//visualization of the players lifes	
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

//movement of the player character using the QKeyEvent
void zeichenFeld::keyPressEvent(QKeyEvent *event) 
{
    if(increment)
        switch (event->key()){
            case Qt::Key_Left:
            if (playerX>0){ //left border of zeichenFeld
                playerX=playerX-15;}
            break;
            case Qt::Key_Right:
            if (playerX+SQUARE_DIMENSION<WIDTH){ //right border of zeichenFeld
                playerX=playerX+15;}
            break;
        default:
            break;
        }
    update();
}

void zeichenFeld::save(QJsonObject &json) const //saving of all variables
{
    json["count"]=count;
    json["counter"]=counter;
    json["lifes"]=lifes;
    json["playerX"]=playerX;
    json["lastY1"]=lastY1;
    json["lastY2"]=lastY2;
    json["lastY3"]=lastY3;
}

void zeichenFeld::load(const QJsonObject &json) //loading the variables includeing a test of the data type (isDouble)
{

    if (json.contains("count") && json["count"].isDouble())
            count = json["count"].toInt();

    if (json.contains("counter") && json["counter"].isDouble())
            counter = json["counter"].toInt();

    if (json.contains("lifes") && json["lifes"].isDouble())
            lifes = json["lifes"].toInt();

    if (json.contains("playerX") && json["playerX"].isDouble())
            playerX = json["playerX"].toInt();

    if (json.contains("lastY1") && json["lastY1"].isDouble())
            lastY1 = json["lastY1"].toInt();

    if (json.contains("lastY2") && json["lastY2"].isDouble())
            lastY2 = json["lastY2"].toInt();

    if (json.contains("lastY3") && json["lastY3"].isDouble())
            lastY3 = json["lastY3"].toInt();
    update(); //allows to visualize the loaded coordinates during the pause
}



