#pragma once

#include <Windows.h>
#include <GL/glew.h>

class Game {
public:
  Game() {}

  void Init();
  void Update(GLfloat dt);
  void Render(HDC context);
  void CleanUp();
};