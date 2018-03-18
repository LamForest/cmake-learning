rm -rf build
mkdir build
cd build
cmake -D USE_MYMATH=ON ..
make VERBOSE=1
./hello 4 5
#cd ..
#./hello
