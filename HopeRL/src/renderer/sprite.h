#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "texture.h"

struct Tileset
{
  Tileset(Texture &texture, GLuint rows, GLuint columns) : Texture(texture), Rows(rows), Columns(columns) {}

  Texture &Texture;
  GLuint Rows, Columns;

  Sprite MakeSprite(GLuint row, GLuint column)
  {
    GLfloat TileWidth = (GLfloat)Texture.Width / (GLfloat)Columns;
    GLfloat TileHeight = (GLfloat)Texture.Height / (GLfloat)Rows;
    vec2 minUV = vec2(TileWidth * column, TileHeight * row);
    vec2 maxUV = vec2(TileWidth, TileHeight) + minUV;

    Sprite newSprite(Texture.ID, minUV, maxUV, TileWidth, TileHeight);
    return newSprite;
  }
};

struct Sprite
{
  Sprite(GLuint textureId, vec2 minUV, vec2 maxUV, GLfloat width, GLfloat height)
    : TextureId(textureId), MinUV(minUV), MaxUV(maxUV), Width(width), Height(height) {}

  GLuint TextureId;
  vec2 MinUV, MaxUV;
  GLfloat Width, Height;
};