#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

// void GLWidget::resizeGL(int w, int h) {}

void GLWidget::SetProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLfloat fov = 60.0 * M_PI / 180;
  GLfloat near = 1 / tan(fov / 2);
  if (settings_.projection_type == 0) {
    glOrtho(-2., 2., -2., 2., -10, 10.);
  } else {
    glFrustum(-0.8, 0.8, -0.8, 0.8, near, 100.);
    glTranslated(0, 0, -3);
  }
}

void GLWidget::paintGL() {
  SetProjection();
  glClearColor(settings_.back_color.redF(), settings_.back_color.greenF(),
               settings_.back_color.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  DrawVertices();
  DrawEdges();
  update();
}

void GLWidget::ParseFile(QString file_path) {
  vertices_.clear();
  faces_.clear();
  s21::Status status = controller_.ParseFile(file_path.toStdString());
  if (status == s21::Status::error) {
    QString error_str = "Choose correct file";
    QMessageBox::information(this, "ERROR", error_str);
    ClearData();
    return;
  }
  vertices_ = controller_.get_vertices();
  controller_.CenterFunc(vertices_);
  faces_ = controller_.get_faces();
  vertices_number_ = controller_.get_vertices_number();
  faces_number_ = controller_.get_faces_number();
  vertices_in_face_number_ = controller_.get_vertices_in_face_number();
  update();
}

void GLWidget::ClearData() {
  vertices_.clear();
  faces_.clear();
  vertices_number_ = 0;
  faces_number_ = 0;
  vertices_in_face_number_ = 0;
  translation_x_ = translation_y_ = translation_z_ = 0;
  rotation_x_ = rotation_y_ = rotation_z_ = 0;
  // scale_ = 1;
}

void GLWidget::DrawVertices() {
  if (settings_.vertices_type == s21::VerticesType::kNone) {
    return;
  }
  if (settings_.vertices_type == s21::VerticesType::kCircle) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
  glPointSize(settings_.vertex_size);
  glColor3d(settings_.vertex_color.redF(), settings_.vertex_color.greenF(),
            settings_.vertex_color.blueF());
  glBegin(GL_POINTS);
  for (unsigned i = 0; i < vertices_number_; i++) {
    double x = vertices_[i][0];
    double y = vertices_[i][1];
    double z = vertices_[i][2];
    glVertex3d(x, y, z);
  }
  glEnd();
}

void GLWidget::DrawEdges() {
  glColor3d(settings_.edge_color.redF(), settings_.edge_color.greenF(),
            settings_.edge_color.blueF());
  glLineWidth(settings_.line_thickness);
  if (settings_.edges_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  auto faces = faces_;
  auto vertices = vertices_;
  auto it = faces.begin();
  for (unsigned int i = 0; i < faces_number_; i++) {
    const std::vector<unsigned>& indices = it->second;
    glBegin(GL_LINE_LOOP);
    for (unsigned index : indices) {
      const std::vector<double>& vertex = vertices[index - 1];
      glVertex3d(vertex[0], vertex[1], vertex[2]);
    }
    glEnd();
    it++;
  }
}

void GLWidget::RotateModel(char axis, double value) {
  double result_value = 0;
  switch (axis) {
    case 'x':
      result_value = value - rotation_x_;
      rotation_x_ = value;
      controller_.Transform(vertices_, result_value, new s21::RotateX());
      break;
    case 'y':
      result_value = value - rotation_y_;
      rotation_y_ = value;
      controller_.Transform(vertices_, result_value, new s21::RotateY());
      break;
    case 'z':
      result_value = value - rotation_z_;
      rotation_z_ = value;
      controller_.Transform(vertices_, result_value, new s21::RotateZ());
      break;
  }
}

void GLWidget::MoveModel(char axis, double value) {
  double result_value = 0;
  switch (axis) {
    case 'x':
      result_value = (value - translation_x_) / 10;
      translation_x_ = value;
      controller_.Transform(vertices_, result_value, new s21::MoveX());
      break;
    case 'y':
      result_value = (value - translation_y_) / 10;
      translation_y_ = value;
      controller_.Transform(vertices_, result_value, new s21::MoveY());
      break;
    case 'z':
      result_value = (value - translation_z_) / 10;
      translation_z_ = value;
      controller_.Transform(vertices_, result_value, new s21::MoveZ());
      break;
  }
}

void GLWidget::ScaleModel(double value) {
  double tmp_scale = value / scale_;
  if (value > 0) {
    scale_ = value;
    controller_.Transform(vertices_, tmp_scale, new s21::Scale());
  }
}

std::vector<std::vector<double>> GLWidget::get_vertices() const {
  std::vector<std::vector<double>> vertices = controller_.get_vertices();
  return vertices;
}

std::map<unsigned, std::vector<unsigned>> GLWidget::get_faces() const {
  return controller_.get_faces();
}

unsigned GLWidget::get_vertices_number() const {
  return controller_.get_vertices_number();
}

unsigned GLWidget::get_faces_number() const {
  return controller_.get_faces_number();
}
unsigned GLWidget::get_vertices_in_face_number() const {
  return controller_.get_vertices_in_face_number();
}

s21::DisplaySettings GLWidget::get_settings() { return settings_; }

int GLWidget::get_pojection_type() const { return settings_.projection_type; }

int GLWidget::get_edges_type() const { return settings_.edges_type; }

s21::VerticesType GLWidget::get_vertices_type() const {
  return settings_.vertices_type;
}

void GLWidget::set_projection_type(int type) {
  settings_.projection_type = type;
}

void GLWidget::set_edges_type(int type) { settings_.edges_type = type; }

void GLWidget::set_vertices_type(s21::VerticesType type) {
  settings_.vertices_type = type;
}

void GLWidget::set_line_thickness(GLfloat thickness) {
  settings_.line_thickness = thickness;
}

void GLWidget::set_vertex_size(GLfloat size) { settings_.vertex_size = size; }

void GLWidget::set_edge_color(QColor color) {
  settings_.edge_color = color;
  update();
}

void GLWidget::set_vertex_color(QColor color) {
  settings_.vertex_color = color;
}

void GLWidget::set_back_color(QColor color) { settings_.back_color = color; }
