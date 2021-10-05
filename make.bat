cmake -B build
cmake --build build --config Release
xcopy /y .\build\Release\ld49.exe .
xcopy /y .\SFML\bin\*.dll .
