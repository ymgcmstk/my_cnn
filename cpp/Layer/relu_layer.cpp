#include <algorithm>

class ReLULayer : public BaseLayer {
public:
  void initialize() {}
  bool forward () {
    if (next_layer == NULL) return false;
    data = MatrixXf::Zero(prev_layer->data.rows(), prev_layer->data.cols());
    data = prev_layer->data.array().max(data.array());
    return true;
  }
  bool backward () {
    if (prev_layer == NULL) return false;
    prev_layer->influence =
      (prev_layer->data.array()>0.0).cast<float>().array() * influence.array();
    return true;
  }
};
