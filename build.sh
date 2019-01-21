
git submodule update --init

rm -R build
mkdir build
cd build

cmake ..
make -j $(nproc)
