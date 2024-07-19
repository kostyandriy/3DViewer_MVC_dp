#ifndef FACADE_MODEL_H
#define FACADE_MODEL_H

#include "Parser/parser.h"
// #include "affine.h"
#include "center_model.h"
#include "transform.h"

namespace s21 {
class Facade {
 public:
  std::vector<std::vector<double>> get_vertices() const;
  unsigned get_vertices_number() const;
  unsigned get_vertices_in_face_number() const;
  std::map<unsigned, std::vector<unsigned>> get_faces() const;
  unsigned get_faces_number() const;
  enum Status ParseObject(std::string file_name);
  void Transform(std::vector<std::vector<double>> &data, double variable,
                 ITransformation *strategy);
  void CenterFunc(std::vector<std::vector<double>> &data);

 private:
  ObjectParser *parser_ = ObjectParser::get_instance();
  Center center_;
  Transformer *transform_;
};

}  // namespace s21

#endif  // FACADE_MODEL_H
