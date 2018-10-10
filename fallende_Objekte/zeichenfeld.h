#include <vector>
using namespace std;
#include <QWidget>
#include <QTimer>


class zeichenFeld : public QWidget
{
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    enum drawType { square, circle };

    void start(void) { timer->start(40); increment=1; increment2=1; };
    void stop(void) { timer->stop(); increment=0; increment2=0; };

private:
    QTimer *timer;
    int lastX;
    int lastY;
    int lastX2;
    int lastY2;
    int increment;
    int phase;
    int increment2;
    int phase2;

protected:
    void paintEvent(QPaintEvent *event);
};

