#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets>

#include "../Controller/facade_controller.h"

namespace s21 {
enum class VerticesType {
  kNone = 0,
  kCircle,
  kSquare,
};

struct DisplaySettings {
  int projection_type;
  int edges_type;
  VerticesType vertices_type;
  GLfloat line_thickness;
  GLfloat vertex_size;
  QColor edge_color;
  QColor vertex_color;
  QColor back_color;
};
}  // namespace s21

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit GLWidget(QWidget *parent = nullptr);

  void ParseFile(QString file_path);
  void ClearData();

  std::vector<std::vector<double>> get_vertices() const;
  std::map<unsigned, std::vector<unsigned>> get_faces() const;
  unsigned get_vertices_number() const;
  unsigned get_faces_number() const;
  unsigned get_vertices_in_face_number() const;

  s21::DisplaySettings get_settings();
  int get_pojection_type() const;
  int get_edges_type() const;
  s21::VerticesType get_vertices_type() const;
  void set_projection_type(int type);
  void set_edges_type(int type);
  void set_vertices_type(s21::VerticesType type);
  void set_line_thickness(GLfloat thickness);
  void set_vertex_size(GLfloat size);
  void set_edge_color(QColor color);
  void set_vertex_color(QColor color);
  void set_back_color(QColor color);

  void MoveModel(char axis, double value);
  void RotateModel(char axis, double value);
  void ScaleModel(double value);

 protected:
  void initializeGL() override;
  void paintGL() override;
  // void resizeGL(int w, int h) override;

 private:
  void SetProjection();
  void DrawVertices();
  void DrawEdges();

  s21::ControllerFacade controller_;
  std::vector<std::vector<double>> vertices_;
  std::map<unsigned, std::vector<unsigned>> faces_;
  unsigned vertices_number_;
  unsigned faces_number_;
  unsigned vertices_in_face_number_;
  s21::DisplaySettings settings_;

  double translation_x_ = 0, translation_y_ = 0, translation_z_ = 0;
  double rotation_x_ = 0, rotation_y_ = 0, rotation_z_ = 0;
  double scale_ = 1;
};

#endif  // GLWIDGET_H
