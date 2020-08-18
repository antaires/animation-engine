#include "Renderer.h"
#include <GL/glew.h>

Renderer::Renderer(class App* app)
  :m_App(app)
{}

Renderer::~Renderer()
{}

bool Renderer::Initialize(float width, float height)
{
  m_ScreenWidth = width;
  m_ScreenHeight = height;

  /*
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Unable to Initialize SDL: %s", SDL_GetError());
    return false;
  }*/

  // set up openGL attributes, returns 0 if succes
  // use the core openGL profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  // specifiy version 3.3
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  // request color buffer with 8-bits per RGBA channel
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  // set up depth buffer (ie Z-buffer)
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  // enable double buffering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  // force OpenGL to sue hardware acceleration
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  m_Window = SDL_CreateWindow(
    ""      // window title
    , 100   // top left  x-coord
    , 100   // top left  y-coord
    , static_cast<int>(m_ScreenWidth)
    , static_cast<int>(m_ScreenHeight)
    , SDL_WINDOW_OPENGL     // use openGL
  );
  if (!m_Window)
  {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  // create open GL context and saves it to member variable
  m_Context = SDL_GL_CreateContext(m_Window);

  // required for mac! without this, a rectangle is drawn as a rhombus
  int screenWidth, screenHeight;
  SDL_GL_GetDrawableSize(m_Window, &screenWidth, &screenHeight );
  glViewport(0, 0, screenWidth, screenHeight); // adjust to high density screen
  m_ScreenWidth = (float) screenWidth;
  m_ScreenHeight = (float) screenHeight;

  // init GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    SDL_Log("Failed to initialize GLEW");
    return false;
  }
  glGetError(); // clears benign error code

  // load shaders / sprites here

  return true;
}

void Renderer::Draw()
{
  // Set the clear color to light grey
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw mesh components
  // Enable depth buffering/disable alpha blend
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  // TODO draw shaders / meshes here
  // Draw all sprite components

  // Disable depth buffering
  glDisable(GL_DEPTH_TEST);
  // Enable alpha blending on the color buffer
  glEnable(GL_BLEND);
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

  // Swap the buffers
  SDL_GL_SwapWindow(m_Window);
}

void Renderer::UnloadData()
{
  // destroy textures / meshes here
}

void Renderer::ShutDown()
{
  SDL_GL_DeleteContext(m_Context);
  SDL_DestroyWindow(m_Window);
}
