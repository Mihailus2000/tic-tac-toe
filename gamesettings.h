#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QDialog>

extern int MapSize;


namespace Ui {
class GameSettings;
}

class GameSettings : public QDialog {
  Q_OBJECT

 public:
  explicit GameSettings(QWidget* parent = 0);
  ~GameSettings();

 private slots:
  void on_buttonBox_accepted();

 private:
  Ui::GameSettings* ui;
};

#endif // GAMESETTINGS_H
