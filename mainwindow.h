#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include "pig.h"
#include "block.h"
#include "slingshot.h"

#define readyX 5.1
#define readyY 8.2
#define birdDiameter 45

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public b2ContactListener
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void restart();

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;

    Bird *bird[5];
    Bird *currentBird;      //the pointer to point the attacking bird
    Slingshot *slingshot;

    bool mousePress;
    bool birdAttacking;
    bool destroying;
    bool theEnd;
    float mouseX;
    float mouseY;
    float mouseToReady;
    int birdCount;
    int score;
    int numOfPig;

    float xPixToMet(int);
    float yPixToMet(int);
    float distance(float,float,float,float);
    float velocity(b2Vec2);

    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);

};

#endif // MAINWINDOW_H
