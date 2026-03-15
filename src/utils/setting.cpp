#include "setting.h"

Setting::Setting() : zNear(0.1f), zFar(100.0f), viewAngle(glm::radians(45.0f)), SCR_WIDTH(800), SCR_HEIGHT(600)
{
    // initial setting
}

void Setting::setRenderdistance(float newzNear, float newzFar)
{
    zNear = newzNear;
    zFar = newzFar;
}

void Setting::setViewAngle(float newviewAngle)
{
    viewAngle = newviewAngle;
}

void Setting::setWindowsize(int newSCR_WIDTH, int newSCR_HEIGHT)
{
    SCR_WIDTH = newSCR_WIDTH;
    SCR_HEIGHT = newSCR_HEIGHT;
}

int Setting::getAspect()
{
    return SCR_WIDTH / SCR_HEIGHT;
}

float Setting::getRadian()
{
    return glm::radians(viewAngle);
}