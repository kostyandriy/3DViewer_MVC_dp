#ifndef FACADE_CONTROLLER_H
#define FACADE_CONTROLLER_H

#include "../Model/facade_model.h"

namespace s21 {
class ControllerFacade {
 public:
  enum Status ParseFile(std::string file_name);
  std::vector<std::vector<double>> get_vertices() const;
  std::map<unsigned, std::vector<unsigned>> get_faces() const;

  unsigned get_vertices_number() const;
  unsigned get_vertices_in_face_number() const;
  unsigned get_faces_number() const;

  void Transform(std::vector<std::vector<double>> &data, double variable,
                 ITransformation *strategy);
  void CenterFunc(std::vector<std::vector<double>> &data);

 private:
  Facade model_;
};

}  // namespace s21

// вершины, полигоны, парсер
#endif  // FACADE_CONTROLLER_H