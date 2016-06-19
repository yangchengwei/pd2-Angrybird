#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f
#define RED_BIRD 0
#define YELLOW_BIRD 1
#define BLUE_BIRD 2
#define BIG_BIRD 3

class Bird : public GameItem
{
private:
    int type;
    bool skillValid;

public:
    Bird(float x, float y, float radius, int birdtype, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    void setLinearVelocity(b2Vec2 velocity);
    void setTransform(b2Vec2 position, float angle);

    float getX();
    float getY();
    int getType();
    bool getSkillValid();

    b2Vec2 getLinearVelocity();

    void useSkill();
    void collide(float velocity);

};

#endif // BIRD_H
