#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
  this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
  glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData()
{
  // Configure VAO/VBO
  GLuint VBO;
  GLuint EBO;

  GLfloat quadVertices[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
  };

  GLfloat quadIndices[] = {
    0, 1, 2,
    2, 1, 3
  };

  glGenVertexArrays(1, &this->quadVAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  
  glGenBuffers(1, &this->instanceVBO);

  glBindVertexArray(this->quadVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, this->instanceVBO);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(RenderItem), (void*)0);
  glVertexAttribDivisor(1, 1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(RenderItem), (void*)(2 * sizeof(float)));
  glVertexAttribDivisor(2, 1);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(RenderItem), (void*)(4 * sizeof(float)));
  glVertexAttribDivisor(3, 1);
  glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(RenderItem), (void*)(6 * sizeof(float)));
  glVertexAttribDivisor(4, 1);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(RenderItem), (void*)(8 * sizeof(float)));
  glVertexAttribDivisor(5, 1);
  glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(RenderItem), (void*)(12 * sizeof(float)));
  glVertexAttribDivisor(6, 1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Sprite &sprite, vec2 position, GLfloat rotate, vec3 color)
{
  // Prepare transformations
  this->shader.Use();
  mat4 model;
  model = glm::translate(model, vec3(position, 0.0f));

  model = glm::translate(model, vec3(0.5f * sprite.Width, 0.5f * sprite.Height, 0.0f));
  model = glm::rotate(model, rotate, vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, vec3(-0.5f * sprite.Width, -0.5f * sprite.Height, 0.0f));

  model = glm::scale(model, vec3(sprite.Width, sprite.Height, 1.0f));

  this->shader.SetMatrix4("model", model);
  this->shader.SetVector3f("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, sprite.TextureId);

  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SpriteRenderer::SetShader(Shader &shader)
{
  this->shader = shader;
}

void SpriteRenderer::UseShader()
{
  this->shader.Use();
}

void SpriteRenderer::DrawInstancedSprites(RenderItemList const &items)
{
  glBindVertexArray(this->quadVAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, this->instanceVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(RenderItem) * items.size(), &items[0], GL_STREAM_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, items.size());
  glBindVertexArray(0);
}