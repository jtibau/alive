#pragma once

#include <alice/App.h>

#include <QObject>
#include <main/modelview.h>


namespace alice {
	namespace poly {
		/** @defgroup poly Polygon Renderer
		  * @{
		  */

		/** @class alice::poly::App App.h
		  * @brief Accomodates Qt3D into our alice application.
		  *
		  * Besides handling Qt3D it acts closely like the parent class.
		  */
		class App : public QObject, public alice::App, public Qt3D::Modelview  {
		Q_OBJECT
		public:
			/** @brief The only constructor takes a scene and an interaction method
			  *
			  * While it is possible to not give a scene, we would get a pretty boring application.
			  * Without an interaction method we can still rely on the tracking system to navigate the scene. 
			  */
			App(alice::SceneRenderer* scene = NULL, alice::InteractionMethod* interactionMethod = NULL);

			/** @brief Exit the application, by properly closing Qt3D */
			void exit();

			/** @brief Update stuff */
			void preFrame();
			
			/** @brief Prepare the buffer for drawing */
			void bufferPreDraw();
			
			/** @brief Before drawing, inside the GL context */
			void contextPreDraw();
			
			/** @brief Ask the scene to draw itself. Also draws the ray and qt3d windows. */
			void draw();

			// Override Qt3D::Modelview
			void getModelview(double*);
		};
		/** @}
		 */
	}
}
