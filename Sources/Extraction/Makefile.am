# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

SUBDIRS = Filters Model MinutiaeDetection

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

all-local:: SOURCES

SOURCES: Makefile Filters/SOURCES Model/SOURCES MinutiaeDetection/SOURCES
	@rm -f $@
	@echo ">>> Generating $@"
	@echo "# Generated from $(subdir)/Makefile.am" >> $@
	@d=`basename $(subdir)`;\
	 for s in $(srcs); do \
		echo "srcs += $$d/$$s"; done           >> $@
	@echo "# End"                                  >> $@

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

srcs = Extract.c

include           Filters/SOURCES
include             Model/SOURCES
include MinutiaeDetection/SOURCES

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
