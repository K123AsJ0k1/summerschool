#include <cstdio>
#include <hip/hip_runtime.h>

// This file include macros for checking the API and kernel launch errors
#include "../../../error_checking.hpp"

__global__ void fill(float *arr, float a, size_t num_values) {
    // TODO: Fill the array 'arr' with the constant 'a'.
    // Assume the array size is 'num_values'
    // Consult earlier exercises where we launched kernels and the lecture
    // slides for help
}

int main() {
    static constexpr size_t num_values = 1000000;
    static constexpr size_t num_bytes = sizeof(float) * num_values;
    static constexpr float a = 3.4f;

    float *d_arr = nullptr;
    // TODO: Allocate memory on the GPU
    // - hipMalloc
    hipMalloc(&d_arr, num_bytes);

    // TODO: Define grid dimensions + launch the device kernel
    int threads = dim3(1024, 1, 1);
    int blocks = dim3(977, 1, 1);
    LAUNCH_KERNEL(fill, blocks, threads, 0, 0, d_arr, a, num_values);

    float *h_arr = static_cast<float *>(std::malloc(num_bytes));
    // TODO: Copy results back to CPU
    // - hipMemcpy
    hipMemcpy(d_arr, h_arr, num_bytes, hipMemcpyDefault);

    // TODO: Free device memory
    // - hipFree
    hipFree(d_arr)

    printf("Some values copied from the GPU: %f, %f, %f, %f\n", h_arr[0],
           h_arr[1], h_arr[num_values - 2], h_arr[num_values - 1]);

    float error = 0.0;
    static constexpr float tolerance = 1e-6f;
    for (size_t i = 0; i < num_values; i++) {
        const auto diff = abs(h_arr[i] - a);
        if (diff > tolerance) {
            error += diff;
        }
    }
    printf("total error: %f\n", error);
    printf("  reference: %f\n", a);
    printf("     result: %f at (42)\n", h_arr[42]);

    std::free(h_arr);

    HIP_ERRCHK(hipDeviceSynchronize());

    return 0;
}
