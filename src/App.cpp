#include "App.h"
#include "Renderer.h"
#include "InputSystem.h"

const float SCREEN_WIDTH = 1280;
const float SCREEN_HEIGHT = 600;

App::App()
  :m_Renderer(nullptr)
  , m_InputSystem(nullptr)
  , m_IsRunning(true)
  , m_TicksCount(0.0f)
{}

App::~App()
{}

bool App::Initialize()
{
  m_Renderer = new Renderer(this);
  if (!m_Renderer->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT)){ return false; }

  m_InputSystem = new InputSystem();
  m_InputSystem->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

  return true;
}

void App::Run()
{
  while(m_IsRunning)
  {
    ProcessInput();
    UpdateApp();
    GenerateOutput();
  }
}

void App::ProcessInput()
{
  m_InputSystem->PrepareForUpdate();

  SDL_Event event;

  // loop over events in event queue
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      // handle all event types
      case SDL_QUIT:
        m_IsRunning = false;
        break;
      case SDL_MOUSEWHEEL:
        m_InputSystem->ProcessEvent(event);
        break;
    }
  }

  m_InputSystem->Update();
  const InputState& keyboardState = m_InputSystem->GetState();

  // todo process any keys here ...
  // if escape pressed, exit Game RunLoop
  if (keyboardState.keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == E_Released)
  {
    m_IsRunning = false;
  }

  // handle input & pass to actor here once actor(s) built
  //for(auto actor: m_Actors)
  //{
  //  actor->ProcessInput(keyboardState);
  //}
}

void App::UpdateApp()
{
  // frame limiting : wait until 16 ms elapsed
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 16));

  // deltaTime is difference in ticks from last frame
  float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;

  // clamp max delta time value (to avoid jumping ahead during debug)
  if (deltaTime > 0.05f)
  {
    deltaTime = 0.05f;
  }
  m_TicksCount = SDL_GetTicks();

  // update objects in game world as function of delta time
  //m_UpdatingActors = true;
  //for(auto actor: m_Actors)
  //{
  //  actor->Update(deltaTime);
  //}
  //m_UpdatingActors = false;
}

void App::GenerateOutput()
{
  m_Renderer->Draw();
}

void App::ShutDown()
{}
