#include "bird.h"

Bird::Bird(float x, float y, float radius, int birdtype, QTimer *timer, QPixmap pixmap,
           b2World *world, QGraphicsScene *scene):GameItem(world)
{
    //Set data
    canDie = false;
    type = birdtype;
    skillValid = true;
    hitPoint = 1;
    name = "bird";

    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    if (birdtype == BIG_BIRD){
        fixturedef.density = BIRD_DENSITY*10;
    }
    else {
        fixturedef.density = BIRD_DENSITY;
    }
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Bird::setTransform(b2Vec2 position, float angle)
{
    g_body->SetTransform(position, angle);
}

float Bird::getX()
{
    return g_body->GetPosition().x;
}

float Bird::getY()
{
    return g_body->GetPosition().y;
}

int Bird::getType()
{
    return type;
}

bool Bird::getSkillValid()
{
    return skillValid;
}

b2Vec2 Bird::getLinearVelocity()
{
    return g_body->GetLinearVelocity();
}

void Bird::useSkill()
{
    if (skillValid){
        switch (type) {
        case YELLOW_BIRD:
            setLinearVelocity(b2Vec2(this->g_body->GetLinearVelocity().x * 20,
                                          this->g_body->GetLinearVelocity().y * 20));
            break;
        case BLUE_BIRD:
            //write in mainwindow, cause the skill has to build new birds
            break;
        default:
            //do nothing
            break;
        }
        skillValid = false;
    }
}

void Bird::collide(float)
{
    return;
}
