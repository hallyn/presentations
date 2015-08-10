all: security.pdf

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

clean:
	rm -f security.aux security.log security.nav security.out security.pdf security.snm security.toc security.vrb
