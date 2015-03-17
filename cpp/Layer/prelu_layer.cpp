class PReLULayer : public BaseLayer {
public:
  PReLULayer () {
    layer_name = "PReLULayer";
  }
  float weight;
  void initialize() {
    weight = 0;
  }
  bool forward() {
    if (next_layer == NULL) return false;
    data = prev_layer->data * weight;
    data = prev_layer->data.array().max(data.array());
    debug();
    return true;
  }
  bool backward () {
    if (prev_layer == NULL) return false;
    transposed = influence.transpose();
    compared = (prev_layer->vectorize(true).array()<=0.0).cast<float>().array() *
      prev_layer->vectorize(true).array();
    prev_layer->influence =
      (prev_layer->data.array()>0.0).cast<float>().array() * influence.array() +
      (prev_layer->data.array()<=0.0).cast<float>().array() * influence.array() * weight;
    weight = weight - (transposed * compared)(0,0);
    debug();
    //print_weight ();
    return true;
  }
  void print_weight () {
    cout << weight << endl;
  }
private:
  MatrixXf transposed;
  MatrixXf compared;
};
