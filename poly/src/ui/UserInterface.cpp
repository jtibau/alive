#include "UserInterface.h"

#include <Qt3D/include/main/qapplication3d.h>

#include <iostream>

UserInterface::UserInterface(QWidget* parent, Qt::WindowFlags flags)
  : QMainWindow(parent,flags)
{
	setupUi(this);
}

void UserInterface::setApp(alice::App* app){ mApp = app; }
void UserInterface::on_pushButton_clicked(){
	std::cout << "Exit\n";
	mApp->exit();
}
