#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
class ITransformation {
 public:
  virtual void Transform(std::vector<std::vector<double>> &data,
                         double variable) const = 0;
};

class MoveX : public ITransformation {
 public:
  void Transform(std::vector<std::vector<double>> &data,
                 double variable) const override;
};

class MoveY : public ITransformation {
 public:
  void Transform(std::vector<std::vector<double>> &data,
                 double variable) const override;
};

class MoveZ : public ITransformation {
 public:
  void Transform(std::vector<std::vector<double>> &data,
                 double variable) const override;
};

class RotateX : public ITransformation {
 public:
  void Transform(std::vector<std::vector<double>> &data,
                 double variable) const override;
};

class RotateY : public ITransformation {
 public:
  void Transform(std::vector<std::vector<double>> &data,
                 double variable) const override;
};

class RotateZ : public ITransformation {
 public:
  void Transform(std::vector<std::vector<double>> &data,
                 double variable) const override;
};

class Scale : public ITransformation {
 public:
  void Transform(std::vector<std::vector<double>> &data,
                 double variable) const override;
};

class Transformer {
 public:
  Transformer(ITransformation *transform) : transform_(transform) {}
  void Transform(std::vector<std::vector<double>> &data, double variable);
  void SetStrategy(ITransformation *strategy);

 private:
  ITransformation *transform_;
};

}  // namespace s21

#endif  // TRANSFORM_H
