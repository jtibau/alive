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
