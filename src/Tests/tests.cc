#include <gtest/gtest.h>

#include "../Model/center_model.h"
#include "../Model/facade_model.h"

TEST(model_viewer, parsing_1) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  
  s21::Status status = model.ParseObject(file_path);
  EXPECT_EQ(s21::Status::ok, status);
}

TEST(model_viewer, parsing_2) {
  std::string file_path = "";
  s21::Facade model;
  
  s21::Status status = model.ParseObject(file_path);
  EXPECT_EQ(s21::Status::error, status);
}

TEST(model_viewer, parsing_3) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;
  
  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    EXPECT_DOUBLE_EQ(vertices_[0][0], 1.00000);
  }
}

TEST(model_viewer, parsing_4) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::map<unsigned, std::vector<unsigned>> faces_;
  
  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    faces_ = model.get_faces();
    EXPECT_DOUBLE_EQ(faces_[1][0], 2);
  }
}

TEST(model_viewer, parsing_5) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  unsigned amount_vertices = 0;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    amount_vertices = model.get_vertices_number();
    EXPECT_EQ(amount_vertices, 8);
  }
}

TEST(model_viewer, parsing_6) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  unsigned amount_faces = 0;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    amount_faces = model.get_faces_number();
    EXPECT_EQ(amount_faces, 12);
  }
}

TEST(model_viewer, parsing_7) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  unsigned amount_faces = 0;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    amount_faces = model.get_vertices_in_face_number();
    EXPECT_EQ(amount_faces, 3);
  }
}

TEST(model_viewer, transform_move_1) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, 10, new s21::MoveX());

    EXPECT_DOUBLE_EQ(vertices_[0][0], 11);
  }
}

TEST(model_viewer, transform_move_2) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, -10, new s21::MoveX());

    EXPECT_DOUBLE_EQ(vertices_[0][0], -9);
  }
}

TEST(model_viewer, transform_move_3) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, 20.02, new s21::MoveY());

    EXPECT_DOUBLE_EQ(vertices_[2][1], 19.02);
  }
}

TEST(model_viewer, transform_move_4) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, -20.02, new s21::MoveY());

    EXPECT_DOUBLE_EQ(vertices_[2][1], -21.02);
  }
}

TEST(model_viewer, transform_move_5) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, 1000.321, new s21::MoveZ());

    EXPECT_DOUBLE_EQ(vertices_[4][2], 999.321001);
  }
}

TEST(model_viewer, transform_move_6) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, -1000.123, new s21::MoveZ());

    EXPECT_DOUBLE_EQ(vertices_[4][2], -1001.122999);
  }
}

TEST(model_viewer, transform_rotate_1) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, 10, new s21::RotateX());

    ASSERT_NEAR(vertices_[0][0], 1, 1e-7);
    ASSERT_NEAR(vertices_[0][1], -0.81115957, 1e-7);
    ASSERT_NEAR(vertices_[0][2], -1.1584559, 1e-7);
  }
}

TEST(model_viewer, transform_rotate_2) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, -2, new s21::RotateX());

    ASSERT_NEAR(vertices_[2][0], -1, 1e-7);
    ASSERT_NEAR(vertices_[2][1], -0.9644913, 1e-7);
    ASSERT_NEAR(vertices_[2][2], 1.03429032, 1e-7);
  }
}

TEST(model_viewer, transform_rotate_3) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, 20.02, new s21::RotateY());

    ASSERT_NEAR(vertices_[2][0], -0.597225, 1e-7);
    ASSERT_NEAR(vertices_[2][1], -1, 1e-7);
    ASSERT_NEAR(vertices_[2][2], 1.2819213, 1e-7);
  }
}

TEST(model_viewer, transform_rotate_4) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, -20.02, new s21::RotateY());

    ASSERT_NEAR(vertices_[4][0], 1.2819209, 1e-7);
    ASSERT_NEAR(vertices_[4][1], 1, 1e-7);
    ASSERT_NEAR(vertices_[4][2], -0.597224, 1e-7);
  }
}

TEST(model_viewer, transform_rotate_5) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, 1000.321, new s21::RotateZ());

    ASSERT_NEAR(vertices_[4][0], 1.1629822, 1e-7);
    ASSERT_NEAR(vertices_[4][1], -0.8046566, 1e-7);
    ASSERT_NEAR(vertices_[4][2], -0.9999989, 1e-7);
  }
}

TEST(model_viewer, transform_rotate_6) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, -1000.123, new s21::RotateZ());

    ASSERT_NEAR(vertices_[6][0], -1.1601946, 1e-7);
    ASSERT_NEAR(vertices_[4][1], 1.1601946, 1e-7);
    ASSERT_NEAR(vertices_[4][2], -0.9999989, 1e-7);
  }
}

TEST(model_viewer, transform_scale_1) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, 10.321, new s21::Scale());

    ASSERT_NEAR(vertices_[4][0], 10.321, 1e-7);
    ASSERT_NEAR(vertices_[4][1], 10.321, 1e-7);
    ASSERT_NEAR(vertices_[4][2], -10.3209896, 1e-7);
  }
}

TEST(model_viewer, transform_scale_2) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, -1000.123, new s21::Scale());

    ASSERT_NEAR(vertices_[6][0], 1000.123, 1e-7);
    ASSERT_NEAR(vertices_[6][1], -1000.123, 1e-7);
    ASSERT_NEAR(vertices_[6][2], -1000.123, 1e-7);
  }
}

TEST(model_viewer, transform_center_1) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, -1000.123, new s21::Scale());
    model.CenterFunc(vertices_);

    ASSERT_NEAR(vertices_[4][0], -0.7999996, 1e-7);
    ASSERT_NEAR(vertices_[4][1], -0.7999996, 1e-7);
    ASSERT_NEAR(vertices_[4][2], 0.7999992, 1e-7);
  }
}

TEST(model_viewer, transform_center_2) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.CenterFunc(vertices_);

    ASSERT_NEAR(vertices_[2][0], -0.7999996, 1e-7);
    ASSERT_NEAR(vertices_[2][1], -0.7999996, 1e-7);
    ASSERT_NEAR(vertices_[2][2], 0.7999992, 1e-7);
  }
}

TEST(model_viewer, transform_center_3) {
  std::string file_path = "../Objects/cube.obj";
  s21::Facade model;
  std::vector<std::vector<double>> vertices_;

  s21::Status status = model.ParseObject(file_path);
  if (status != s21::Status::error) {
    vertices_ = model.get_vertices();
    model.Transform(vertices_, 10, new s21::MoveX());
    model.CenterFunc(vertices_);

    ASSERT_NEAR(vertices_[1][0], 0.7999996, 1e-7);
    ASSERT_NEAR(vertices_[1][1], -0.7999996, 1e-7);
    ASSERT_NEAR(vertices_[1][2], 0.7999992, 1e-7);

    // EXPECT_DOUBLE_EQ(vertices_[1][0], 1.1629822);
    // EXPECT_DOUBLE_EQ(vertices_[1][1], -0.8046566);
    // EXPECT_DOUBLE_EQ(vertices_[1][2], -0.9999989);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
