#include "path_finder.h"

#include <queue>
#include <unordered_map>
#include <valarray>
#include <vector>

#include "model.h"

namespace s21 {

// bool PathFinder::isCollision(const Maze::Cell &current,
//                              const Maze::Cell &next) {
//   bool is_collision = false;
//   if (current.y > next.y) { // шаг вниз
//     if (current.b_wall == true) {
//       is_collision = true;
//     }
//   } else if (current.y < next.y) { // шаг вверх
//     if (next.b_wall == true) {
//       is_collision = true;
//     }
//   } else if (current.x > next.x) { // шаг вправо
//     if (current.b_wall == true) {
//       is_collision = true;
//     }
//   } else if (current.x < next.x) { // шаг влево
//     if (next.b_wall == true) {
//       is_collision = true;
//     }
//   }
//   return is_collision;
// }
}  // namespace s21
