CC := gcc
CFLAGS := -g -Wall -Wextra
LINKFLAGS := -std=c99 -lpthread -lSDL2_image `sdl2-config --cflags --libs`
RM := rm
.PHONY: $(TARGET)
.PHONY: clean

MKDIR_P := mkdir -p

VPATH := ./src/ ./obj/ ./includes/


SRC_PATH := ./src/
OBJ_PATH := ./obj/
INC_PATH := -I ./includes


TARGET := ECS

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
		collisions.o
		

OBJ := $(patsubst %,$(OBJ_PATH)%, $(OBJ1))

#build .o
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@echo [CC] $<
				@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)

#build final binary
$(TARGET):	$(OBJ)
			@$(CC) -o $@ $^ $(LINKFLAGS)

#clean all files
clean:
		@echo "[Cleaning]"
		-rm $(OBJ_PATH)*o
		@$(RM) -rfv $(TARGET)