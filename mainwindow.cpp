#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    restart();
}

void MainWindow::restart()
{
    /*// Clean
    delete scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;

    Bird *bird[5];
    Bird *currentBird;      //the pointer to point the attacking bird
    Slingshot *slingshot;*/

    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    world->SetContactListener(this);
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());


    //============= set Item ===============
    // Create land
    itemList.push_back(new Land(16,1.5, xPixToMet(960), xPixToMet(90),QPixmap(":/image/GROUND.png").scaled(960,90),world,scene));
    itemList.push_back(new Land(4, 16, xPixToMet(240), xPixToMet(10),QPixmap(":/image/GROUND.png").scaled(240,10),world,scene));
    itemList.push_back(new Land(32, 9, xPixToMet(90), xPixToMet(540),QPixmap(":/image/GROUND.png").scaled(90,540),world,scene));


    // Create slingshot
    slingshot = new Slingshot(4.0, 9.5, -1, -1, QPixmap(":/image/Slingshot.png").scaled(width()/20.0,height()/3.0),world,scene);
    itemList.push_back(slingshot);

    // Create block
    Block *block[8];
    block[0] = new Block(0, 0, xPixToMet(150), xPixToMet(50), &timer, QPixmap(":/image/Rock_1.png").scaled(150,50),world,scene);
    itemList.push_back(block[0]);
    block[1] = new Block(0, 0, xPixToMet(150), xPixToMet(50), &timer, QPixmap(":/image/Rock_1.png").scaled(150,50),world,scene);
    itemList.push_back(block[1]);
    block[2] = new Block(0, 0, xPixToMet(150), xPixToMet(50), &timer, QPixmap(":/image/Rock_1.png").scaled(150,50),world,scene);
    itemList.push_back(block[2]);
    block[3] = new Block(0, 0, xPixToMet(150), xPixToMet(50), &timer, QPixmap(":/image/Rock_1.png").scaled(150,50),world,scene);
    itemList.push_back(block[3]);
    block[4] = new Block(0, 0, xPixToMet(150), xPixToMet(50), &timer, QPixmap(":/image/Rock_1.png").scaled(150,50),world,scene);
    itemList.push_back(block[4]);
    block[5] = new Block(0, 0, xPixToMet(150), xPixToMet(50), &timer, QPixmap(":/image/Rock_1.png").scaled(150,50),world,scene);
    itemList.push_back(block[5]);
    block[6] = new Block(0, 0, xPixToMet(150), xPixToMet(50), &timer, QPixmap(":/image/Rock_1.png").scaled(150,50),world,scene);
    itemList.push_back(block[6]);
    block[7] = new Block(0, 0, xPixToMet(150), xPixToMet(50), &timer, QPixmap(":/image/Rock_1.png").scaled(150,50),world,scene);
    itemList.push_back(block[7]);

    block[0]->SetTransform(b2Vec2(25,16),0);
    block[1]->SetTransform(b2Vec2(22.5,13),3.14/2);
    block[2]->SetTransform(b2Vec2(27.5,13),3.14/2);
    block[3]->SetTransform(b2Vec2(22.5,10),0);
    block[4]->SetTransform(b2Vec2(27.5,10),0);
    block[5]->SetTransform(b2Vec2(20,6),3.14/2);
    block[6]->SetTransform(b2Vec2(25,6),3.14/2);
    block[7]->SetTransform(b2Vec2(30,6),3.14/2);

    // Create pig
    Pig *pig[3];
    pig[0] = new Pig(0, 0, xPixToMet(80)/2, &timer, QPixmap(":/image/Pig_1.png").scaled(80,80),world,scene);
    itemList.push_back(pig[0]);
    pig[1] = new Pig(0, 0, xPixToMet(80)/2, &timer, QPixmap(":/image/Pig_1.png").scaled(80,80),world,scene);
    itemList.push_back(pig[1]);
    pig[2] = new Pig(0, 0, xPixToMet(80)/2, &timer, QPixmap(":/image/Pig_1.png").scaled(80,80),world,scene);
    itemList.push_back(pig[2]);

    pig[0]->setTransform(b2Vec2(25,12),0);
    pig[1]->setTransform(b2Vec2(22.5,6),0);
    pig[2]->setTransform(b2Vec2(27.5,6),0);

    // Create bird
    bird[0] = new Bird(0, 0, xPixToMet(birdDiameter)/2, YELLOW_BIRD, &timer, QPixmap(":/image/Yellow_Bird_1.png").scaled(birdDiameter,birdDiameter),world,scene);
    itemList.push_back(bird[0]);
    bird[1] = new Bird(0, 0, xPixToMet(birdDiameter)/2, RED_BIRD, &timer, QPixmap(":/image/Red_Bird_1.png").scaled(birdDiameter,birdDiameter),world,scene);
    itemList.push_back(bird[1]);
    bird[2] = new Bird(0, 0, xPixToMet(birdDiameter)/2, BLUE_BIRD, &timer, QPixmap(":/image/Blue_Bird_1.png").scaled(birdDiameter,birdDiameter),world,scene);
    itemList.push_back(bird[2]);
    bird[3] = new Bird(0, 0, xPixToMet(birdDiameter)/2, BIG_BIRD,&timer, QPixmap(":/image/Big_Bird_1.png").scaled(birdDiameter,birdDiameter),world,scene);
    itemList.push_back(bird[3]);
    bird[4] = new Bird(0, 0, xPixToMet(birdDiameter)/2, YELLOW_BIRD, &timer, QPixmap(":/image/Yellow_Bird_1.png").scaled(birdDiameter,birdDiameter),world,scene);
    itemList.push_back(bird[4]);

    bird[0]->setTransform(b2Vec2(6,17),0);
    bird[1]->setTransform(b2Vec2(5,17),0);
    bird[2]->setTransform(b2Vec2(4,17),0);
    bird[3]->setTransform(b2Vec2(3,17),0);
    bird[4]->setTransform(b2Vec2(2,17),0);
    //=======================================

    //============== set Data ===============
    mousePress = false;
    birdAttacking = false;
    destroying = false;
    theEnd = false;
    currentBird = bird[0];
    birdCount = 0;
    score = 0;
    numOfPig = 3;
    //=======================================

    // Setting the Velocity
    // Timer
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    disconnect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress && !mousePress)
    {
        //std::cout << "Press !" << std::endl ;

        //birds use skill
        if (birdAttacking){
            if (currentBird->getSkillValid()){
                //blue bird's skill
                if (currentBird->getType() == BLUE_BIRD){
                    Bird *tempBird = new Bird(currentBird->getX(), currentBird->getY(), xPixToMet(birdDiameter)/2, BLUE_BIRD,
                                      &timer, QPixmap(":/image/Blue_Bird_1.png").scaled(birdDiameter,birdDiameter),world,scene);
                    tempBird->setLinearVelocity(currentBird->getLinearVelocity()+b2Vec2(0,5));
                    itemList.push_back(tempBird);
                    tempBird->canDie = true;

                    tempBird = new Bird(currentBird->getX(), currentBird->getY(), xPixToMet(birdDiameter)/2, BLUE_BIRD,
                                 &timer, QPixmap(":/image/Blue_Bird_1.png").scaled(birdDiameter,birdDiameter),world,scene);
                    tempBird->setLinearVelocity(currentBird->getLinearVelocity()+b2Vec2(0,-5));
                    itemList.push_back(tempBird);
                    tempBird->canDie = true;
                }
            }
            currentBird->useSkill();
        }

        mousePress = true;
    }

    if(event->type() == QEvent::MouseMove)
    {
        //std::cout << "Move !" << std::endl ;

        QMouseEvent *eventM = (QMouseEvent*)event;
        mouseX = xPixToMet(eventM->x());
        mouseY = yPixToMet(eventM->y());
    }

    if(event->type() == QEvent::MouseButtonRelease && mousePress)
    {
        //std::cout << "Release !" << std::endl ;

        mousePress = false;
        if (!birdAttacking){
            currentBird->setLinearVelocity(b2Vec2(-10*(currentBird->getX()-readyX), -10*(currentBird->getY()-readyY)));
            currentBird->canDie = true;
        }
        birdAttacking = true;

    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();

    // The end
    if ((numOfPig == 0 || birdCount == 5) && !theEnd){
        theEnd = true;
        birdAttacking = true;
        score += (5-birdCount)*10000;

        //std::cout<<score<<std::endl;
        QString result;
        if (numOfPig <= 0){
            result = QString("YOU WIN~!\n");
        }
        else {
            result = QString("YOU LOSE~\n");
        }

        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "The End", result.append("Your score is ").append(QString::number(score)).append(QString(".\n"))
                                                                                .append("Do you want to restart ?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (rb == QMessageBox::Yes)
        {
            restart();
        }
        else if (rb == QMessageBox::No)
        {
            this->close();
        }
    }

    // Prepare to shot
    mouseToReady = distance(mouseX, mouseY, readyX, readyY);
    if (mousePress && !birdAttacking){
        if (mouseToReady < 3){
            currentBird->setTransform(b2Vec2(mouseX, mouseY), 0);
            currentBird->setLinearVelocity(b2Vec2(0,0));
        }
        else {
            currentBird->setTransform(b2Vec2((mouseX-readyX)*3/mouseToReady+readyX,
                                         (mouseY-readyY)*3/mouseToReady+readyY), 0.0);
            currentBird->setLinearVelocity(b2Vec2(0,0));
        }
    }
    if (birdAttacking && (velocity(currentBird->getLinearVelocity()) < 1||
                          currentBird->getX() < 0 || currentBird->getX() > 32))     //out of screen
    {
        ++birdCount;
        if (birdCount == 5){
            return;
        }
        currentBird = bird[birdCount];
        birdAttacking = false;
    }


    // Destroy body
    QList<GameItem *>::iterator it;
    GameItem* dying;
    int i, j;

    for (i=0 ; i<itemList.length() ; i++){
        dying = itemList.at(i);

        if (dying->getName() == QString("bird") &&
            dying->getBody()->GetLinearVelocity() == b2Vec2(0,0))
        {
            for (j=0 ; j<birdCount ; j++){
                if (dying->canDie){
                    // The bird already shoted
                    dying->setHitPoint(0);
                }
            }
        }

        if (dying->getHitPoint() <= 0){
            destroying = true;
            if (dying->getName() == QString("pig")){
                numOfPig--;
                score += 8000;
            }
            else if (dying->getName() == QString("block")){
                score += 3000;
            }
            delete dying;
            j = itemList.indexOf(dying);
            it = itemList.begin()+j;
            itemList.erase(it);
            destroying = false;
            return;
        }
    }
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

float MainWindow::xPixToMet(int xP)
{
    // Change pixel to meter
    return xP/30.0;
}

float MainWindow::yPixToMet(int yP)
{
    // Change pixel, y-direction only, to meter
    return 18-yP/30.0;
}

float MainWindow::distance(float x1, float y1, float x2, float y2)
{
    return (float)sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

float MainWindow::velocity(b2Vec2 vec)
{
    return (float)sqrt(vec.x*vec.x + vec.y*vec.y);
}

void MainWindow::BeginContact(b2Contact *contact)
{
    //std::cout<<"collide"<<std::endl;

    int i;
    int v;

    b2Body *bodyA;
    b2Body *bodyB;

    bodyA = contact->GetFixtureA()->GetBody();
    bodyB = contact->GetFixtureB()->GetBody();

    //block collide
    if (!destroying){
        for (i=0 ; i<itemList.length() ; i++){
            if (bodyA == itemList.at(i)->getBody()){
                v = velocity(bodyB->GetLinearVelocity());
                itemList.at(i)->collide(v);
                score += v;
            }
            else if (bodyB == itemList.at(i)->getBody()){
                v = velocity(bodyA->GetLinearVelocity());
                itemList.at(i)->collide(v);
                score += v;
            }
        }
    }
}

void MainWindow::EndContact(b2Contact *)
{

    return;
}
