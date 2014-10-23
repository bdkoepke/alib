AUX = *.aux *.bbl *.dvi *.idx *.log *.scn *.tex

all: wcltx.pdf

wcltx.pdf: wcltx.tex wcltx.bib
	pdflatex wcltx
	rm -f wcltx.blg

wcltx.tex: wcltx.w
	cweave wcltx

clean:
	/bin/rm -f $(AUX)
