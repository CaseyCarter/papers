DOCNO = 0899
REV = 0
PD = D
SOURCE = P$(DOCNO).md
TARGET = $(PD)$(DOCNO)R$(REV)

PANDOC = pandoc

$(TARGET).html: $(SOURCE) header.html pandoc-template.html
	$(PANDOC) -f markdown_github+yaml_metadata_block+citations+smart -t html -o $@ --filter pandoc-citeproc --csl=acm-sig-proceedings.csl -s --template=pandoc-template --include-before-body=header.html --include-in-header=pandoc.css $<

$(TARGET).pdf: $(SOURCE)
	$(PANDOC) -f markdown_github+yaml_metadata_block+citations+smart -t latex -o $@ --filter pandoc-citeproc --csl=acm-sig-proceedings.csl -s $<

header.html: header.html.in Makefile
	sed 's/%%DOCNO%%/$(TARGET)/g' < $< > $@ || rm -f $@

clean:
	rm -f $(TARGET).html *~

view: $(TARGET).html
	gnome-www-browser $(TARGET).html

cooked.txt: raw.txt
	sed -rf cook < $< > $@ || rm -f $@
