TARGET=bin

mkdir ${TARGET}
cd ${TARGET}
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 ../src/
