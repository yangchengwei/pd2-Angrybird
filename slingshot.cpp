#include "slingshot.h"

Slingshot::Slingshot(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set data
    hitPoint = 1;
    name = "slingshot";

    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_size = QSize(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    paint();
}

void Slingshot::collide(float)
{
    return;
}
