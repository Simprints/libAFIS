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
	 for s in $(usrc); do \
		echo "usrc += $$d/$$s"; done           >> $@
	@echo "# End"                                  >> $@

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

# unity.c compiled directly - compiler flag dependent

usrc = unity_fixture.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
