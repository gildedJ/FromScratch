#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
using namespace glm;

#include <vector>
#include <map>
using namespace std;

#include "sprite.h"
#include "SpriteRenderer.h"

struct RenderItem
{
  vec2 Position;
  vec2 Size;
  vec2 TexPos;
  vec2 TexSize;
  vec4 Color;
  GLfloat Rotation;

  RenderItem(Sprite &sprite, vec2 position = vec2(0.0f), vec4 color = vec4(1.0f), GLfloat rotation = 1.0f);
};

typedef std::vector<RenderItem> RenderItemList;
typedef std::map<GLuint, RenderItemList> RenderItemListTextureMap;

struct RenderBuffer
{
  static RenderItemListTextureMap Items;

  static void BeginRender();
  static void PushSprite(Sprite &sprite, vec2 position = vec2(0.0f), vec4 color = vec4(1.0f), GLfloat rotation = 1.0f);
  static void EndRender(SpriteRenderer &renderer);
};