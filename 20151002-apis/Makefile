all: apis.pdf

%.pdf: %.tex timeline.pdf
	pdflatex $<
	pdflatex $<

clean:
	rm -f apis.aux apis.log apis.nav apis.out apis.pdf apis.snm apis.toc apis.vrb
