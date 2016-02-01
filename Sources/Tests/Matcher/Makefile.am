# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

SUBDIRS = runners

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

all-local:: SOURCES

SOURCES: Makefile runners/SOURCES
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

tsrc  = Test_BestMatchSkipper.c

include runners/SOURCES

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------

