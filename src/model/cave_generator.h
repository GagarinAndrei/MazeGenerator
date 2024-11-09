#ifndef MODEL_CAVE_GENEATOR_H_
#define MODEL_CAVE_GENEATOR_H_

#include <string>
#include <vector>

#define MAX_CAVE_SIZE 50
namespace s21 {

class CaveGenerator {
 public:
  CaveGenerator() {};
  ~CaveGenerator() {};
  struct Settings {
    int width = 1;
    int height = 1;
    float init_chance = 0;
    int born_limits = 0;
    int death_limits = 0;
  };

  void generate();
  void saveCaveInFile(const std::string &filename);
  void loadCaveFromFile(const std::string &filename);

  void setSettings(Settings settings);
  inline void setHeight(int height) { this->settings_.height = height; }
  inline void setWidth(int width) { this->settings_.width = width; }

  inline Settings &getSettings() { return this->settings_; }
  inline std::vector<std::vector<int>> &getCave() { return this->cave_; }
  inline int getHeight() { return this->settings_.height; }
  inline int getWidth() { return this->settings_.width; }
  void resizeCave(int height, int width);

  // TODO Deelete before finish project
  void printCave();

 private:
  bool trueOrFalseGenerator();
  int countLiveNeighbors(std::vector<std::vector<int>> cave, int x, int y);
  void generateFirstGeneration();
  void generateNextGeneration();
  bool isGenerationFinished();

  Settings settings_;
  std::vector<std::vector<int>> cave_;
  std::vector<std::vector<int>> prev_cave_;
};
}  // namespace s21
#endif  // MODEL_CAVE_GENEATOR_H_