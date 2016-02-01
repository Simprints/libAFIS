# -*- makefile-automake -*-
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

SUBDIRS = Extraction General Matcher Utils Tests

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

lib_LTLIBRARIES = libafis.la libutils.la libtest.la

bin_PROGRAMS = extract all_tests

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

libafis_la_CFLAGS  = -I$(SOURCES_DIR)
libutils_la_CFLAGS = -I$(SOURCES_DIR)
libtest_la_CFLAGS  = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity

# ---------------------------------------------------------------------------
# Legacy tests
# ---------------------------------------------------------------------------

test: $(lib_LTLIBRARIES) $(bin_PROGRAMS)
	@for s in $(bin_PROGRAMS); do (set -x; ./$$s); done; :

# ---------------------------------------------------------------------------
# Sources for libafis
# ---------------------------------------------------------------------------

srcs =

include    General/SOURCES
include Extraction/SOURCES
include    Matcher/SOURCES

libafis_la_SOURCES = $(srcs)

# ---------------------------------------------------------------------------
# Sources for libutils
# ---------------------------------------------------------------------------

usrc =

include Utils/SOURCES

libutils_la_SOURCES = $(usrc)

# ---------------------------------------------------------------------------
# Sources for libtest
# ---------------------------------------------------------------------------

tsrc =

include Tests/SOURCES

libtest_la_SOURCES = $(tsrc)

# ---------------------------------------------------------------------------
# Linking test programmes
# ---------------------------------------------------------------------------

all_tests_SOURCES = Tests/all_tests.c Utils/Unity/unity.c
all_tests_LDADD   = libtest.la libafis.la libutils.la
all_tests_CFLAGS  = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity
all_tests_CFLAGS += -Wall -Wextra -Werror -Wpointer-arith -Wcast-align
all_tests_CFLAGS += -Wwrite-strings -Wswitch-default -Wunreachable-code
all_tests_CFLAGS += -Winit-self -Wmissing-field-initializers
all_tests_CFLAGS += -Wno-unknown-pragmas -Wstrict-prototypes -Wundef
all_tests_CFLAGS += -Wold-style-definition -Wmissing-prototypes
all_tests_CFLAGS += -Wmissing-declarations -DUNITY_FIXTURES

extract_SOURCES   = Tests/extract.c Utils/Unity/unity.c
extract_LDADD     = libafis.la
extract_CFLAGS    = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
