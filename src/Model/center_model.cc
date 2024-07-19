#include "center_model.h"

namespace s21 {
void Center::center_model(std::vector<std::vector<double>> &data) {
  // double min_x, max_x, min_y, max_y, min_z, max_z;
  find_min_max_coords(data);

  double center_x = min_x + (max_x - min_x) / 2;
  double center_y = min_y + (max_y - min_y) / 2;
  double center_z = min_z + (max_z - min_z) / 2;

  unsigned int size = (unsigned int)data.size();
  // for (unsigned int i = 1; i < size; ++i) {
  //   file_data->matrix_3d.matrix[i][0] -= center_x;
  //   file_data->matrix_3d.matrix[i][1] -= center_y;
  //   file_data->matrix_3d.matrix[i][2] -= center_z;
  // }
  for (unsigned int i = 0; i < size; ++i) {
    data[i][0] -= center_x;
    data[i][1] -= center_y;
    data[i][2] -= center_z;
  }

  double max_diametr = dmax();
  double scale = 1.6 / max_diametr;

  for (unsigned int i = 0; i < size; ++i) {
    data[i][0] *= scale;
    data[i][1] *= scale;
    data[i][2] *= scale;
  }

  // return scale;

  // Заскейлить модельку надо будет
  // scale_model(&file_data->matrix_3d, scale);
}

void Center::find_min_max_coords(std::vector<std::vector<double>> &data) {
  min_x = data[0][0];
  max_x = data[0][0];
  min_y = data[0][1];
  max_y = data[0][1];
  min_z = data[0][2];
  max_z = data[0][2];

  unsigned int size = (unsigned int)data.size();
  for (unsigned int i = 0; i < size; ++i) {
    double x = data[i][0];
    double y = data[i][1];
    double z = data[i][2];

    min_x = (x < min_x) ? x : min_x;
    min_y = (y < min_y) ? y : min_y;
    min_z = (z < min_z) ? z : min_z;

    max_x = (x > max_x) ? x : max_x;
    max_y = (y > max_y) ? y : max_y;
    max_z = (z > max_z) ? z : max_z;
  }
}

double Center::dmax() {
  double dmax = 0, dx = 0, dy = 0, dz = 0;
  dx = max_x - min_x;
  dy = max_y - min_y;
  dz = max_z - min_z;
  dmax = dx;
  if (dy > dmax) dmax = dy;
  if (dz > dmax) dmax = dz;
  return dmax;
}
}  // namespace s21