#pragma once

#include <SDL2/SDL.h>

class Renderer
{
public:
  Renderer(class App* app);
  ~Renderer();

  bool Initialize(float width, float height);
  void Draw();
  void UnloadData();
  void ShutDown();

private:
  class App* m_App;
  SDL_Window* m_Window;
  // OpenGL context
  SDL_GLContext m_Context;
  float m_ScreenWidth;
  float m_ScreenHeight;
};
