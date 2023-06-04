all:
	g++ --std=c++17 -Wno-deprecated -Wall -g -I./dependencies/include -L./dependencies/library ./dependencies/library/libglfw.3.3.dylib ./dependencies/library/glad.c ./dependencies/library/stb_image.c ./src/*.cpp ./*.cpp -o openGL -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation

clean:
	rm openGL