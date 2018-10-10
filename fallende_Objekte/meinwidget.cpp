// Qt5 add:
#include <QPushButton>
#include <QGridLayout>

#include <QtGui>
#include "meinWidget.h"

meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton(tr("Ende"));
    quit->setFont(QFont("Times", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QPushButton *startButton = new QPushButton(tr("Start"));
    startButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));

    QPushButton *stopButton = new QPushButton(tr("Stop"));
    stopButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));

    meinZeichenFeld = new zeichenFeld;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(quit, 0, 0);
    gridLayout->addWidget(startButton, 1, 0);
    gridLayout->addWidget(stopButton, 2, 0);
    gridLayout->addWidget(meinZeichenFeld, 0, 1, 3, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}

void meinWidget::start(void)
{
    meinZeichenFeld->start();
}

void meinWidget::stop(void)
{
    meinZeichenFeld->stop();
}
