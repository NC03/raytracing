.DEFAULT_GOAL := gen_docs

gen_docs:
	git merge main
	doxygen Doxyfile
	make -Clatex/

