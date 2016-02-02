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

all-local:: SOURCES

SOURCES: Makefile
	@rm -f $@
	@echo ">>> Generating $@"
	@echo "# Generated from $(subdir)/Makefile.am" >> $@
	@d=`basename $(subdir)`;\
	 for s in $(tsrc); do \
		echo "tsrc += $$d/$$s"; done           >> $@
	@echo "# End"                                  >> $@

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

tsrc  = TestRunner_Array.c TestRunner_Calc.c TestRunner_MinutiaeDetection.c
tsrc += TestRunner_Point.c TestRunner_BinaryMap.c TestRunner_Equalizer.c
tsrc += TestRunner_Pgm.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
