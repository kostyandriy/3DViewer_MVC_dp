#include "parser.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace s21 {
ObjectParser *ObjectParser::instance_ = nullptr;

std::vector<std::vector<double>> ObjectParser::get_vertices() const {
  return vertices_;
}

unsigned ObjectParser::get_vertices_number() const {
  return number_of_vertices_;
}

unsigned ObjectParser::get_vertices_in_face_number() const {
  return number_of_vertices_in_face;
}

// std::vector<unsigned> ObjectParser::get_faces() const { return faces_; }

std::map<unsigned, std::vector<unsigned>> ObjectParser::get_faces() const {
  return faces_;
}

unsigned ObjectParser::get_faces_number() const { return number_of_faces_; }

ObjectParser *ObjectParser::get_instance() {
  if (!instance_) {
    instance_ = new ObjectParser();
  }
  return instance_;
}

Status ObjectParser::ParseObject(std::string file_name) {
  ClearData();
  Status status = Status::ok;
  std::ifstream fin(file_name);
  if (!fin.is_open()) {
    status = Status::error;
  }
  std::string line;
  unsigned vertex_count = 0, face_count = 0;
  while (std::getline(fin, line) && status == Status::ok) {
    if (line.front() == 'v' && line.at(1) == ' ') {
      status = ParseVertex(line);
      vertex_count++;
      number_of_vertices_ = vertex_count;
    } else if (line.front() == 'f') {
      // status = ParseFaces(line);
      face_count++;
      status = ParseFaces(line, face_count);
    }
  }
  fin.close();
  // number_of_vertices_ = vertex_count;
  number_of_faces_ = face_count;
  return status;
}

void ObjectParser::ClearData() {
  vertices_.clear();
  faces_.clear();
  number_of_vertices_ = 0;
  number_of_faces_ = 0;
  number_of_vertices_in_face = 0;
}

Status ObjectParser::ParseVertex(std::string line) {
  std::istringstream iss_validate(line.substr(2));
  std::istringstream iss(line.substr(2));
  double x, y, z;
  if (!(iss >> x >> y >> z)) {
    return Status::error;
  }
  char extra_character;
  if (iss.get(extra_character)) {
    // std::cout << "COORDS: " << extra_character << std::endl;
    // return Status::error;
  }
  vertices_.push_back({x, y, z});
  // std::cout << "COORDS: " << x << y << z << std::endl;
  return Status::ok;
}

// Status ObjectParser::ParseFaces(std::string line) {
//   std::istringstream iss(line.substr(2));
//   std::string faces;
//   unsigned vertex_index, vertices_in_face = 0;
//   while (iss >> faces) {
//     vertex_index = std::stoul(faces);
//     faces_.push_back(vertex_index);
//     vertices_in_face++;
//   }
//   number_of_vertices_in_face = vertices_in_face;
//   return Status::ok;
// }

Status ObjectParser::ParseFaces(std::string line, unsigned face_count) {
  std::istringstream iss(line.substr(2));
  std::string faces;
  std::vector<unsigned> vertices;
  unsigned vertex_index, vertices_in_face = 0;
  while (iss >> faces) {
    try {
      vertex_index = std::stoul(faces);
    } catch (const std::invalid_argument &ia) {
      // std::cout << ia.what() << std::endl;
      return Status::error;
    }
    if (vertex_index == 0 || vertex_index > get_vertices_number()) {
      // std::cout << "index = " << vertex_index
      //           << " vertices number = " << get_vertices_number() <<
      //           std::endl;
      return Status::error;
    }
    vertices.push_back(vertex_index);
    vertices_in_face++;
  }
  faces_.insert({face_count, {vertices}});
  number_of_vertices_in_face = vertices_in_face;
  return Status::ok;
}

}  // namespace s21
