FILENAME=szg0031CA01
LATEX_COMPILER=xelatex

all: paper clean-intermediate

paper:
	$(LATEX_COMPILER) $(FILENAME)
	$(LATEX_COMPILER) $(FILENAME)

clean-intermediate:
	rm -f $(FILENAME).{aux,bbl,blg,fff,log,ttt,out}

clean:clean-intermediate
	rm -f $(FILENAME).pdf
