#include "servergame.h"

#include <QDebug>
#include <QMessageBox>


void ServerGame::chooseYourROLE(QString ClientRole)
{
    YOUR_ROLE = ClientRole;
}

void ServerGame::makeTurn()
{

}

ServerGame::ServerGame() {
  // При старте программы сразу начинается новая игра
  //newGame();
    connect(Server,SIGNAL(sendRecievedRole(QString)),this, SLOT(chooseYourROLE(QString)));
}

// Новая игра
void ServerGame::mapResize() {
  Map.resize(MapSize);

  for(int i = 0; i < MapSize; ++i)
    Map[i].resize(MapSize);
}

void ServerGame::newGame() {
  //mapResize();

  // Первыми ходят всегда крестики
  state = S_X_MOVE;
   Server->start();
  // Заполняем поле пустыми клетками, без крестиков и ноликов
//  for(int i = 0; i < MapSize; i++)
//    for(int j = 0; j < MapSize; j++)
//      Map[i][j] = ' ';
}

QString ServerGame::getStateString() {
  switch(state) {
    case S_X_MOVE:
      return QString("Ход крестиков");

    case S_O_MOVE:
      return QString("Ход ноликов");

    case S_X_WIN:
      return QString("Крестики выиграли!");

    case S_O_WIN:
      return QString("Нолики выиграли!");

    case S_DRAW:
      return QString("Ничья! :)");

    default:
      return QString("Ошибка в программе!");
      assert(false);
  }

  return QString("Непредусмотренное состояние игры!");
}

// Совершаем ход
//QString ServerGame::makeMove(int row, int col) {

//  if(Map[row][col] != ' ') {
//    QMessageBox::critical(NULL, "Ошибка",
//                          "Нельзя ходить в занятую клетку");
//    return QString("!");
//  }

//  switch (state) {
//    case S_X_MOVE:
//      Map[row][col] = S_X;
//      state = S_O_MOVE;
//      break;

//    case S_O_MOVE:
//      Map[row][col] = S_O;
//      state = S_X_MOVE;
//      break;

//    default:
//      return QString(" ");
//  }

//  checkGameOver();
//  return QString(Map[row][col]);
//}

// Три крестика или три нолика (или больше/меньше)

//void ServerGame::checkLine(std::vector<char> a) {
//  // Если не все элементы равны => не подходит
//  for(int i = 1; i < MapSize; ++i)
//    if(a[i - 1] != a[i])
//      return;

//  // Кто-то выиграл :)
//  switch(a[0]) {
//    case S_X:
//      state = S_X_WIN;
//      break;

//    case S_O:
//      state = S_O_WIN;
//      break;

//    default:
//      break; // Если не крестики и не нолики, то не подходит
//  }
//}

//void ServerGame::checkGameOver() {
//  std::vector<char> a(MapSize);

//  // == Проверяем диагонали ==
//  // Основная диагональ
//  for(int i = 0; i < MapSize; ++i)
//    a[i] = Map[i][i];

//  checkLine(a);

//  // Дополнительная диагональ
//  //   (0,0) (0,1) [0,2]
//  //   (1,0) [1,1] (1,2)
//  //   [2,0] (2,1) (2,2)
//  for(int i = 0; i < MapSize; ++i)
//    a[i] = Map[MapSize - i - 1][i];

//  checkLine(a);

//  // Вертикальные и горизонтальные линии
//  for(int i = 0; i < MapSize; ++i) {
//    // Вертикальная линия
//    // копируем в a i-ый столбец
//    for(int j = 0; j < MapSize; ++j)
//      a[j] = Map[j][i];

//    checkLine(a);

//    // Горизонтальная линия
//    checkLine(Map[i]);
//  }

//  // Проверяем что крестики или нолики
//  // выиграли и выходим
//  switch(state) {
//    case S_X_WIN:
//    case S_O_WIN:
//      emit unavailible_bottoms();

//      return;

//    default:
//      ; // Do nothing
//  }

//  // Ничья = не осталось пустых клеток
//  int cnt = 0; // Количество пустых клеток

//  for(int i = 0; i < MapSize; i++)
//    for(int j = 0; j < MapSize; j++)
//      if(Map[i][j] == ' ')
//        cnt++;

//  qDebug() << "cnt = " << cnt;

//  if(cnt == 0)
//    state = S_DRAW;
//}

const char* ServerGame::getCell(int i, int j) {
  static const char buf = Map[i][j];

  return &buf;
}

