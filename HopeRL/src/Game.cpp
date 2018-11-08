#include "Game.h"

#include "resource_manager.h"
#include "renderer\texture.h"
#include "renderer\sprite.h"
#include "renderer\RenderBuffer.h"

void Game::Init() {
  Texture mainTexture = ResourceManager::LoadTexture("assets/textures/dcss_tileset.png", GL_TRUE, "DCSS Tileset"); //64 x 48 tiles
  Tileset dcssTileset(mainTexture, 48, 64);
  Sprite playerSprite(dcssTileset, 3, 10);
  Sprite floorTile(dcssTileset, 10, 8);

  this->Sprites["player"] = playerSprite;
  this->Sprites["floorTile"] = floorTile;

  Shader spriteShader = ResourceManager::LoadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", nullptr, "Sprite");
  this->renderer.SetShader(spriteShader);
}

void Game::Update(GLfloat dt)
{

}

void Game::Render(HDC context)
{
  glViewport(0, 0, 800, 600);
  glClearColor(0.2f, 0.5f, 0.4f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  RenderBuffer::BeginRender();

  RenderBuffer::PushSprite(this->Sprites["player"], vec2(5,5));
  for (int x = 0; x < 10; x++)
    for (int y = 0; y < 10; y++)
      RenderBuffer::PushSprite(this->Sprites["floorTile"], vec2(x, y));

  RenderBuffer::EndRender(this->renderer);

  SwapBuffers(context);
}

void Game::CleanUp()
{

}