cmake -S . -B out/build -DCMAKE_BUILD_TYPE=Release
cmake --build out/build --config Release --parallel
cd out/build
ctest -C Release --rerun-failed --output-on-failure
cd ../..