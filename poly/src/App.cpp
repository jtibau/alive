#include "App.h"

#include <main/qapplication3d.h>

#include <iostream>

namespace alive{
  namespace poly{
    App::App(alive::Scene* scene, alive::InteractionMethod* interactionMethod)
        : alive::App(scene, interactionMethod){
        
        Qt3D::qApp3d->setWindowPosition(-1.5,1.2,1);
        Qt3D::qApp3d->setWindowOrientation(1.0,0.0,0.0);
        Qt3D::qApp3d->setScaleFactor(1.0/1000.0);
        Qt3D::qApp3d->hideInteractionRay(true);
        Qt3D::qApp3d->setCamera(this);
        Qt3D::qApp3d->setAutoUpdate(false);
        Qt3D::qApp3d->setEnabled(true);
        Qt3D::qApp3d->setFocusPolicy(true);
        Qt3D::qApp3d->setInteractionMode(2);
    }
    App::~App(){}
    
    void App::exit(){
      qApp->exit();
    }
  }
}


