#include "facade_model.h"

namespace s21 {
Status Facade::ParseObject(std::string file_name) {
  return parser_->ParseObject(file_name);
}

std::vector<std::vector<double>> Facade::get_vertices() const {
  return parser_->get_vertices();
}

unsigned Facade::get_vertices_number() const {
  return parser_->get_vertices_number();
}

unsigned Facade::get_vertices_in_face_number() const {
  return parser_->get_vertices_in_face_number();
}

std::map<unsigned, std::vector<unsigned>> Facade::get_faces() const {
  return parser_->get_faces();
}

unsigned Facade::get_faces_number() const {
  return parser_->get_faces_number();
}

void Facade::Transform(std::vector<std::vector<double>> &data, double variable,
                       ITransformation *strategy) {
  transform_ = new Transformer(strategy);
  transform_->Transform(data, variable);
}

void Facade::CenterFunc(std::vector<std::vector<double>> &data) {
  center_.center_model(data);
  // transform_ = new Transformer(new Scale());
  // transform_->Transform(data, scale);
}

}  // namespace s21
