##
## Build tools
##
CC = /usr/bin/gcc
ZIP = /usr/bin/zip
MKDIR=mkdir -p

##
## Compiler flags
##
COMMON_CFLAGS = -std=c99 -g
CAFIS_CFLAGS = -Wall
UNITY_CFLAGS = -Wall -Wextra -Werror -Wpointer-arith -Wcast-align -Wwrite-strings -Wswitch-default -Wunreachable-code -Winit-self -Wmissing-field-initializers -Wno-unknown-pragmas -Wstrict-prototypes -Wundef -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -DUNITY_FIXTURES

##
## Linker flags
##
LFLAGS = -g

##
## Root directories
##
BUILD_DIR = Build
UTEST_DIR = Tests
UTILS_DIR = Utils
UNITY_DIR = $(UTILS_DIR)/Unity

##
## Include directories
##
CAFIS_INCS = -I .
UNITY_INCS = -I $(UNITY_DIR)

##
## Misc
##
UTEST_EXE = all_tests

##
## Source files to include and exclude
##
CAFIS_SRCS = General/*.c \
             Extraction/Filters/*.c \
             Extraction/Model/*.c
CAFIS_SRCS_EXCLUDE = 

UTILS_SRCS =  IO/*.c
UTILS_SRCS_EXCLUDE = 

UTEST_SRCS =  General/*.c  General/runners/*.c \
              Extraction/Filters/*.c Extraction/Filters/runners/*.c
UTEST_SRCS_EXCLUDE = 
UTEST_SRCS += $(UTEST_EXE).c

UNITY_SRCS = $(addprefix  $(UNITY_DIR)/, unity.c unity_fixture.c)

##
## Process file lists
##
CAFIS_SRCS := $(wildcard $(CAFIS_SRCS))
CAFIS_SRCS := $(filter-out $(CAFIS_SRCS_EXCLUDE), $(CAFIS_SRCS))
CAFIS_OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(CAFIS_SRCS)))

UTILS_SRCS := $(wildcard $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS)))
UTILS_SRCS := $(filter-out $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS_EXCLUDE)), $(UTILS_SRCS))
UTILS_OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(UTILS_SRCS)))

UTEST_SRCS := $(wildcard $(addprefix $(UTEST_DIR)/, $(UTEST_SRCS)))
UTEST_SRCS := $(filter-out $(addprefix $(UTEST_DIR)/, $(UTEST_SRCS_EXCLUDE)), $(UTEST_SRCS))
UTEST_OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(UTEST_SRCS)))

UNITY_OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(UNITY_SRCS)))

##
## Targets
##
all: cafis
cafis: $(CAFIS_OBJS)
utest: $(UTEST_EXE)


##
## Rules
##
$(CAFIS_OBJS): $(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(CAFIS_CFLAGS) $(CAFIS_INCS) $< -o $@

$(UTILS_OBJS): $(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(CAFIS_CFLAGS) $(CAFIS_INCS) $< -o $@

$(UTEST_OBJS):  $(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(UNITY_CFLAGS) $(CAFIS_INCS) $(UNITY_INCS) $< -o $@

$(UNITY_OBJS):  $(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(UNITY_CFLAGS) $(UNITY_INCS) $< -o $@

$(UTEST_EXE): $(UTEST_OBJS) $(UNITY_OBJS) $(UTILS_OBJS) $(CAFIS_OBJS)
	$(CC) $(LFLAGS) $^ -o $(BUILD_DIR)/$@

archive:
	find . ! -path "*/Utils/*" -type f -name *.h | xargs $(ZIP) $(BUILD_DIR)/libAFIS.zip; \
	cd $(BUILD_DIR); \
	find . ! -path "*/Utils/*" ! -path "*/Tests/*" -type f -name *.o | xargs $(ZIP) -g libAFIS.zip
	
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all cafis utest clean archive
