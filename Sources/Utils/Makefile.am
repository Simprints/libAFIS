# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

SUBDIRS = IO Misc Unity

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

all-local:: SOURCES

SOURCES: Makefile IO/SOURCES Misc/SOURCES Unity/SOURCES
	@rm -f $@
	@echo ">>> Generating $@"
	@echo "# Generated from $(subdir)/Makefile.am" >> $@
	@d=`basename $(subdir)`;\
	 for s in $(usrc); do \
		echo "usrc += $$d/$$s"; done           >> $@
	@echo "# End"                                  >> $@

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

usrc =

include    IO/SOURCES
include  Misc/SOURCES
include Unity/SOURCES

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
