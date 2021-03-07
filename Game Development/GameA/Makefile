target := bin/main.exe
objs := src/main.o src/utility/gameStateManager.o
deps := src/gameStateManager.h

CC := gcc
LIBSDL := -I"C:/libsdl/include" -L"C:/libsdl/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

all: $(target)

$(target) : $(objs)
	$(CC) $^ $(LIBSDL) -o $@

%.o : src/%.c $(deps)
	$(CC) -c $< 

clean:
	del $(objs) $(target)
