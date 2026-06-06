
mkdir bin
g++ main.cpp src/UI/*.cpp src/app/*.cpp src/core/*.cpp -o bin/xadrez -I include -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./bin/xadrez