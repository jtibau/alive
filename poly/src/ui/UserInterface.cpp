#include "UserInterface.h"

#include <gmtl/Matrix.h>
#include <QMatrix4x4>
#include <Qt3D/include/main/qapplication3d.h>

#include <iostream>

UserInterface::UserInterface(QWidget* parent, Qt::WindowFlags flags)
  : QMainWindow(parent,flags)
{
	setupUi(this);
}

void UserInterface::setApp(alice::App* app){ mApp = app; }
void UserInterface::on_exitButton_clicked(){
	std::cout << "Exit\n";
	mApp->exit();
}
void UserInterface::on_addButton_clicked(){
  gmtl::Matrix44f nav = mApp->mInput->navigationMatrix();
  qreal values[16];
  const float* navData =  nav.getData();

  for(int i=0; i<16; i++) values[i] = navData[i];

  QMatrix4x4 mat(values);
}
