#ifndef SERVERGAME_H
#define SERVERGAME_H

#include <QString>
#include <vector>
#include <QObject>

#include "server.h"


extern QString YOUR_ROLE;

extern int MapSize;

// Состояние игры
enum ServerGameState {
    S_X_MOVE, // Ход крестиков
    S_O_MOVE, // Ход ноликов
    S_X_WIN,  // Крестики выиграли
    S_O_WIN,  // Нолики выиграли
    S_DRAW    // Ничья
};

// Все что происодит на поле и логика игрового мира
// Ходы, выйгрыш/проигрыш
class ServerGame : public QMainWindow{

  Q_OBJECT
private:
  ServerGameState state; // Текущее состояние игры
  // Игровое поле
  std::vector<std::vector<char> > Map;
  // Проверка выигрыша.
  // Проверяется одна строка,
  // один столбец или одна диагональ
  void checkLine(std::vector<char> a);

  server* Server = new server;

private slots:
    void makeTurn();

 public:
  // Конструктор
  ServerGame();
  // Новая игра без пересоздания объекта
  void newGame();
  // Получаем строку, соответствующую состоянию игры
  QString getStateString();
  // Совершаем ход, возвращает строку для клетки на форме
  QString makeMove(int row, int col);
  // Проверяем на окончание игры
  void checkGameOver();

  // Состояние ячейки
  const char* getCell(int i, int j);
  void resizeMap();
  void mapResize();
public slots:
  void chooseYourROLE(QString);
public:
signals:
  void unavailible_bottoms();
  void SendRole(QString);
};

#endif // SERVERGAME_H
