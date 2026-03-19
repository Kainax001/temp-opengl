#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "inputmanager.h"

void rotateObject(GLfloat* vertices, InputManager* ourInputmanager);
void moveObject(GLfloat* vertices, InputManager* ourInputmanager);

#endif 