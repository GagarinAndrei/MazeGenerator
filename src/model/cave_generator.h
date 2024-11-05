#ifndef MODEL_CAVE_GENEATOR_H_
#define MODEL_CAVE_GENEATOR_H_

#include <vector>

#define MAX_CAVE_SIZE 50
namespace s21 {

class CaveGenerator {
  struct Settings {
    int width = 0;
    int height = 0;
    double init_chance = 0;
    int born_limits = 0;
    int death_limits = 0;
  };

 public:
  explicit CaveGenerator(int height, int width);
  ~CaveGenerator() {};

  void generate(int width, int height);

  void setSettings(Settings settings) { settings_ = settings; }

  Settings &getSettings() { return settings_; }

  void printCave();

 private:
  bool trueOrFalseGenerator();
  void cleanCave();
  bool initChanceGenerator();
  int countLiveNeighbors(std::vector<std::vector<int>> cave, int x, int y);
  void generateFirstGeneration();
  void generateNextGeneration();
  bool isGenerationFinished();

  int height_ = 0;
  int width_ = 0;
  Settings settings_;
  std::vector<std::vector<int>> cave_;
  std::vector<std::vector<int>> prev_cave_;
};
}  // namespace s21
#endif  // MODEL_CAVE_GENEATOR_H_