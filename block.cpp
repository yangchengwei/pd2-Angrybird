#include "block.h"
#include <iostream>
Block::Block(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap,
           b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set data
    hitPoint = 100.0;
    name = "block";

    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = BLOCK_DENSITY;
    fixturedef.friction = BLOCK_FRICTION;
    fixturedef.restitution = BLOCK_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Block::SetTransform(b2Vec2 position, float angle)
{
    g_body->SetTransform(position, angle);
}

void Block::collide(float velocity)
{
    hitPoint -= velocity;
    if (hitPoint <= 50){
        g_pixmap.setPixmap(QPixmap(":/image/Rock_2.png").scaled(150,50));
    }
}
