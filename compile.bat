cmake -S . -B adk-build -DCMAKE_BUILD_TYPE=Release
cmake --build adk-build --config Release --parallel
.\adk-build\Release\Test.exe