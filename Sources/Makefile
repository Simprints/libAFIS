##
## Build tools
##
CC = /usr/bin/gcc
ZIP = tar
MKDIR=mkdir -p

##
## Environment variables from CI System
##
BUILD_NUMBER = 1.0.0.$(DRONE_BUILD_NUMBER)

##
## Compiler flags
##
COMMON_CFLAGS = -std=c99 -g
LIBAFIS_CFLAGS = -Wall
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
LIBAFIS_INCS = -I .
UNITY_INCS = -I $(UNITY_DIR)

##
## Misc
##
UTEST_EXE = all_tests

##
## Source files to include and exclude
##
LIBAFIS_SRCS = General/*.c \
               Extraction/Filters/*.c Extraction/Model/*.c Extraction/*.c \
               Templates/*.c \
               Matcher/*.c  Matcher/Minutia/*.c

LIBAFIS_SRCS_EXCLUDE =

UTILS_SRCS =  IO/*.c
UTILS_SRCS_EXCLUDE =

UTEST_SRCS =  General/*.c  General/runners/*.c \
              Extraction/Filters/*.c Extraction/Filters/runners/*.c Extraction/Model/*.c Extraction/Model/runners/*.c \
              DataStructures/*.c \
              EndToEnd/*.c \
              Matcher/*.c Matcher/runners/*.c

UTEST_SRCS_EXCLUDE =
UTEST_SRCS += $(UTEST_EXE).c

UNITY_SRCS = $(addprefix  $(UNITY_DIR)/, unity.c unity_fixture.c)

##
## Process file lists
##
LIBAFIS_SRCS := $(wildcard $(LIBAFIS_SRCS))
LIBAFIS_SRCS := $(filter-out $(LIBAFIS_SRCS_EXCLUDE), $(LIBAFIS_SRCS))
LIBAFIS_OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(LIBAFIS_SRCS)))

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
all: runall
libafis: $(LIBAFIS_OBJS)
tests: $(UTEST_EXE) $(BUILD_DIR)/Tests/extract
utest: runUnitTest

##
## Rules
##
$(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(LIBAFIS_CFLAGS) $(LIBAFIS_INCS) $< -o $@

$(BUILD_DIR)/Tests/extract: $(BUILD_DIR)/Tests/extract.o $(LIBAFIS_OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(UTILS_OBJS): $(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(LIBAFIS_CFLAGS) $(LIBAFIS_INCS) $< -o $@

$(UTEST_OBJS):  $(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(UNITY_CFLAGS) $(LIBAFIS_INCS) $(UNITY_INCS) $< -o $@

$(UNITY_OBJS):  $(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(UNITY_CFLAGS) $(UNITY_INCS) $< -o $@

$(UTEST_EXE): $(UTEST_OBJS) $(UNITY_OBJS) $(UTILS_OBJS) $(LIBAFIS_OBJS)
	$(CC) $(LFLAGS) $^ -o $(BUILD_DIR)/$@

runUnitTest: $(UTEST_EXE)
	$(BUILD_DIR)/all_tests ../TestData/

archive: $(LIBAFIS_OBJS) runUnitTest
	find . ! -path "*/Utils/*" ! -path "*/Tests/*" -type f -name *.h -exec $(ZIP) -cvf $(BUILD_DIR)/libAFIS-$(BUILD_NUMBER).tar {} \+ ; \
	cd $(BUILD_DIR); \
	find . ! -path "*/Utils/*" ! -path "*/Tests/*" -type f -name *.o -exec $(ZIP) -rvf libAFIS-$(BUILD_NUMBER).tar {} \+

runall: clean libafis tests runUnitTest archive

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all libafis utest clean archive runUnitTest
