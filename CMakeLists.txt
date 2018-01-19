#MIT License

#Copyright (c) 2017 Chaitanya Sri Krishna Lolla
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

cmake_minimum_required (VERSION 2.8)
project(caffe-onnx-converter)

set(CMAKE_CXX_STANDARD 11)

find_package(Protobuf REQUIRED)

file(DOWNLOAD "https://raw.githubusercontent.com/onnx/onnx/master/onnx/onnx.proto" "${CMAKE_CURRENT_BINARY_DIR}/onnx.proto")
PROTOBUF_GENERATE_CPP(PROTO_SRCS_ONNX PROTO_HDRS_ONNX ${CMAKE_CURRENT_BINARY_DIR}/onnx.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
message("ONNX Proto found")

file(DOWNLOAD "https://raw.githubusercontent.com/BVLC/caffe/master/src/caffe/proto/caffe.proto" "${CMAKE_CURRENT_BINARY_DIR}/caffe.proto")
PROTOBUF_GENERATE_CPP(PROTO_SRCS_CAFFE PROTO_HDRS_CAFFE ${CMAKE_CURRENT_BINARY_DIR}/caffe.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
message("Caffe Proto found")

list(APPEND SOURCES
	src/caffe_onnx_converter.cpp
        ${PROTO_SRCS_CAFFE} ${PROTO_HDRS_CAFFE}
	${PROTO_SRCS_ONNX} ${PROTO_HDRS_ONNX}
    )

add_executable(caffe_onnx_converter ${SOURCES})
target_link_libraries(caffe_onnx_converter ${PROTOBUF_LIBRARIES})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
