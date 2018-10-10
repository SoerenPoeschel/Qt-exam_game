#include <vector>
using namespace std;
#include <QWidget>

class zeichenFeld : public QWidget
{
   // Q_OBJECT
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

private:
    //vector<QRect *> rects; unnöötig, weil dumm
    vector<QPoint *> points;

    int playerX;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
