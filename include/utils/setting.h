#ifndef SETTING_H
#define SETTING_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Setting 
{
    public :
        Setting();
        void setRenderdistance(float newzNear, float newzFar);
        void setViewAngle(float newviewAngle);
        void setWindowsize(int newSCR_WIDTH, int newSCR_HEIGHT);
        
        void loadConfig();
        void setConfig();

        float getAspect();
        float getRadian();
        float getZNear();
        float getZFar();
        int getWindowWidth();
        int getWindowHeight();
        int canResize();
    
    private :
        float zNear;
        float zFar;
        float viewAngle;
        int SCR_WIDTH;
        int SCR_HEIGHT;
        int reSizable;
};

#endif