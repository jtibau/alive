#pragma once

#include "ui_UserInterface.h"

#include <QMainWindow>
#include "../App.h"

/** @class UserInterface UserInterface.h
  * @brief Provides the connection between the Qt UI layer and our application.
  */
class UserInterface : public QMainWindow, private Ui::MainWindow {
Q_OBJECT

public:

	/** @brief Default constructor of a Qt widget.
	  *
	  * Initializes components of the UI.
	  */
	UserInterface(QWidget* parent, Qt::WindowFlags flags=0);

public Q_SLOTS:

	/** @brief Stores a pointer to the application object. */
	void setApp(alice::poly::App* app);

	/** @brief Tells the app to exit. */
	void on_exitButton_clicked();

	/** @brief Adds the current navigation matrix to the list. */
	void on_addButton_clicked();

	/** @brief Removes the currently selected nav matrix of the list. */
	void on_removeButton_clicked();

	/** @brief Upon clicking on a listed item from the camera list, changes the nav matrix to it. */
	void on_cameraListWidget_itemClicked();

	/** @brief Tells the App to center the scene */
	void on_centerButton_clicked();

private:

	alice::poly::App* mApp;		/**< Pointer to the application object. */
	int camN;					/**< Number of next cam. Used to vary the name of the next cam on the list. */
};
