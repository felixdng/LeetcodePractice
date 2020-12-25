TOP_DIR=$(shell pwd)

COMMON_DIR=src
MAIN_DIR=main
INC_DIR=inc

#comma:=:
#empty:=
#space:=$(empty) $(empty)
#vpath %.c $(subst $(space),$(comma),$(strip $(COMMON_DIR) $(MAIN_DIR)))

BIN_DIR=bin
OUTPUT_SUBDIR=$(BIN_DIR) $(COMMON_DIR) $(MAIN_DIR)
OUTPUT_DIR=output

INCS=$(wildcard $(INC_DIR)/*.h)
SRC_COMMON=$(foreach dir,$(COMMON_DIR),$(wildcard $(dir)/*.c))
OBJ_COMMON=$(addprefix $(OUTPUT_DIR)/,$(patsubst %.c,%.o,$(SRC_COMMON)))
#$(info "[SRC_COMMON] $(SRC_COMMON)")
#$(info "[OBJ_COMMON] $(OBJ_COMMON)")

SRC_MAIN=$(foreach dir,$(MAIN_DIR),$(wildcard $(dir)/*.c))
OBJ_MAIN=$(addprefix $(OUTPUT_DIR)/,$(patsubst %.c,%.o,$(SRC_MAIN)))
#$(info "[SRC_MAIN] $(SRC_MAIN)")
#$(info "[OBJ_MAIN] $(OBJ_MAIN)")

# To avoid "rm output/main/1-reverse.o output/src/listdemo.o"
#.PRECIOUS:$(OBJ_COMMON) $(OBJ_MAIN)
.SECONDAY:$(OBJ_COMMON) $(OBJ_MAIN)

TARGETS=$(patsubst %.o,%,$(notdir $(OBJ_MAIN)))
#$(info "[TARGETS] $(TARGETS)")

CC=gcc
CFLAGS=-Wall -Wno-error -I$(TOP_DIR)/$(INC_DIR)
ifeq ($(debug),)
CFLAGS+=-O2
else
CFLAGS+=-g -DDEBUG
endif
LDFLAGS=


all:dir_create $(TARGETS) echo_finish

#target rule
%:$(OUTPUT_DIR)/$(MAIN_DIR)/%.o $(OBJ_COMMON)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(OUTPUT_DIR)/$(BIN_DIR)/$@

$(OUTPUT_DIR)/%.o:%.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

dir_create:
	@mkdir -p $(TOP_DIR)/$(OUTPUT_DIR)
	@mkdir -p $(foreach dir, $(OUTPUT_SUBDIR), $(TOP_DIR)/$(OUTPUT_DIR)/$(dir))

echo_finish:
	@echo "#"
	@echo "# make successfully"
	@echo "#"

clean:
	@rm -rf $(OUTPUT_DIR)

.PHONY:all clean dir_create echo_finish
