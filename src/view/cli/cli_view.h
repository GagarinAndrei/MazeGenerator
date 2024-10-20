#ifndef VIEW_CLI_VIEW_H
#define VIEW_CLI_VIEW_H

#include "../../controller/controller.h"

namespace s21 {

class CliView {
 public:
  CliView(Controller &controller) : controller_(controller) {}
  ~CliView() = default;
  void printLabirinth();

 private:
  Controller &controller_;
};

}  // namespace s21
#endif  // VIEW_CLI_VIEW_H