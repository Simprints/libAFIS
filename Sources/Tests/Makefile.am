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

all-local:: SOURCES

SOURCES: Makefile DataStructures/SOURCES Extraction/SOURCES \
		General/SOURCES Matcher/SOURCES
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

tsrc =

include DataStructures/SOURCES
include     Extraction/SOURCES
include        General/SOURCES
include        Matcher/SOURCES

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
