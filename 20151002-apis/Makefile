all: apis.pdf

timeline.pdf: timeline.fig
	fig2pdf --nogv timeline.fig

%.pdf: %.tex timeline.pdf
	pdflatex $<
	pdflatex $<

clean:
	rm -f apis.aux apis.log apis.nav apis.out apis.pdf apis.snm apis.toc apis.vrb timeline.pdf *.bak
