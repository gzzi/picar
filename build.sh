rm -R build
mkdir build
cd build

cmake ..
make -j $(nproc)
