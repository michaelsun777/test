git clone ...
git submodule init
git submodule update
#先编译QCefView
cd 3rd/QCefView
mkidr lib
#./generate-linux-x86_64.sh
mkdir build
cd build
cmake ..
make -j14
#移动库到相应该目录
cd output/Debug/
mv bin Debug
mv Debug ../../../lib/
cd 到工程根目录
修改CMakeLists.txt 中依敕库的路径
mkdir build
cd build
cmake ..
make -j14
#复制动态库到运行目录build中
cp -r 3rd/QCefView/lib/Debug/* ./
