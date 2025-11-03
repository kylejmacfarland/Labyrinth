COMPONENT = component/componentmap.cpp component/component.cpp component/monsterai.cpp
ENTITY = entity/entity.cpp entity/entitygen.cpp
FLOOR = floor/floor.cpp floor/floorgen.cpp
MENU = menu/inventorymenu.cpp
MVC = mvc/view.cpp mvc/model.cpp mvc/controller.cpp
COMMAND = command/command.cpp command/move.cpp command/pickup.cpp command/drop.cpp command/monsteract.cpp
SRCS = game.cpp util.cpp $(COMPONENT) $(ENTITY) $(FLOOR) $(MENU) $(MVC) $(COMMAND)
OBJ_DIR = ../build/obj
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
CC = g++
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lSDL2main -lSDL2
OUTPUTDIR = ../build/bin
TARGET = $(OUTPUTDIR)/labyrinth

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

$(TARGET): $(OBJS) $(OUTPUTDIR)
	$(CC) $(OBJS) -o $(TARGET) $(LINKER_FLAGS)\

$(OUTPUTDIR):
	@mkdir -p $(OUTPUTDIR)