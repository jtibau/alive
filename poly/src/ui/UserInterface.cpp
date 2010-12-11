#include "UserInterface.h"

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>

#include <QMatrix4x4>

#include <main/qapplication3d.h>

#include <iostream>

UserInterface::UserInterface(QWidget* parent, Qt::WindowFlags flags)
    : QMainWindow(parent,flags)
{
    setupUi(this);
    camN = 1;

    qreal values[16];
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            values[i*4 + j] = (i==j?1:0);
    QMatrix4x4 mat(values);

    QListWidgetItem *start = new QListWidgetItem("Start", cameraListWidget);
    start->setData(Qt::UserRole,mat);
    cameraListWidget->addItem(start);
}

void UserInterface::setApp(alice::App* app){ mApp = app; }
void UserInterface::on_exitButton_clicked(){ mApp->exit(); }

void UserInterface::on_addButton_clicked(){
    gmtl::Matrix44f nav = mApp->mInput->navigationMatrix();
    const float* navData =  nav.getData();

    qreal values[16];
    for(int i=0; i<16; i++)
        values[i] = navData[i];
    QMatrix4x4 mat(values);

    QString name = "Nav";
    name.append(QString("%1").arg(camN++));
    QListWidgetItem *newNavigationMat = new QListWidgetItem(name, cameraListWidget);
    newNavigationMat->setData(Qt::UserRole,mat);
    cameraListWidget->addItem(newNavigationMat);
}

void UserInterface::on_removeButton_clicked(){
    delete cameraListWidget->currentItem();
}

void UserInterface::on_cameraListWidget_itemClicked(){
    QMatrix4x4 storedNavigation =
        cameraListWidget->currentItem()->data(Qt::UserRole).value<QMatrix4x4>();

    float matValues[16];
    qreal* storedValues = storedNavigation.data();
    for(int i=0; i<16; i++)
        matValues[i] = storedValues [i];

    gmtl::Matrix44f restoredNavigation;
    restoredNavigation.set(matValues);
    gmtl::transpose(restoredNavigation);

    mApp->mInput->navigationMatrix(restoredNavigation);
}
