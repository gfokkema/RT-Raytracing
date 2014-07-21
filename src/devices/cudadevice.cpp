#include <devices/cudadevice.h>

CUDADevice::CUDADevice() {}

CUDADevice::~CUDADevice() {}

int CUDADevice::init() {
	return 0;
}

device_mem CUDADevice::malloc(size_t size, permission perm) {
	void* buff;
	cudaMalloc(&buff, size);
	return {(uintptr_t)buff, size};
}

void CUDADevice::read(device_mem mem, size_t size, void* data_read) {
	cudaMemcpy(data_read, (void*)mem._mem_pointer, size, cudaMemcpyDeviceToHost);
}

void CUDADevice::write(device_mem mem, size_t size, void* data_write) {
	cudaMemcpy((void*)mem._mem_pointer, data_write, size, cudaMemcpyHostToDevice);
}

int CUDADevice::enqueue_kernel_range(	kernel_key id, uint8_t num_args, void** arg_values,
										size_t* arg_sizes, uint8_t dim, size_t* work_size) {
	dim3 threads(8,8);
	dim3 blocks(arg_sizes[1] / threads.x, arg_sizes[1] / threads.y);
	switch (id) {
	case 0:
		cudaproduceray(blocks, threads, (camera&)arg_values, (float4*)arg_values[1]);
		break;
	case 1:
		cudatraceray(blocks, threads, (camera&)arg_values, (float4*)arg_values[1], (shape*)arg_values[2], (unsigned char*)arg_values[3]);
		break;
	}
}
