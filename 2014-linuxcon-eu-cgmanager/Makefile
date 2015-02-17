clean:
	rm -f *.aux *.log *nav *.out *.pdf *.snm *.toc *.png

%.png: %.svg
	convert $^ $@

%.pdf: %.tex
	pdflatex $^

all: scm.png proxies.png pidmessage.png cgm-slides.pdf
