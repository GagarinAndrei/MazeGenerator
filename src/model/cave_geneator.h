#ifndef MODEL_CAVE_GENEATOR_H_
#define MODEL_CAVE_GENEATOR_H_

#include <vector>
namespace s21 {

class Cave_Generator {
 public:
  Cave_Generator();
  ~Cave_Generator();

  void generate(int width, int height);

 private:
  int width_;
  int height_;
  std::vector<std::vector<int>> map_;
};
}  // namespace s21
#endif  // MODEL_CAVE_GENEATOR_H_