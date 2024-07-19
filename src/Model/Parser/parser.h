#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <string>
#include <vector>

namespace s21 {
enum class Status { ok, error };

class ObjectParser {
 public:
  static ObjectParser *get_instance();
  std::vector<std::vector<double>> get_vertices() const;
  unsigned get_vertices_number() const;
  unsigned get_vertices_in_face_number() const;
  std::map<unsigned, std::vector<unsigned>> get_faces() const;
  unsigned get_faces_number() const;
  Status ParseObject(std::string file_name);
  void ClearData();

 protected:
  ObjectParser(){};
  ~ObjectParser() { delete instance_; }

 private:
  static ObjectParser *instance_;
  std::vector<std::vector<double>> vertices_;
  std::map<unsigned, std::vector<unsigned>> faces_;
  unsigned number_of_vertices_;
  unsigned number_of_faces_;
  unsigned number_of_vertices_in_face;

  Status ParseVertex(std::string line);
  Status ParseFaces(std::string line);
  Status ParseFaces(std::string line, unsigned face_count);
};
}  // namespace s21

#endif  // PARSER_H
