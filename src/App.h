#pragma once

class App
{
private:
  class Renderer* m_Renderer;
  class InputSystem* m_InputSystem;
  bool m_IsRunning;
  float m_TicksCount;
public:
  App();
  ~App();
  bool Initialize();
  void Run();
  void ShutDown();
private:
  void ProcessInput();
  void UpdateApp();
  void GenerateOutput();
};
