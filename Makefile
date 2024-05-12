CPP=g++
CPPFLAGS=-g -Wall -O0 -m64 -D_DEBUG
INCS=-Isrc -I$(SDL2)\include -I$(SDL2_image)\include
LDFLAGS=-L$(SDL2)\lib\x64 -L$(SDL2_image)\lib\x64 -lSDL2 -lSDL2main -l:SDL2.dll -lSDL2_image -l:SDL2_image.dll

SRC=src
OBJ=obj
AST=assets
SRCS=$(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/**/*.cpp) $(wildcard $(SRC)/**/**/*.cpp)
ASSET=$(wildcard $(AST)/*.png)

BIN=.\bin
ASSETS=$(foreach f, $(ASSET), $(BIN)\$f)

DEB_BIN=$(BIN)\debug
DEB_ASSETS=$(foreach f, $(ASSET), $(DEB_BIN)\$f)

REL_BIN=$(BIN)\release
REL_ASSETS=$(foreach f, $(ASSET), $(REL_BIN)\$f)

TARGET=volpesnocti.exe

all: ASSETS=$(foreach f, $(ASSET), $(BIN)\$f)
all: clean copy $(ASSETS) $(BIN)\$(TARGET)

debug: CPPFLAGS=-g -Wall -O0 -m64 -D_DEBUG
debug: deb_copy $(DEB_ASSETS) $(DEB_BIN)\$(TARGET)

release: CPPFLAGS=-Wall -O2 -m64 -D_NDEBUG
release: rel_copy $(REL_ASSETS) $(REL_BIN)\$(TARGET)

$(BIN)\$(TARGET): $(ASSETS)
	$(CPP) $(CPPFLAGS) $(SRCS) -o $(BIN)\$(TARGET) $(INCS) $(LDFLAGS)

$(DEB_BIN)\$(TARGET): $(DEB_ASSETS)
	$(CPP) $(CPPFLAGS) $(SRCS) -o $(DEB_BIN)\$(TARGET) $(INCS) $(LDFLAGS)

$(REL_BIN)\$(TARGET): $(REL_ASSETS)
	$(CPP) $(CPPFLAGS) $(SRCS) -o $(REL_BIN)\$(TARGET) $(INCS) $(LDFLAGS)

copy:
	mkdir -p $(BIN)
	mkdir -p $(BIN)\assets
	cp -f $(SDL2)\lib\x64\SDL2.dll $(BIN)
	cp -f $(SDL2_image)\lib\x64\SDL2_image.dll $(BIN)

deb_copy:
	mkdir -p $(BIN)
	mkdir -p $(DEB_BIN)
	mkdir -p $(DEB_BIN)\assets
	cp -f $(SDL2)\lib\x64\SDL2.dll $(DEB_BIN)
	cp -f $(SDL2_image)\lib\x64\SDL2_image.dll $(DEB_BIN)

rel_copy:
	mkdir -p $(BIN)
	mkdir -p $(REL_BIN)
	mkdir -p $(REL_BIN)\assets
	cp -f $(SDL2)\lib\x64\SDL2.dll $(REL_BIN)
	cp -f $(SDL2_image)\lib\x64\SDL2_image.dll $(REL_BIN)

$(ASSETS): $(ASSET) copy
	cp -f $< $@

$(REL_ASSETS): $(ASSET) rel_copy
	cp -f $< $@

$(DEB_ASSETS): $(ASSET) deb_copy
	cp -f $< $@

clean:
	$(RM) -r bin