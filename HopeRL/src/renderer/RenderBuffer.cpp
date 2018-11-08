#include "RenderBuffer.h"


RenderItem::RenderItem(Sprite &sprite, vec2 position, vec4 color, GLfloat rotation)
{
  Position = position;
  Size = vec2(sprite.Width, sprite.Height);
  TexPos = sprite.MinUV;
  TexSize = sprite.MaxUV;
  Color = color;
  Rotation = rotation;
}

void RenderBuffer::BeginRender()
{
  Items.clear();
}

void RenderBuffer::PushSprite(Sprite &sprite, vec2 position, vec4 color, GLfloat rotation)
{
  if (Items.find(sprite.TextureId) == Items.end())
  {
    Items[sprite.TextureId] = RenderItemList();
    Items[sprite.TextureId].reserve(512);
  }
  Items[sprite.TextureId].emplace_back(sprite, position, color, rotation);
}

void RenderBuffer::EndRender(SpriteRenderer &renderer)
{
  for (auto const &textureGroup : Items)
  {
    glBindTexture(GL_TEXTURE_2D, textureGroup.first);
    renderer.DrawInstancedSprites(textureGroup.second);
  }
}