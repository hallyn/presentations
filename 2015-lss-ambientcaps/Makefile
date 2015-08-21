all: capa.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -f capa.aux capa.log capa.nav capa.out capa.pdf capa.snm capa.toc capa.vrb
