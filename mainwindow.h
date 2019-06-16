#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>

#include <QtCore>
#include <QtGui>

#include "game.h"
#include "servergame.h"
#include "cellbutton.h"

namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow {
  Q_OBJECT

private slots:
  void setUnavailableBottoms(bool);
//  void Server_namePlayerRole(QString);
public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

  void exit_application();

  void resizeButtonsArray();
 private slots:
  void updateWindow(); // Обновить поле
  void newGame(); // Новая игра

  void newServerGame(); //новая игра по серверу
//  void on_exitButton_clicked();

  void on_setFieldSize_triggered();



  void on_action_2_triggered();

  void on_action_triggered();

private:
  Ui::MainWindow* ui;
  Game game; // Одиночка
  ServerGame ServerGame; // Мультиплеер
  vector<vector<CellButton*> > cells; // Клетки поля (кнопки)
  void updateGameButtons(); // Обновляем кнопки - клетки поля
};

#endif // MAINWINDOW_H
