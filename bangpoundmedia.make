; bangpoundmedia makefile

api = 2
core = 7.x

projects[image_resize_filter][subdir] = contrib

projects[media][version] = 2.x-dev
projects[media][type] = module
projects[media][download][type] = git
projects[media][download][branch] = 7.x-2.x
projects[media][subdir] = contrib

projects[file_entity][version] = 2.x-dev
projects[file_entity][type] = module
projects[file_entity][download][type] = git
projects[file_entity][download][branch] = 7.x-2.x
projects[file_entity][subdir] = contrib

projects[oembed][version] = 0.x-dev
projects[oembed][type] = module
projects[oembed][download][type] = git
projects[oembed][download][branch] = 7.x-0.x
projects[oembed][subdir] = contrib

projects[plupload][version] = 1.1
projects[plupload][subdir] = contrib

projects[mediaelement][subdir] = contrib

projects[remote_stream_wrapper][subdir] = contrib

libraries[plupload][download][type] = get
libraries[plupload][download][url] = http://plupload.com/downloads/plupload_1_5_5.zip
libraries[plupload][directory_name] = plupload
libraries[plupload][destination] = libraries
libraries[plupload][type] = library

libraries[mediaelement][download][type] = git
libraries[mediaelement][download][url] = https://github.com/johndyer/mediaelement.git
libraries[mediaelement][download][tag] = 2.10.1
libraries[mediaelement][directory_name] = mediaelement
libraries[mediaelement][destination] = libraries
libraries[mediaelement][type] = library
