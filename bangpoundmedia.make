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

projects[oembed][version] = 1.x-dev
projects[oembed][type] = module
projects[oembed][download][type] = git
projects[oembed][download][branch] = 7.x-1.x
projects[oembed][subdir] = contrib
projects[oembed][patch][] = https://drupal.org/files/issues/oembed-inline-dependency-remove-2239345-1_0.patch

projects[plupload][version] = 1.6
projects[plupload][subdir] = contrib

projects[remote_stream_wrapper][subdir] = contrib

libraries[plupload][download][type] = get
libraries[plupload][directory_name] = plupload
libraries[plupload][download][url] = https://github.com/moxiecode/plupload/archive/v1.5.8.zip
libraries[plupload][patch][] = https://drupal.org/files/issues/plupload-1_5_8-rm_examples-1903850-16.patch
libraries[plupload][type] = library
