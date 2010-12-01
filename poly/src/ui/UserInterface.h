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
  
  private:
  alice::App* mApp;
};
