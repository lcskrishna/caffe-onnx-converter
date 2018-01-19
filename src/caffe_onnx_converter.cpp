#include <iostream>
#include <sstream>
#include <iomanip>
#include <fcntl.h>
#include <fstream>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "caffe.pb.h"
#include "onnx.pb.h"

int loadCaffeModel(const char * fileName, int inputDim[4])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	caffe::NetParameter net_parameter;
	std::fstream input(fileName, std::ios::in | std::ios::binary);
	bool isSuccess = net_parameter.ParseFromIstream(&input);
	if(isSuccess) {
		std::cout << "INFO: caffemodel read successful" << std::endl;
		//TODO: need to parse caffemodel and create an onnx model.
	}
	else {
		std::cout << "ERROR: failed to read caffemodel" << std::endl;
		return -1;
	}

	return 0;
	
}

int main(int argc, char * argv[])
{
	const char * usage = "Usage: caffe_onnx_converter <net.caffemodel> <n c h w>";
	
	if(argc < 2 ) {
		printf("ERROR: %s\n", usage);
		return -1;
	}

	int inputDim[4] = {0, 0, 0, 0};

	const char * fileName = argv[1];
	
	if(argc > 2) inputDim[0] = atoi(argv[2]);
	if(argc > 3) inputDim[1] = atoi(argv[3]);
	if(argc > 4) inputDim[2] = atoi(argv[4]);
	if(argc > 5) inputDim[3] = atoi(argv[5]);

	if(!strstr(fileName, "caffemodel")) {
		std::cout << "ERROR: Unsupported file. Make sure to give a caffemodel input" << std::endl;
		return -1;
	}

	if(loadCaffeModel(fileName, inputDim) < 0) {
		return -1;
	}

	return 0;
}
