#ifndef MODEL_H
#define MODEL_H

#include<json/json.h>
#include"Mesh.h"

class Model
{
    public :
    Model(const char* file);

    void Draw();
};

#endif