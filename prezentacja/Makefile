NAME := PORR_prezentacja
ENGINE := pdflatex
BIB := bibtex
LOGS := logs

all: notes
notes: $(NAME).tex
	mkdir -p $(LOGS)
	$(ENGINE) --output-dir=$(LOGS) $(NAME).tex
	mv $(LOGS)/$(NAME).pdf $(LOGS)/.. 
clean:
	rm -rf $(LOGS)/ $(NAME).pdf

.PHONY: all clean

