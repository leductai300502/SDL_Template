SOURCE = main.cpp game_define/base_object.cpp game_define/common.cpp game_define/Player_Object.cpp game_define/Ball_Object.cpp game_define/img_link.cpp game_define/game_status_machine.cpp game_define/Menu.cpp
all:
	g++ -I src/include -I header -L src/lib -o main $(SOURCE) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
