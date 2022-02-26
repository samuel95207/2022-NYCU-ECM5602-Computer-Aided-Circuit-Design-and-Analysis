TARGET = ./bin/Project1

SRC_DIR = ./src
SRC_SUBDIR += devices .
INCLUDE_DIR += ./src
OBJ_DIR = ./bin/obj

CC = g++
C_FLAGS = -g -Wall -lstdc++ -std=c++11
LD = $(CC)
INCLUDES += -I$(INCLUDE_DIR)
LD_FLAFS += 
LD_LIBS =

ifeq ($(CC), g++)
	TYPE = cpp
else
	TYPE = c
endif

SRCS += ${foreach subdir, $(SRC_SUBDIR), ${wildcard $(SRC_DIR)/$(subdir)/*.$(TYPE)}}
OBJS += ${foreach src, $(notdir $(SRCS)), ${patsubst %.$(TYPE), $(OBJ_DIR)/%.o, $(src)}}

vpath %.$(TYPE) $(sort $(dir $(SRCS)))

all : $(TARGET)
	@echo "Builded target:" $^
	@echo "Done"

$(TARGET) : $(OBJS)
	@mkdir -p $(@D)
	@echo "Linking" $@ "from" $^ "..."
	$(LD) -o $@ $^ $(LD_FLAGS) $(LD_LIBS)
	@echo "Link finished"

$(OBJS) : $(OBJ_DIR)/%.o:%.$(TYPE)
	@mkdir -p $(@D)
	@echo "Compiling" $@ "from" $< "..."
	$(CC) -c -o $@ $< $(C_FLAGS) $(INCLUDES)
	@echo "Compile finished"

.PHONY : clean cleanobj
clean : cleanobj
	@echo "Remove all executable files and output files"
	rm -f $(TARGET)
	rm -f ./outputs/*
cleanobj :
	@echo "Remove object files"
	rm -rf $(OBJ_DIR)/*.o

case%:
	@mkdir -p outputs
	@$(TARGET) inputs/circuit_netlist_case$(patsubst case%,%,$@).txt outputs/output_mnaMatrix_$(patsubst case%,%,$@).txt outputs/output_xVector_$(patsubst case%,%,$@).txt outputs/output_rhs_$(patsubst case%,%,$@).txt
leak_case%:
	@mkdir -p outputs
	@valgrind $(TARGET) inputs/circuit_netlist_case$(patsubst leak_case%,%,$@).txt outputs/output_mnaMatrix_$(patsubst case%,%,$@).txt outputs/output_xVector_$(patsubst case%,%,$@).txt outputs/output_rhs_$(patsubst case%,%,$@).txt

zip:
	@make clean
	@make
	@rm -f 0710764.zip
	@zip -r 0710764.zip src bin/Project1 makefile README.md