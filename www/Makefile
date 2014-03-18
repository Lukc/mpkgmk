all: index.xhtml why.xhtml faq.xhtml features.xhtml

index.xhtml: header.in index.in footer.in
	@echo '  [CAT]   index.xhtml'
	@cat header.in index.in footer.in > index.xhtml

why.xhtml: header.in why.in footer.in
	@echo '  [CAT]   why.xhtml'
	@cat header.in why.in footer.in > why.xhtml

faq.xhtml: header.in faq.in footer.in
	@echo '  [CAT]   faq.xhtml'
	@cat header.in faq.in footer.in > faq.xhtml

features.xhtml: header.in features.in footer.in
	@echo '  [CAT]   features.xhtml'
	@cat header.in features.in footer.in > features.xhtml

clean:  index.xhtml.clean why.xhtml.clean faq.xhtml.clean features.xhtml.clean

index.xhtml.clean:
	@echo '  [RM]    index.xhtml'
	@rm -f index.xhtml

why.xhtml.clean:
	@echo '  [RM]    why.xhtml'
	@rm -f why.xhtml

faq.xhtml.clean:
	@echo '  [RM]    faq.xhtml'
	@rm -f faq.xhtml

features.xhtml.clean:
	@echo '  [RM]    features.xhtml'
	@rm -f features.xhtml

