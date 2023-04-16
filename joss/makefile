current_dir = $(shell pwd)

test: paper.md paper.bib
	podman run --privileged --rm --volume "$(current_dir)"/:/data --env JOURNAL=joss openjournals/inara

clean:
	rm paper.jats paper.pdf 
