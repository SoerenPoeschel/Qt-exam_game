#include <vector>
using namespace std;
#include <QWidget>

class zeichenFeld : public QWidget
{
   // Q_OBJECT
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    void start(void) { timer->start(40); increment=1; };
    void stop(void) { timer->stop(); increment=0; };


private:
    //vector<QRect *> rects; unnöötig, weil dumm
    QTimer *timer;

    int playerX;
    int increment;
    int phase;

    int leftKey;
    int rightKey;
    int noKey;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
