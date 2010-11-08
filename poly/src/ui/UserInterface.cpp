#include "UserInterface.h"

#include <Qt3D/include/main/qapplication3d.h>

UserInterface::UserInterface(QWidget* parent, Qt::WindowFlags flags)
  : QMainWindow(parent,flags)
{
	setupUi(this);
}

void UserInterface::setApp(alive::App* app){ mApp = app; }
void UserInterface::on_pushButton_clicked(){ mApp->exit(); }
