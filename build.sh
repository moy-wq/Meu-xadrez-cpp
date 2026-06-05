g++ main_test.cpp src/UI/*.cpp src/app/*.cpp src/core/*.cpp -o xadrez.o -I include -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./xadrez.o