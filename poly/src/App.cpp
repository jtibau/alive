#include "App.h"

#include <main/qapplication3d.h>
#include <main/trackerEvent.h>

#include "ui/UserInterface.h"

#include <gmtl/VecOps.h>

#include <iostream>

namespace alice{
    namespace poly{
        App::App(alice::SceneRenderer* scene, alice::InteractionMethod* interactionMethod)
            : alice::App(scene, interactionMethod){

            Qt3D::qApp3d->setWindowPosition(0,0.5,5);
            Qt3D::qApp3d->setWindowOrientation(0,0,1);
            Qt3D::qApp3d->setScaleFactor(1.0/150.0);
            Qt3D::qApp3d->hideInteractionRay(true);
            Qt3D::qApp3d->setCamera(this);
            Qt3D::qApp3d->setAutoUpdate(false);
            Qt3D::qApp3d->setEnabled(true);
            Qt3D::qApp3d->setFocusPolicy(true);
            Qt3D::qApp3d->setInteractionMode(2);
        }

        void App::preFrame(){
            alice::App::preFrame();

            ////// QT3D Block //////

            int leftButtonID = 0;   // Left Click on a mouse with standalone.jconf, may differ on other VR systems

            Qt3D::trackerEvent::Flags buttonEvent = Qt3D::trackerEvent::noButton;
            Qt3D::trackerEvent::Flags stateEvent = Qt3D::trackerEvent::deviceMove;

            if( mInput->getButtonChanged(leftButtonID) ){    //Handle button toggle
                buttonEvent = Qt3D::trackerEvent::leftButton;
                if( mInput->getButtonState(leftButtonID) ) stateEvent = Qt3D::trackerEvent::buttonPressed;
                else                            stateEvent = Qt3D::trackerEvent::buttonReleased;
            }
            else if( mInput->getButtonState(leftButtonID) ){ //Not toggled but pressed
                buttonEvent = Qt3D::trackerEvent::leftButton;
                stateEvent = Qt3D::trackerEvent::deviceMove;
            }

            gmtl::Vec3f pos	= mInput->getRayStart();
            gmtl::Vec3f dir	= mInput->getRayEnd() - pos;

            Qt3D::trackerEvent* event = new Qt3D::trackerEvent(buttonEvent, stateEvent, pos[0], pos[1], pos[2], dir[0], dir[1], dir[2]);
            bool interactedWithWindows = Qt3D::qApp3d->sendEventTracker(event);

            ////// QT3D Block Ends //////

            //Signal OSG to check intersection with scene objects if no qt3d interaction
            if(!mInput->applyManipulation()) mInput->applySelectionTest(!interactedWithWindows);
        }

        void App::bufferPreDraw(){
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void App::contextPreDraw(){
            Qt3D::qApp3d->updateTextures();
            alice::App::contextPreDraw();
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
                gmtl::Vec3f start	= mInput->getRayStart();
                gmtl::Vec3f end		= mInput->getRayEnd();

                glVertex3f(start[0],start[1],start[2]);
                glVertex3f(end[0],end[1],end[2]);
            }
            glEnd();
            // Wand Drawn

            Qt3D::qApp3d->drawWindows();
            
            glPopAttrib();
            glPopAttrib();
            glPopAttrib();
        }

        void App::exit(){
            qApp->exit();
        }

        void App::getModelview(double* modelView){
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    modelView[i*4+j] = (i==j ? 1:0);
        }
    }
}


