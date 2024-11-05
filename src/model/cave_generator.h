#ifndef MODEL_CAVE_GENEATOR_H_
#define MODEL_CAVE_GENEATOR_H_

#include <vector>

#define MAX_CAVE_SIZE 50
namespace s21 {

class CaveGenerator {
  struct Settings {
    int width = 0;
    int height = 0;
    int init_chance = 0;
    int born_limits = 0;
  };

 public:
  explicit CaveGenerator(int height, int width);
  ~CaveGenerator();

  void generate(int width, int height);

 private:
  void cleanCave();
  void generateFirstGeneration();

  int height_ = 0;
  int width_ = 0;
  Settings settings_;
  std::vector<std::vector<int>> cave_;
};
}  // namespace s21
#endif  // MODEL_CAVE_GENEATOR_H_