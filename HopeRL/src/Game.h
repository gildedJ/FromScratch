#pragma once

#include <Windows.h>
#include <GL/glew.h>

#include <map>
#include <string>

#include "renderer\SpriteRenderer.h"

class Game {
public:
  Game() {}

  void Init();
  void Update(GLfloat dt);
  void Render(HDC context);
  void CleanUp();

private:
  SpriteRenderer renderer;
  std::map<std::string, Sprite> Sprites;
};