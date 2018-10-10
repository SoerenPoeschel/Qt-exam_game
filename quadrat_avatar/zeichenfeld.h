#ifndef ZEICHENFELD_H
#define ZEICHENFELD_H

#include <vector>
using namespace std;
#include <QWidget>
#include <QTimer>

class zeichenFeld : public QWidget //mann ey, warum bekomme ich da previously denfined/redifinition errors?
{
   Q_OBJECT
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    void start(void) { timer->start(40); increment=1; increment_o1=1; }
    void stop(void) { timer->stop(); increment=0; increment_o1=0; }
    void keyPressEvent(QKeyEvent *event);


private:
    QTimer *timer;

    int playerX;
    int lastY1;
    int lastY2;
    int lastY3;
    int increment;
    int increment_o1;
    int phase;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif
