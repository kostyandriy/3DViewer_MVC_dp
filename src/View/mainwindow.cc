#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  setWindowTitle("3DViewer_v2.0");
  LoadSettings();
}

MainWindow::~MainWindow() {
  SaveSettings();
  delete ui_;
}

void MainWindow::ConnectSignals() {
  connect(ui_->rotateXLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::UpdateScrollBar);
  connect(ui_->rotateYLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::UpdateScrollBar);
  connect(ui_->rotateZLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::UpdateScrollBar);
  connect(ui_->translateXLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::UpdateScrollBar);
  connect(ui_->translateYLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::UpdateScrollBar);
  connect(ui_->translateZLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::UpdateScrollBar);
  connect(ui_->scaleLineEdit, &QLineEdit::textChanged, this,
          &MainWindow::UpdateScrollBar);
}

void MainWindow::UpdateScrollBar(const QString &value) {
  double doubleValue = value.toDouble();
  if (sender() == ui_->rotateXLineEdit) {
    ui_->rotateXScrollBar->setValue(static_cast<int>(doubleValue));
  } else if (sender() == ui_->rotateYLineEdit) {
    ui_->rotateYScrollBar->setValue(static_cast<int>(doubleValue));
  } else if (sender() == ui_->rotateZLineEdit) {
    ui_->rotateZScrollBar->setValue(static_cast<int>(doubleValue));
  } else if (sender() == ui_->translateXLineEdit) {
    ui_->translateXScrollBar->setValue(static_cast<int>(doubleValue));
  } else if (sender() == ui_->translateYLineEdit) {
    ui_->translateYScrollBar->setValue(static_cast<int>(doubleValue));
  } else if (sender() == ui_->translateZLineEdit) {
    ui_->translateZScrollBar->setValue(static_cast<int>(doubleValue));
  } else if (sender() == ui_->scaleLineEdit) {
    ui_->scaleScrollBar->setValue(static_cast<int>(doubleValue));
  }
}

void MainWindow::SaveSettings() {
  QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                     ORGANIZATION_NAME, APPLICATION_NAME);
  s21::DisplaySettings display_settings = ui_->glwidget->get_settings();
  settings.beginGroup("Colors");
  settings.setValue("EdgeColor", display_settings.edge_color);
  settings.setValue("VertexColor", display_settings.vertex_color);
  settings.setValue("BackColor", display_settings.back_color);
  settings.endGroup();

  settings.beginGroup("DisplaySettings");
  settings.setValue("ProjectionMode", display_settings.projection_type);
  settings.setValue("LineSolid", display_settings.edges_type);
  settings.setValue("VertexDisplay",
                    static_cast<int>(display_settings.vertices_type));
  settings.setValue("LineThickness", display_settings.line_thickness);
  settings.setValue("VertexSize", display_settings.vertex_size);
  settings.endGroup();
}

void MainWindow::LoadSettings() {
  QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                     ORGANIZATION_NAME, APPLICATION_NAME);
  settings.beginGroup("Colors");
  ui_->glwidget->set_edge_color(
      settings.value("EdgeColor", QColor(Qt::black)).value<QColor>());
  ui_->glwidget->set_vertex_color(
      settings.value("VertexColor", QColor(Qt::black)).value<QColor>());
  ui_->glwidget->set_back_color(
      settings.value("BackColor", QColor(Qt::blue)).value<QColor>());
  settings.endGroup();

  settings.beginGroup("DisplaySettings");
  ui_->glwidget->set_projection_type(
      settings.value("ProjectionMode", 0).toInt());
  ui_->parallelRadioButton->setChecked(ui_->glwidget->get_pojection_type() ==
                                       0);
  ui_->centralRadioButton->setChecked(ui_->glwidget->get_pojection_type() != 0);

  ui_->glwidget->set_edges_type(settings.value("LineSolid", 0).toInt());
  ui_->solidRadioButton->setChecked(ui_->glwidget->get_edges_type() == 0);
  ui_->dashedRadioButton->setChecked(ui_->glwidget->get_edges_type() != 0);

  ui_->glwidget->set_vertices_type(static_cast<s21::VerticesType>(
      settings.value("VertexDisplay", 0).toInt()));
  ui_->noneRadioButton->setChecked(ui_->glwidget->get_vertices_type() ==
                                   s21::VerticesType::kNone);
  ui_->circleRadioButton->setChecked(ui_->glwidget->get_vertices_type() ==
                                     s21::VerticesType::kCircle);
  ui_->circleRadioButton_2->setChecked(ui_->glwidget->get_vertices_type() ==
                                       s21::VerticesType::kSquare);

  int lineThickness = settings.value("LineThickness", 0).toInt();
  ui_->thicknesslSlider->setValue(lineThickness);

  int vertexSize = settings.value("VertexSize", 0).toInt();
  ui_->sizelSlider->setValue(vertexSize);

  settings.endGroup();

  ui_->scaleScrollBar->setRange(1, 10);
  ui_->scaleScrollBar->setValue(5);
}

void MainWindow::ResetAffine() {
  ui_->rotateXScrollBar->setValue(0);
  ui_->rotateYScrollBar->setValue(0);
  ui_->rotateZScrollBar->setValue(0);
  ui_->translateXScrollBar->setValue(0);
  ui_->translateYScrollBar->setValue(0);
  ui_->translateZScrollBar->setValue(0);
  ui_->scaleScrollBar->setValue(5);
}

void MainWindow::SaveGif(QString gif_name) {
  QImage image(ui_->glwidget->size(), QImage::Format_RGBA8888);
  QImage scaled_image;
  QPainter painter(&image);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  QTime time;
  GifWriter gif;
  GifBegin(&gif, gif_name.toUtf8().data(), 640, 480, 10);

  for (int i = 1; i <= 50; i++) {
    ui_->gifButton->setText(QString::number(i / 10) + "s");
    ui_->glwidget->render(&painter);
    scaled_image = image.scaled(640, 480);
    GifWriteFrame(&gif, scaled_image.bits(), 640, 480, 10);
    time = QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < time)
      QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
  }
  ui_->gifButton->setText("GIF");
  GifEnd(&gif);
  QMessageBox messageBoxGif;
  messageBoxGif.information(0, "", "Gif animation saved successfully");
  ui_->gifButton->setEnabled(true);
}

void MainWindow::on_openFileButton_clicked() {
  QString file_path = QFileDialog::getOpenFileName(this, tr("Open File"), "~/",
                                                   "OBJ Files (*.obj)");
  QString file_name = QFileInfo(file_path).fileName();
  ui_->fileNameLineEdit->setText(file_name);
  ResetAffine();
  ui_->glwidget->ClearData();
  ui_->glwidget->ParseFile(file_path);
  QString vertices_number =
      QString::number(ui_->glwidget->get_vertices_number());
  ui_->verticesLineEdit->setText(vertices_number);
  QString faces_number = QString::number(ui_->glwidget->get_faces_number());
  ui_->edgesLineEdit->setText(faces_number);
  ConnectSignals();
  ui_->glwidget->update();
}

void MainWindow::on_parallelRadioButton_clicked() {
  ui_->glwidget->set_projection_type(0);
  ui_->glwidget->update();
}

void MainWindow::on_centralRadioButton_clicked() {
  ui_->glwidget->set_projection_type(1);
  ui_->glwidget->update();
}

void MainWindow::on_solidRadioButton_clicked() {
  ui_->glwidget->set_edges_type(0);
  ui_->glwidget->update();
}

void MainWindow::on_dashedRadioButton_clicked() {
  ui_->glwidget->set_edges_type(1);
  ui_->glwidget->update();
}

void MainWindow::on_edgeColorButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",
                                        QColorDialog::DontUseNativeDialog);
  ui_->glwidget->set_edge_color(color);
  ui_->glwidget->update();
}

void MainWindow::on_verticesColorButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",
                                        QColorDialog::DontUseNativeDialog);
  ui_->glwidget->set_vertex_color(color);
  ui_->glwidget->update();
}

void MainWindow::on_backgroundButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color",
                                        QColorDialog::DontUseNativeDialog);
  ui_->glwidget->set_back_color(color);
  ui_->glwidget->update();
}

void MainWindow::on_thicknesslSlider_valueChanged(int value) {
  ui_->glwidget->set_line_thickness(static_cast<GLfloat>(value / 5.));
  ui_->glwidget->update();
}

void MainWindow::on_noneRadioButton_clicked() {
  ui_->glwidget->set_vertices_type(s21::VerticesType::kNone);
  ui_->glwidget->update();
}

void MainWindow::on_circleRadioButton_clicked() {
  ui_->glwidget->set_vertices_type(s21::VerticesType::kCircle);
  ui_->glwidget->update();
}

void MainWindow::on_circleRadioButton_2_clicked() {
  ui_->glwidget->set_vertices_type(s21::VerticesType::kSquare);
  ui_->glwidget->update();
}

void MainWindow::on_rotateXScrollBar_valueChanged(int value) {
  ui_->glwidget->RotateModel('x', value);
  ui_->rotateXLineEdit->setText(QString::number(value));
}

void MainWindow::on_rotateYScrollBar_valueChanged(int value) {
  ui_->glwidget->RotateModel('y', value);
  ui_->rotateYLineEdit->setText(QString::number(value));
}

void MainWindow::on_rotateZScrollBar_valueChanged(int value) {
  ui_->glwidget->RotateModel('z', value);
  ui_->rotateZLineEdit->setText(QString::number(value));
}

void MainWindow::on_translateXScrollBar_valueChanged(int value) {
  ui_->glwidget->MoveModel('x', value);
  ui_->translateXLineEdit->setText(QString::number(value));
}

void MainWindow::on_translateYScrollBar_valueChanged(int value) {
  ui_->glwidget->MoveModel('y', value);
  ui_->translateYLineEdit->setText(QString::number(value));
}

void MainWindow::on_translateZScrollBar_valueChanged(int value) {
  ui_->glwidget->MoveModel('z', value);
  ui_->translateZLineEdit->setText(QString::number(value));
}

void MainWindow::on_scaleScrollBar_valueChanged(int value) {
  ui_->glwidget->ScaleModel(value);
  ui_->scaleLineEdit->setText(QString::number(value));
}

void MainWindow::on_sizelSlider_valueChanged(int value) {
  ui_->glwidget->set_vertex_size(value);
  ui_->glwidget->update();
}

void MainWindow::on_screenButton_clicked() {
  QString name = QFileDialog::getSaveFileName(this, tr("Save image"));
  if (!name.isEmpty()) {
    ui_->glwidget->grab().save(name);
  }
}

void MainWindow::on_gifButton_clicked() {
  QDateTime currentDate = QDateTime::currentDateTime();
  QString formattedTime = currentDate.toString("yyyy-MM-dd hh.mm.ss");
  QString namePattern = "Screen Cast " + formattedTime + ".gif";
  QString gifname = QFileDialog::getSaveFileName(
      this, tr("Save a gif animation"), namePattern, tr("gif (*.gif)"));
  if (gifname != "") {
    ui_->gifButton->setDisabled(true);
    SaveGif(gifname);
  }
}
