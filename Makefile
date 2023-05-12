
#    This file is a template for gnu make.
#    Try it by editing the variables below.
#
#    by github.com/luizfelmach
#    2023


# Variables


PROJECT    =     sparse_matrix
TARGETS    =     scripts/gen_matrix.c
FILES      =     ./*.c
IMPORTS    =     matrix
LINKER     =     m

# Folders

BUILD = .build
BUILD_L = $(BUILD)/lib
BUILD_I = $(BUILD)/include
BUILD_O = $(BUILD)/objs
BUILD_T = $(BUILD)/tests
BUILD_B = $(BUILD)/bin


# Misc

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))


# Files


ALL_IMPORTS = $(foreach IMPORT,$(IMPORTS), $(wildcard $(IMPORT)))
ALL_TARGETS = $(foreach TARGET,$(TARGETS), $(wildcard $(TARGET)))


FILES_TEMP = $(filter-out $(ALL_TARGETS), $(wildcard $(FILES)))
FILES_C = $(foreach IMPORT, $(ALL_IMPORTS), $(foreach S, $(call rwildcard, $(IMPORT), *.c), $(if $(findstring /tests/, $S), ,$S)))
FILES_C += $(FILES_TEMP)
HEADERS_H = $(foreach IMPORT, $(ALL_IMPORTS), $(foreach S, $(call rwildcard, $(IMPORT), *.h), $(if $(findstring /tests/, $S), ,$S)))
TESTS_C = $(foreach IMPORT, $(ALL_IMPORTS), $(foreach S, $(call rwildcard, $(IMPORT), *.c), $(if $(findstring /tests/, $S), $S)))


# Rules and targets

OBJECTS = $(addprefix $(BUILD_O)/, $(subst .c,.o, $(FILES_C)))
INCLUDES = $(addprefix -I, $(ALL_IMPORTS))
HEADERS = $(notdir $(HEADERS_H))

# Auxiliary

LIBRARY_NAME = $(addsuffix .a, $(addprefix lib, $(PROJECT)))
HEADER_NAME = $(addsuffix .h, $(PROJECT))
LIBRARY = $(addprefix $(BUILD_L)/, $(LIBRARY_NAME))
HEADER = $(addprefix $(BUILD_I)/, $(HEADER_NAME))
TESTS = $(addprefix $(BUILD_T)/, $(subst .c,, $(TESTS_C)))
EXECUTABLES = $(addprefix $(BUILD_B)/, $(subst .c,, $(ALL_TARGETS)))


# Compiler

CC = gcc
AR = ar
LL = $(addprefix -l, $(LINKER))
CC_FLAGS += -Wall
DEBUG_FLAGS += -g -fsanitize=address -fsanitize=undefined -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize-recover=all -fstack-protector-all -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC

ifeq ($(DEBUG),true)
CC_FLAGS += $(DEBUG_FLAGS)
$(info debug mode is active)
endif

.PHONY: all
all: $(LIBRARY) $(HEADER) $(TESTS) $(EXECUTABLES)

# Executables

$(BUILD_B)/%: %.c $(LIBRARY) $(HEADER)
	$(eval FOLDER = $(addprefix $(BUILD_B)/, $(dir $<)))
	$(eval OUT = $(addprefix $(BUILD_B)/, $(subst .c,,$<)))
	@mkdir -p $(FOLDER)
	@echo "linking with $(notdir $(OUT))"
	@$(CC) $(LL) $(CC_FLAGS) -o $(OUT) -L$(BUILD_L) -I$(BUILD_I)/ $< -l$(PROJECT)
	@cp $(OUT) .

# Library

$(BUILD_L)/$(LIBRARY_NAME): $(OBJECTS)
	@mkdir -p $(BUILD_L)
	@$(AR) -crs $(BUILD_L)/$(LIBRARY_NAME) $^
	@echo "finished $(LIBRARY_NAME)"

# Objects

$(BUILD_O)/%.o: %.c %.h
	$(eval FOLDER = $(addprefix $(BUILD_O)/, $(dir $<)))
	$(eval OUT = $(addprefix $(BUILD_O)/, $(subst .c,.o,$<)))
	@mkdir -p $(FOLDER)
	@echo "compiling $(notdir $(OUT))"
	@$(CC) $(LL) $(CC_FLAGS) -c -o $(OUT) $< $(INCLUDES)

$(BUILD_O)/%.o: %.c
	$(eval FOLDER = $(addprefix $(BUILD_O)/, $(dir $<)))
	$(eval OUT = $(addprefix $(BUILD_O)/, $(subst .c,.o,$<)))
	@mkdir -p $(FOLDER)
	@echo "compiling $(notdir $(OUT))"
	@$(CC) $(LL) $(CC_FLAGS) -c -o $(OUT) $< $(INCLUDES)

# Header

$(BUILD_I)/$(HEADER_NAME): $(HEADERS_H)
	@mkdir -p $(BUILD_I)
	@rm -rf $(BUILD_I)/$(HEADER_NAME)
	@touch $(BUILD_I)/$(HEADER_NAME)
	@for header_h in $(HEADERS_H) ; do \
		cp $${header_h} $(BUILD_I); \
	done
	@for header in $(HEADERS) ; do \
        echo "#include <$${header}>" >> $(BUILD_I)/$(HEADER_NAME); \
    done
	@echo "finished $(HEADER_NAME)"

# Tests

$(BUILD_T)/%: %.c $(LIBRARY) $(HEADER)
	$(eval FOLDER = $(addprefix $(BUILD_T)/, $(dir $<)))
	$(eval OUT = $(addprefix $(BUILD_T)/, $(subst .c,,$<)))
	@mkdir -p $(FOLDER)
	@echo "building test $(notdir $(OUT))"
	@$(CC) $(LL) $(CC_FLAGS) -o $(OUT) $< -I$(BUILD_I) -L$(BUILD_L) -l$(PROJECT)


.PHONY: clean
clean:
	rm -rf $(LIBRARY) $(OBJECTS) $(TESTS) $(EXECUTABLES) $(notdir $(EXECUTABLES))

.PHONY: cleanall
cleanall:
	rm -rf $(BUILD) $(notdir $(EXECUTABLES))
