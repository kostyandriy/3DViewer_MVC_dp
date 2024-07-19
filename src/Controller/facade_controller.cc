#include "facade_controller.h"

namespace s21 {
enum Status ControllerFacade::ParseFile(std::string file_name) {
  return model_.ParseObject(file_name);
}

std::vector<std::vector<double>> ControllerFacade::get_vertices() const {
  return model_.get_vertices();
}

std::map<unsigned, std::vector<unsigned>> ControllerFacade::get_faces() const {
  return model_.get_faces();
}

void ControllerFacade::Transform(std::vector<std::vector<double>> &data,
                                 double variable, ITransformation *strategy) {
  model_.Transform(data, variable, strategy);
}

void ControllerFacade::CenterFunc(std::vector<std::vector<double>> &data) {
  model_.CenterFunc(data);
}

unsigned ControllerFacade::get_vertices_number() const {
  return model_.get_vertices_number();
}

unsigned ControllerFacade::get_vertices_in_face_number() const {
  return model_.get_vertices_in_face_number();
}

unsigned ControllerFacade::get_faces_number() const {
  return model_.get_faces_number();
}

}  // namespace s21