#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
// nur notwendig, wenn Qt 5:
#include <QPushButton>
#include <QGridLayout>
//Ende Qt 5
#include "meinwidget.h"
#include "zeichenfeld.h"


meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *start = new QPushButton(tr("Start"));
    start->setFont(QFont("Times", 18, QFont::Bold));
    connect(start, SIGNAL(clicked()), qApp, SLOT(start()));

    QPushButton *pause = new QPushButton(tr("Pause"));
    pause->setFont(QFont("Times", 18, QFont::Bold));
    connect(pause, SIGNAL(clicked()), qApp, SLOT(pause()));

    QPushButton *save = new QPushButton(tr("Speichern"));
    save->setFont(QFont("Times", 18, QFont::Bold));
    connect(save, SIGNAL(clicked()), qApp, SLOT(save()));

    QPushButton *load = new QPushButton(tr("Laden"));
    load->setFont(QFont("Times", 18, QFont::Bold));
    connect(load, SIGNAL(clicked()), qApp, SLOT(load()));

    zeichenFeld *meinZeichenFeld = new zeichenFeld;
    meinZeichenFeld->setFixedSize(1000, 800);
            //widget->resize(165, widget->height());


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(start, 0, 0);
    gridLayout->addWidget(pause, 1, 0);
    gridLayout->addWidget(save, 2, 0);
    gridLayout->addWidget(load, 3, 0);
    gridLayout->addWidget(meinZeichenFeld, 0, 1, 4, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}



