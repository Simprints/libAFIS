# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

lib_LTLIBRARIES = libgeneral.la

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

libgeneral_la_CFLAGS = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

libgeneral_la_SOURCES  = runners/TestRunner_Array.c
libgeneral_la_SOURCES += runners/TestRunner_Calc.c
libgeneral_la_SOURCES += runners/TestRunner_MinutiaeDetection.c
libgeneral_la_SOURCES += runners/TestRunner_Point.c
libgeneral_la_SOURCES += runners/TestRunner_BinaryMap.c
libgeneral_la_SOURCES += runners/TestRunner_Equalizer.c
libgeneral_la_SOURCES += runners/TestRunner_Pgm.c

libgeneral_la_SOURCES += Test_BinaryMap.c Test_Equalizer.c Test_Pgm.c
libgeneral_la_SOURCES += Test_Array.c Test_Calc.c Test_MinutiaeDetection.c
libgeneral_la_SOURCES += Test_Point.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
