#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QMainWindow>
#include <QSettings>

#include "gif.h"

#define ORGANIZATION_NAME "countbodya"
#define ORGANIZATION_DOMAIN "count.bodya"
#define APPLICATION_NAME "3D Viewer"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void LoadFile(QString file_path);

 private slots:
  void on_openFileButton_clicked();

  void on_parallelRadioButton_clicked();

  void on_centralRadioButton_clicked();

  void on_backgroundButton_clicked();

  void on_edgeColorButton_clicked();

  void on_solidRadioButton_clicked();

  void on_dashedRadioButton_clicked();

  void on_thicknesslSlider_valueChanged(int value);

  void on_noneRadioButton_clicked();

  void on_circleRadioButton_clicked();

  void on_circleRadioButton_2_clicked();

  void on_rotateXScrollBar_valueChanged(int value);

  void on_rotateYScrollBar_valueChanged(int value);

  void on_rotateZScrollBar_valueChanged(int value);

  void on_translateXScrollBar_valueChanged(int value);

  void on_translateYScrollBar_valueChanged(int value);

  void on_translateZScrollBar_valueChanged(int value);

  void on_scaleScrollBar_valueChanged(int value);

  void on_sizelSlider_valueChanged(int value);

  void on_verticesColorButton_clicked();

  void on_screenButton_clicked();

  void on_gifButton_clicked();

 private:
  void ConnectSignals();
  void UpdateScrollBar(const QString &value);
  void SaveSettings();
  void LoadSettings();
  void ResetAffine();
  void SaveGif(QString gif_name);

  Ui::MainWindow *ui_;
  QSettings *settings_;
};
#endif  // MAINWINDOW_H
