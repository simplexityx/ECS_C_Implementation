CC := gcc
CFLAGS := -g
LINKFLAGS := -std=c99 -lpthread -lm -lSDL2_image -lSDL2_ttf `sdl2-config --cflags --libs` 
RM := rm
.PHONY: $(TARGET)
.PHONY: clean

MKDIR_P := mkdir -p

VPATH := ./src/ ./obj/ ./includes/ 

SRC_PATH := ./src/
OBJ_PATH := ./obj/
OBJ_COMP_PATH := ./obj/components/
INC_PATH := -I ./includes
SRC_COMP_PATH := ./src/components/

TARGET := ECS

OBJCOMP := charge.o


OBJ1 := main.o \
		entities.o \
		transformComponent.o \
		spriteComponent.o \
		colliderComponent.o \
		keyboardComponent.o \
		manager.o \
		renderer.o \
		textureManager.o \
		assetManager.o \
		gridMap.o \
		TerrainManager.o \
		hashmap.o \
		vector2D.o \
		tileComponent.o \
		statComponent.o \
		textComponent.o \
		aiComponent.o \
		observable.o \
		particleComponent.o
		
COMPOBJ := $(patsubst %, $(OBJ_COMP_PATH)%, $(OBJCOMP))

OBJ := $(patsubst %,$(OBJ_PATH)%, $(OBJ1))

$(OBJ_COMP_PATH)%.o: $(SRC_COM_PATH)%.c  
				@echo [CC] $<
				@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)
#build .o
$(OBJ_PATH)%.o: $(SRC_PATH)%.c  
				@echo [CC] $<
				@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)

#build final binary
$(TARGET):	$(OBJ) $(COMPOBJ)
			@$(CC) -o $@ $^ $(LINKFLAGS)

#clean all files
clean:
		@echo "[Cleaning]"
		-rm $(OBJ_PATH)*o
		-rm $(OBJ_COMP_PATH)*o
		@$(RM) -rfv $(TARGET)