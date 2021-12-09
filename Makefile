SOURCE = P$(DOCNO).md
TARGET = $(PD)$(DOCNO)R$(REV)

PANDOC = pandoc
PANDOC_FMT = gfm+smart

AUTHOR ?= Casey Carter \&lt;<a href="mailto:Casey@Carter.net">Casey@Carter.net<\/a>\&gt;<br>
DATE ?= $(shell date --iso-8601)
HEADER ?= ../header.html.in

ifndef AUDIENCE
$(error AUDIENCE is not defined.)
endif

$(TARGET).html: $(SOURCE) header.html ../pandoc-template.html ../pandoc.css
	$(PANDOC) -f $(PANDOC_FMT) -t html -o $@ --csl=../acm-sig-proceedings.csl -s --template=../pandoc-template --include-before-body=header.html --include-in-header=../pandoc.css $<

# FIXME
$(TARGET).pdf: $(SOURCE)
	$(PANDOC) -f $(PANDOC_FMT) -t latex -o $@ --csl=../acm-sig-proceedings.csl -s $<

header.html: $(HEADER) Makefile
	sed 's/%%DOCNO%%/$(TARGET)/g;s/%%DATE%%/$(DATE)/g;s/%%AUDIENCE%%/$(AUDIENCE)/g;s/%%AUTHOR%%/$(AUTHOR)/g' < $< > $@~
	rm -f $@
	mv $@~ $@

clean:
	rm -f header.html $(TARGET).html $(TARGET).pdf *~

view: $(TARGET).html
	gnome-www-browser $(TARGET).html || cmd.exe /c start $(TARGET).html

cooked.txt: raw.txt
	sed -rf ../cook < $< > $@ || rm -f $@
