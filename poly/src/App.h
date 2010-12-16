#pragma once

#include <alice/App.h>

#include <QObject>
#include <main/modelview.h>


namespace alice {
  namespace poly {
    class App : public QObject, public alice::App, public Qt3D::Modelview  {
    Q_OBJECT
    public:
      App(alice::SceneRenderer* scene = NULL,
        alice::InteractionMethod* interactionMethod = NULL);

      void exit();

      void preFrame();
      void bufferPreDraw();
      void contextPreDraw();
      void draw();

      // Override Qt3D::Modelview
      void getModelview(double*);
    };
  }
}
