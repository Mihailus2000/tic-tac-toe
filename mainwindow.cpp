#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> // Для qDebug()
#include <QFileDialog> // Диалог выбора имени файла
#include <QMessageBox> // Диалоговое окно с сообщением
#include "gamesettings.h"

void MainWindow::resizeButtonsArray() {
  cells.resize(MapSize);

  for(int i = 0; i < MapSize; ++i)
    cells[i].resize(MapSize);

}

void MainWindow::setUnavailableBottoms()
{
    for(int i = 0; i < MapSize; i++)
      for(int j = 0; j < MapSize; j++) {
        cells[i][j]->setEnabled(false);
      }
}

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Скрываем кнопку с прототипом
  ui->fontPrototypeButton->setVisible(false);

  // Задаём размер массиву кнопок
  resizeButtonsArray();

  // Связываем дизактивацию всех кнопок с игрой
  connect(&game,SIGNAL(unavailible_bottoms()),this,SLOT(setUnavailableBottoms()));

  // Заполним весь массив кнопок поля NULL
  for(int i = 0; i < MapSize; i++)
    for(int j = 0; j < MapSize; j++)
      cells[i][j] = NULL;

  // Начало игры
  qDebug() << "Constructor >>> ";
  newGame();
  qDebug() << "<<< Constructor";
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::exit_application() {
  // Выход из программы
  QApplication::exit();
}



// После изменения состояния игры
void MainWindow::updateWindow() {
  qDebug() << "updateWindow()" << endl;
  update();
  ui->moveLabel->setText(game.getStateString());
  // Подстраиваем размер, т.к. эта метка не в Layout

  // Изменение размера окна
//  this->setGeometry(250,200,50+66*MapSize+195,80+66*MapSize+10);
  this->setFixedSize(25+66*MapSize+195,40+66*MapSize+10);

  ui->moveLabel->setGeometry(100+66*MapSize,this->height()/2-ui->moveLabel->height()*2,ui->moveLabel->width(),ui->moveLabel->height());
  ui->moveLabel->adjustSize();
  ui->exitButton->setGeometry(100+66*MapSize,this->height()/2,ui->exitButton->width(),ui->exitButton->height());

  int windowSize = this->geometry().width();
  QRect rect = ui->moveLabel->geometry();
  //qDebug() << windowSize << "  Width of lable: " << rect.width();

  int borderSize = 15; // Бордюр справа
  rect.moveLeft(windowSize - rect.width() - borderSize);
 // rect.(this->geometry().height()/2-ui->moveLabel->height());
  ui->moveLabel->setGeometry(rect);
  update();
}

void MainWindow::newGame() { // Новая игра
  game.newGame();
  updateWindow();
  updateGameButtons();
}

void MainWindow::updateGameButtons() {
  int cellSize = 60; // Размер кнопки
  int cellSpace = 6; // Отступ
  int topSpace = 40; // Отступ сверху
  int leftSpace = 25; // Отступ слева
//  int randOffset = 5;

  for(unsigned int i = 0; i < cells.size(); ++i)
    for(unsigned int j = 0; j < cells[i].size(); ++j) {
      if(cells[i][j] != NULL){
        delete cells[i][j];
          qDebug() << "Delete: " << i << " " << j;
        }
    }

  resizeButtonsArray();

  // Создаём массив MapSize на MapSize из QPushButton
  for(int i = 0; i < MapSize; i++)
    for(int j = 0; j < MapSize; j++) {
      cells[i][j] = new CellButton(game.getCell(i, j), this, i, j, game);
      // Шрифт как в прототипе
      cells[i][j]->setFont(ui->fontPrototypeButton->font());
      // Задаём размеры и положение кнопки
      cells[i][j]->setGeometry(
        (cellSize + cellSpace) * j + leftSpace,
        (cellSize + cellSpace) * i + topSpace,
        cellSize, // Ширина кнопки
        cellSize  // Высота кнопки
      );

      cells[i][j]->setVisible(true);

      connect(cells[i][j], SIGNAL(clicked()),
              cells[i][j], SLOT(slotCellClicked()));

      connect(cells[i][j], SIGNAL(clicked()),
              this, SLOT(updateWindow()));
    }
}


//void MainWindow::on_exitButton_clicked() {

//}


void MainWindow::on_setFieldSize_triggered() {
  // Вызываем окно настройки размера поля
  GameSettings gs(this);
  gs.exec();

  // После изменения размера поля
  // рестарт игры
  newGame();
}

