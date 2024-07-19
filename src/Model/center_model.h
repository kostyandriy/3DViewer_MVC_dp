#ifndef CENTERMODEL_H
#define CENTERMODEL_H

#include <iostream>
#include <vector>

// #include "glwidget.h"

namespace s21 {
class Center {
 public:
  void center_model(std::vector<std::vector<double>> &data);
  void find_min_max_coords(std::vector<std::vector<double>> &data);
  double dmax();

 private:
  double min_x = 0, min_y = 0, min_z = 0, max_x = 0, max_y = 0, max_z = 0;
};
}  // namespace s21

#endif  // CENTERMODEL_H
