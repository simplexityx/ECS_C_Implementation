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
INC_PATH := -I ./includes

TEST_SRC := ./src/tests/

COMPONENTS_SRC := ./src/components/

UTILITY_SRC := ./src/utils/

TARGET := ECS

TEST_TARGET := ECS_TEST




ECS_OBJS := ecs.o


MAIN_OBJ := main.o

TEST_OBJS := testRun.o


UTILITY_OBJS := hashmap.o \
				vector2D.o \
				observable.o 



COMPONENT_OBJS := 	particleComponent.o \
				  	spriteComponent.o \
					colliderComponent.o \
					keyboardComponent.o \
					tileComponent.o \
					statComponent.o \
					textComponent.o \
					aiComponent.o 

OBJ1 := transformComponent.o \
		entities.o \
		manager.o \
		renderer.o \
		textureManager.o \
		assetManager.o \
		gridMap.o \
		TerrainManager.o 

TESTOBJ := $(patsubst %, $(OBJ_PATH)%, $(TEST_OBJS))

UTILOBJ := $(patsubst %, $(OBJ_PATH)%, $(UTILITY_OBJS))

COMPOBJ := $(patsubst %, $(OBJ_PATH)%, $(COMPONENT_OBJS))

OBJ := $(patsubst %,$(OBJ_PATH)%, $(OBJ1))

MAINOBJ := $(patsubst %,$(OBJ_PATH)%, $(MAIN_OBJ))

$(OBJ_PATH)%.o: $(UTILITY_SRC)%.c  
				@echo [CC] $<
				@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)

#build components.o
$(OBJ_PATH)%.o: $(COMPONENTS_SRC)%.c  
				@echo [CC] $<
				@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)

#build .o
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@echo [CC] $<
				@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)

$(OBJ_PATH)%.o: $(TEST_SRC)%.c
				@echo [CC] $<
				@$(CC) $(CFLAGS) -o $@ -c $< $(INC_PATH)




#$(TEST_TARGET): $(TESTOBJ) $(COMPOBJ) $(UTILOBJ) $(OBJ)
#			@$(CC) -o $@ $^ $(LINKFLAGS)

#build final binary
$(TARGET):	 $(MAINOBJ) $(OBJ) $(COMPOBJ) $(UTILOBJ)
			@$(CC) -o $@ $^ $(LINKFLAGS)

#clean all files
clean:
		@echo "[Cleaning]"
		-rm $(OBJ_PATH)*o
		@$(RM) -rfv $(TEST_TARGET)
		@$(RM) -rfv $(TARGET)