#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader &shader)
{
  this->shader = shader;
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
  GLfloat vertices[] = {
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

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

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->quadVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
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

void SpriteRenderer::UseShader()
{
  this->shader.Use();
}

void SpriteRenderer::DrawInstancedSprites(RenderItemList &items)
{

}