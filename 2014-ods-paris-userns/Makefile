all: user_namespaces.pdf

clean:
	rm -f *.aux *.log *nav *.out *.pdf *.snm *.toc *.png *.vrb

%.png: %.svg
	convert $^ $@

# run pdflatex twice if we're using the TOC
%.pdf: %.tex
	pdflatex $^
	pdflatex $^
