#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
using namespace glm;

#include "shader.h"
#include "sprite.h"
#include "RenderBuffer.h"

class SpriteRenderer
{
public:
  SpriteRenderer();
  ~SpriteRenderer();

  void SetShader(Shader &shader);
  void UseShader();
  void DrawSprite(Sprite &sprite, vec2 position, GLfloat rotate = 0.0f, vec3 color = vec3(1.0f));
  void DrawInstancedSprites(RenderItemList const &items);
private:
  Shader shader;
  GLuint quadVAO;
  GLuint instanceVBO;

  void initRenderData();
};