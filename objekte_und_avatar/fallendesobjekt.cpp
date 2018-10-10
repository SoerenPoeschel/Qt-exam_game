#include <QPainter>
#include "fallendesobjekt.h"

fallendesObjekt::fallendesObjekt(int speed, int x, QWidget* zeichenfeld, QRect spielFeld)
{
    this->speed = speed;
    this->x = x;
    this->zeichenfeld = zeichenfeld;
    this->spielFeld = spielFeld;
}

void fallendesObjekt::update()
{
    QPainter painter_object1;
    //Hab den painter für das erste Object gebaut
        painter_object1.begin(zeichenfeld);

        int y1=lastY1-50;

        painter_object1.drawEllipse(x, y1,50,50);
        painter_object1.setClipRect(spielFeld);

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
                */
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

        painter_object1.end();


}
