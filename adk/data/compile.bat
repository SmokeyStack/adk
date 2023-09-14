cmake -S ./data/adk -B adk-build -DCMAKE_BUILD_TYPE=Release -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_TOOLCHAIN_FILE=%1
cmake --build adk-build --config Release --parallel
.\adk-build\Release\adk.exe