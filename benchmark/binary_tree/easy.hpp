#include <binary_tree.h>
#include <easyDAG.hpp>

template <int N, class L, class R, typename std ::enable_if<(N > 0)>::type *>
auto make_tree(L left, R right) {
  return make_tree<N - 1>(make_task(math ::Add_lambda, left, right),
                          make_task(math ::Add_lambda, left, right));
}

template <int N, class L, class R, typename std ::enable_if<N <= 0>::type *>
auto make_tree(L left, R right) {
  return make_task(math ::Add_lambda, left, right);
}

template <int num_layers> void binary_tree_task() {
  std ::size_t one = 1;
  auto var_left = InputVariable(
      one); // it must be a step otherwise a inputvariable-task is not valuable
  auto var_right = InputVariable(
      one); // it must be a step otherwise a inputvariable-task is not valuable

  auto tree = make_tree<num_layers - 1>(var_left, var_right);
  tree.eval();

  // in release the asserts are turned off
  if (tree() != (1 << num_layers)) {
    std ::cerr << "Error easyDAG: " << tree() << " vs " << (1 << num_layers)
               << std ::endl;
    std ::exit(1);
  }
}
