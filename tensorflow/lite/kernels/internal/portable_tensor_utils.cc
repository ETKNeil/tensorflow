/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef TENSORFLOW_LITE_KERNELS_INTERNAL_TENSOR_UTILS_H_
#define TENSORFLOW_LITE_KERNELS_INTERNAL_TENSOR_UTILS_H_

#include "tensorflow/lite/kernels/internal/portable_tensor_utils.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "third_party/eigen3/Eigen/Core"
#include "tensorflow/lite/c/builtin_op_data.h"

#if defined(_MSC_VER)
#define __restrict__ __restrict
#endif

namespace tflite {

// Not all backends support CpuBackendContext usage, so forward declare to avoid
// pulling in its implementation. Use of CpuBackendContext in method
// implementations is purely optional.
class CpuBackendContext;

namespace tensor_utils {

// Apply Rectified Linear to elements of a vector.
void ApplyReluToVector(const float* __restrict__ vector, int v_size,
                       float* __restrict__ result) {
  for (int v = 0; v < v_size; v++) {
    result[v] = std::max(0.0f, vector[v]);
  }
}

// Apply Rectified Linear 1 (cap to [-1;1]) to elements of a vector
void ApplyRelu1ToVector(const float* __restrict__ vector, int v_size,
                        float* __restrict__ result) {
  for (int v = 0; v < v_size; v++) {
    result[v] = std::max(-1.0f, std::min(vector[v], 1.0f));
  }
}

// Apply Rectified Linear 6 (cap to [0;6]) to elements of a vector
void ApplyRelu6ToVector(const float* __restrict__ vector, int v_size,
                        float* __restrict__ result) {
  for (int v = 0; v < v_size; v++) {
    result[v] = std::max(0.0f, std::min(vector[v], 6.0f));
  }
}

// Apply signbit to elements of a vector
void ApplySignbitToVector(const float* __restrict__ vector, int v_size,
                          float* __restrict__ result) {
  for (int v = 0; v < v_size; v++) {
    result[v] = std::signbit(vector[v]);
  }
}

}  // namespace tensor_utils
}  // namespace tflite

#endif  // TENSORFLOW_LITE_KERNELS_INTERNAL_TENSOR_UTILS_H_
