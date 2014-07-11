#include <fstream>
#include <iostream>
#include <sstream>

#include "opencl.h"

OpenCL::OpenCL() {}

OpenCL::~OpenCL() {}

int OpenCL::init() {
	cl_int err;
	std::vector<cl::Platform> platforms;

	err = cl::Platform::get(&platforms);
	if (err != CL_SUCCESS) return err;

	float max_ver;
	for (int i = 0; i < platforms.size(); i++) {
		std::vector<cl::Device> devices;
		err = platforms[i].getDevices(CL_DEVICE_TYPE_ALL, &devices);
		if (err != CL_SUCCESS) continue;

		std::string version;
		err = platforms[i].getInfo(CL_PLATFORM_VERSION, &version);
		if (err != CL_SUCCESS) continue;

		float ver = atof(version.substr(7,3).c_str());
		if (ver > max_ver && devices.size() > 0) {
			max_ver = ver;
			device = devices[0];
		}
	}

	std::string platversion, devicename;
	err = device.getInfo(CL_DEVICE_VERSION, &platversion);
	if (err != CL_SUCCESS) return err;
	err = device.getInfo(CL_DEVICE_NAME, &devicename);
	if (err != CL_SUCCESS) return err;

	std::cout << "Selected platform:\t" << platversion << std::endl;
	std::cout << "Selected device:\t" << devicename << std::endl;

	context = cl::Context(device, 0, 0, 0, &err);
	if (err != CL_SUCCESS) return err;

	queue = cl::CommandQueue(context, device, 0, &err);
	if (err != CL_SUCCESS) return err;

	return CL_SUCCESS;
}

int OpenCL::load(std::string kernel_path, cl::Kernel& kernel) {
	std::ifstream file(kernel_path);
	std::stringstream buffer;

	buffer << file.rdbuf();
	const char* txt_source = buffer.str().c_str();

	cl::Program::Sources source(1, std::make_pair(txt_source, strlen(txt_source)));
	cl::Program program(context, source);

	cl_int err;
	std::vector<cl::Device> devices(1, device);
	err = program.build(devices, 0, 0, 0);
	if (err != CL_SUCCESS) return err;

	kernel = cl::Kernel(program, kernel_path.c_str(), &err);
	return err;
}
