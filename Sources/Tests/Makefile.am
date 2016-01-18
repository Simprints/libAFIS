# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

SUBDIRS = DataStructures Extraction General Matcher

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

bin_PROGRAMS = all_tests extract

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

local_cflags = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity

local_ldadd  = DataStructures/libdatastructures.la
local_ldadd += Extraction/libextraction.la
local_ldadd += General/libgeneral.la Matcher/libmatcher.la

all_tests_CFLAGS = $(local_cflags)
all_tests_LDADD  = $(local_libadd)

extract_CFLAGS   = $(local_cflags)
extract_LDADD    = $(local_libadd)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

all_tests_SOURCES = all_tests.c
extract_SOURCES   = extract.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
