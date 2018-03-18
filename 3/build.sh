rm -rf build
mkdir build
cd build
cmake -D CMAKE_INSTALL_PREFIX=/home/barneygao/software/study ..
make VERBOSE=1
make test
make install
