####################################################
# Students' Makefile for the CS:APP Architecture Lab
####################################################

# Default team name and version number
TEAM = ecen324
VERSION = 2

# Where are the different parts of the lab should be copied to when they
# are handed in.
HANDINDIR-PARTA = /home/jonesro/ecen324/archlab/handin-parta
HANDINDIR-PARTB = /home/jonesro/ecen324/archlab/handin-partb
HANDINDIR-PARTC = /home/jonesro/ecen324/archlab/handin-partc

# Use this rule to hand in Part A ("make handin-parta")
handin-parta:
	cp sim/misc/sum.ys $(HANDINDIR-PARTA)/$(TEAM)-$(VERSION)-sum.ys
	chmod 404 $(HANDINDIR-PARTA)/$(TEAM)-$(VERSION)-sum.ys
	cp sim/misc/rsum.ys $(HANDINDIR-PARTA)/$(TEAM)-$(VERSION)-rsum.ys
	chmod 404 $(HANDINDIR-PARTA)/$(TEAM)-$(VERSION)-rsum.ys
	cp sim/misc/copy.ys $(HANDINDIR-PARTA)/$(TEAM)-$(VERSION)-copy.ys
	chmod 404 $(HANDINDIR-PARTA)/$(TEAM)-$(VERSION)-copy.ys

# Use this rule to handin Part B ("make handin-partb")
handin-partb:
	cp sim/seq/seq-full.hcl $(HANDINDIR-PARTB)/$(TEAM)-$(VERSION)-seq-full.hcl
	chmod  404 $(HANDINDIR-PARTB)/$(TEAM)-$(VERSION)-seq-full.hcl

# Use this rule to handin Part C ("make handin-partc")
handin-partc:
	cp sim/pipe/ncopy.ys $(HANDINDIR-PARTC)/$(TEAM)-$(VERSION)-ncopy.ys
	chmod 404 $(HANDINDIR-PARTC)/$(TEAM)-$(VERSION)-ncopy.ys
	cp sim/pipe/pipe-full.hcl $(HANDINDIR-PARTC)/$(TEAM)-$(VERSION)-pipe-full.hcl
	chmod 404 $(HANDINDIR-PARTC)/$(TEAM)-$(VERSION)-pipe-full.hcl

clean:
	rm -f *~ *.o



