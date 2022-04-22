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

project1_case%:
	@mkdir -p project1/outputs
	@$(TARGET) project1/inputs/circuit_netlist_case$(patsubst project1_case%,%,$@).txt project1/outputs/output_mnaMatrix_case$(patsubst project1_case%,%,$@).txt project1/outputs/output_xVector_case$(patsubst project1_case%,%,$@).txt project1/outputs/output_rhs_case$(patsubst project1_case%,%,$@).txt
	@diff project1/golden/output_mnaMatrix_case$(patsubst project1_case%,%,$@).txt project1/outputs/output_mnaMatrix_case$(patsubst project1_case%,%,$@).txt
	@diff project1/golden/output_xVector_case$(patsubst project1_case%,%,$@).txt project1/outputs/output_xVector_case$(patsubst project1_case%,%,$@).txt 
	@diff project1/golden/output_rhs_case$(patsubst project1_case%,%,$@).txt project1/outputs/output_rhs_case$(patsubst project1_case%,%,$@).txt


leak_case%:
	@mkdir -p outputs
	@valgrind $(TARGET) project1/inputs/circuit_netlist_case$(patsubst leak_case%,%,$@).txt project1/outputs/output_mnaMatrix_$(patsubst case%,%,$@).txt project1/outputs/output_xVector_$(patsubst case%,%,$@).txt project1/outputs/output_rhs_$(patsubst case%,%,$@).txt

project1_zip:
	@make clean
	@make
	@rm -f project1/0710764.zip
	@zip -r project1/0710764.zip src bin/Project1 makefile project1/README.md