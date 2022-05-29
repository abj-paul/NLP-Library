#include "DefineNoisyChannel.h"
#include "ConfusionMatrix.h"

int main(){
  DefineNoisyChannel ncm;
  ncm.loadMatrices();
  ncm.printMatrices();

  abj::ConfusionMatrix::test_function();
  return 0;
}
