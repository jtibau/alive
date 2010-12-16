#pragma once

#include "ui_UserInterface.h"

#include <QMainWindow>

#include <alice/App.h>

class UserInterface : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT
  
  public:

  UserInterface(QWidget* parent, Qt::WindowFlags flags=0);
  
  public Q_SLOTS:
  void setApp(alice::App* app);
  void on_exitButton_clicked();

  void on_addButton_clicked();
  void on_removeButton_clicked();
  
  void on_cameraListWidget_itemClicked();

  private:

  alice::App* mApp;
  int camN;

};
