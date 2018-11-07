#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

#include "texture.h"
#include "sprite.h"

struct Tileset
{
  Tileset(Texture &texture, GLuint rows, GLuint columns) : Texture(texture), Rows(rows), Columns(columns) {}

  Texture &Texture;
  GLuint Rows, Columns;
};

struct Sprite
{
  Sprite(Tileset &tileset, GLuint rows, GLuint columns)
  {
    Width = (GLfloat)tileset.Texture.Width / (GLfloat)columns;
    Height = (GLfloat)tileset.Texture.Height / (GLfloat)rows;
    MinUV = vec2(Width * columns, Height * rows);
    MaxUV = vec2(Width, Height) + MinUV;
    TextureId = tileset.Texture.ID;
  }

  Sprite(GLuint textureId, vec2 minUV, vec2 maxUV, GLfloat width, GLfloat height)
    : TextureId(textureId), MinUV(minUV), MaxUV(maxUV), Width(width), Height(height) {}

  GLuint TextureId;
  vec2 MinUV, MaxUV;
  GLfloat Width, Height;
};