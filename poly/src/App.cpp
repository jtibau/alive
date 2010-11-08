#include "App.h"

#include <main/qapplication3d.h>
#include "ui/UserInterface.h"

#include <iostream>

namespace alive{
  namespace poly{
    App::App(alive::SceneRenderer* scene, alive::InteractionMethod* interactionMethod)
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

    void App::contextPreDraw(){
      alive::App::contextPreDraw();

      //Qt3D::qApp3d->updateTextures();
    }

    void App::draw(){
      glClear(GL_DEPTH_BUFFER_BIT);

      // Users have reported problems with OpenGL reporting stack underflow
      // problems when the texture attribute bit is pushed here, so we push all
      // attributes *except* GL_TEXTURE_BIT.
      glPushAttrib(GL_ALL_ATTRIB_BITS & ~GL_TEXTURE_BIT);
      glPushAttrib(GL_TRANSFORM_BIT);
      glPushAttrib(GL_VIEWPORT_BIT);

      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();

      glMatrixMode(GL_PROJECTION);
      glPushMatrix();

      if(mSceneRenderer) mSceneRenderer->draw();

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();

      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();

      // Drawing the Wand
      glEnable(GL_DEPTH_TEST);
      glColor3f(0.663f,0.83f,0.51f);
      glLineWidth(2.);

      glBegin(GL_LINES);
      {
	      gmtl::Vec3f start = mInput->getWandPosition();
	      gmtl::Vec3f dir = mInput->getWandDirection();

	      glVertex3f(start[0],start[1],start[2]);
        glVertex3f(start[0]+dir[0],start[1]+dir[1],start[2]+dir[2]);
      }
      glEnd();
      // Wand Drawn
      
      //Qt3D::qApp3d->drawWindows();
      
      glPopAttrib();
      glPopAttrib();
      glPopAttrib();
    }
    
    void App::exit(){
      qApp->exit();
    }
  }
}


