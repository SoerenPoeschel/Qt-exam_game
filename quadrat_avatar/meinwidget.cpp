#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
// nur notwendig, wenn Qt 5:
#include <QPushButton>
#include <QGridLayout>
//Ende Qt 5
#include "meinwidget.h"
#include <iostream>


meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *startButton = new QPushButton(tr("Start"));
    startButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(startButton, SIGNAL(clicked()), this, SLOT(start())); // war nicht connected weil statt this noch qApp da stand

    QPushButton *pauseButton = new QPushButton(tr("Pause"));
    pauseButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(stop()));

    QPushButton *saveButton = new QPushButton(tr("Speichern"));
    saveButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));

    QPushButton *loadButton = new QPushButton(tr("Laden"));
    loadButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));

    QPushButton *quit = new QPushButton(tr("Ende"));
    quit->setFont(QFont("Times", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));


    meinZeichenFeld = new zeichenFeld;
    meinZeichenFeld->setFixedSize(1000, 800);
            //widget->resize(165, widget->height());


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(startButton, 0, 0);
    gridLayout->addWidget(pauseButton, 1, 0);
    gridLayout->addWidget(saveButton, 2, 0);
    gridLayout->addWidget(loadButton, 3, 0);
    gridLayout->addWidget(quit, 4, 0);
    gridLayout->addWidget(meinZeichenFeld, 0, 1, 5, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}

void meinWidget::start(void)
{
    meinZeichenFeld->start();
    cout << "start";
}

void meinWidget::stop(void)
{
    meinZeichenFeld->stop();
}

void meinWidget::keyPressEvent(QKeyEvent* event)
{
    cout << event->text().toStdString();


    std::chrono::time_point<std::chrono::system_clock> this_press = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = time_last_pressed-this_press;

    std::cout << " ...Time spent between presses " << diff.count() << " s\n";

    time_last_pressed = this_press;

    meinZeichenFeld->keyPressEvent(event);
}
