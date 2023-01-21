cmake -S ./data/adk -B adk-build -DCMAKE_BUILD_TYPE=Release
cmake --build adk-build --config Release --parallel
.\adk-build\Release\adk.exe
.\adk-build\Release\datagen.exe