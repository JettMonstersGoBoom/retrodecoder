CFLAGS = -Itigr -Idecoder
ifeq ($(OS),Windows_NT)
	LDFLAGS = -s -lopengl32 -lgdi32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS = -framework OpenGL -framework Cocoa
	else ifeq ($(UNAME_S),Linux)
		LDFLAGS = -s -lGLU -lGL -lX11
	endif
endif

view : viewer.c tigr/tigr.c decoder/decoder.c
	gcc $^ -Os -o $@ $(CFLAGS) $(LDFLAGS)

