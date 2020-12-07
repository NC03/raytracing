.DEFAULT_GOAL := docs

docs:
	git merge main
	doxygen Doxyfile
	make -Clatex/
