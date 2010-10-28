/******************************************************************************
 *
 *	This library is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This library is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#pragma once

#include <alive/App.h>

#include <QObject>
#include <main/modelview.h>


namespace alive {
  namespace poly {
    class App : public QObject, public alive::App, public Qt3D::Modelview  {
    Q_OBJECT
    public:
      App(alive::Scene* scene = NULL, alive::InteractionMethod* interactionMethod = NULL);

      ~App();
      
      void exit();
    /*
      void init(alive::Input* input);
      void contextInit();
      void preFrame();
      void latePreFrame();
      void bufferPreDraw();
      void contextPreDraw();
      void draw();
      void intraFrame();
      void contextPostDraw();
      void postFrame();
      void contextClose();
      
      // Override Qt3D::Modelview
      void getModelview(double*);
      */
      
      
    };
  }
}
