#include "transform.h"

namespace s21 {
void MoveX::Transform(std::vector<std::vector<double>> &data,
                      double variable) const {
  int size = data.size();
  for (auto i = 0; i < size; i++) {
    data[i][0] += variable;
  }
}

void MoveY::Transform(std::vector<std::vector<double>> &data,
                      double variable) const {
  int size = data.size();
  for (auto i = 0; i < size; i++) {
    data[i][1] += variable;
  }
}

void MoveZ::Transform(std::vector<std::vector<double>> &data,
                      double variable) const {
  int size = data.size();
  for (auto i = 0; i < size; i++) {
    data[i][2] += variable;
  }
}

void RotateX::Transform(std::vector<std::vector<double>> &data,
                        double variable) const {
  int size = data.size();
  variable *= M_PI / 180;
  for (auto i = 0; i < size; i++) {
    double temp_y = data[i][1];
    double temp_z = data[i][2];
    data[i][1] = cos(variable) * temp_y - sin(variable) * temp_z;
    data[i][2] = sin(variable) * temp_y + cos(variable) * temp_z;
  }
}

void RotateY::Transform(std::vector<std::vector<double>> &data,
                        double variable) const {
  int size = data.size();
  variable *= M_PI / 180;
  for (auto i = 0; i < size; i++) {
    double temp_x = data[i][0];
    double temp_z = data[i][2];
    data[i][0] = cos(variable) * temp_x + sin(variable) * temp_z;
    data[i][2] = -sin(variable) * temp_x + cos(variable) * temp_z;
  }
}

void RotateZ::Transform(std::vector<std::vector<double>> &data,
                        double variable) const {
  int size = data.size();
  variable *= M_PI / 180;
  for (auto i = 0; i < size; i++) {
    double temp_x = data[i][0];
    double temp_y = data[i][1];
    data[i][0] = cos(variable) * temp_x - sin(variable) * temp_y;
    data[i][1] = sin(variable) * temp_x + cos(variable) * temp_y;
  }
}

void Scale::Transform(std::vector<std::vector<double>> &data,
                      double variable) const {
  int size = data.size();
  for (auto i = 0; i < size; i++) {
    data[i][0] *= variable;
    data[i][1] *= variable;
    data[i][2] *= variable;
  }
}

void Transformer::SetStrategy(ITransformation *strategy) {
  transform_ = strategy;
}

void Transformer::Transform(std::vector<std::vector<double>> &data,
                            double variable) {
  if (transform_) {
    transform_->Transform(data, variable);
  } else {
    std::cout << "transform_ isn't set\n";
  }
}

}  // namespace s21
