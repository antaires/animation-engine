#include "App.h"

int main(int argc, char* args[]){

  App app;

  if (app.Initialize())
  {
    app.Run();
  }

  app.ShutDown();

  return 0;
}
