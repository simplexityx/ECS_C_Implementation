CC := gcc
CFLAGS := -g -Wall -Wextra
LINKFLAGS := -lpthread -lSDL2_image -lSDL2_image `sdl2-config --cflags --libs`
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
		entities.o
		

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