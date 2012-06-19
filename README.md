zebfross.com
===============

This is how I created my personal website, using [Nanoc](http://nanoc.stoneship.org/).  Nanoc is a convenient, command-line tool for generating static sites.

Download
--------------

Fork the project and then clone it with:

	git clone git@github.com:[username]/zebfross-dot-com.git

Here is the directory structure

* config.yaml - configuration for the nanoc compiler
* content - all website content; html files are written in kramdown (markdown varient)
* layouts - the website layouts
* lib - ruby helper scripts
* README.md - this
* Rules - rules for how to compile the site content

Compile & Run
--------------

	cd zebfross-dot-com
	nanoc

The html pages will be compiled into zebfross-dot-com/output/.  Everything in this folder should make a functioning website.  Test it out with:

	cd zebfross-dot-com
	nanoc view &
	wget localhost:3000

If everything worked, it should download the home page.

Upload
--------------

After modifying the website, it is easy to upload it to a web server.  Start by modifying the _config.yaml_ file.  Under deploy, change this line:

	dst: "zebfross@zebfross.com:~/public_html"

to

	dst: "your_username@your_url.com:your_dir"

Then upload the files by running the following:

	nanoc deploy --target public

