!&# Media
=========
This module pulls together best practices for media in Drupal.

Dependencies
------------
* Media
* File Entity
* oEmbed

Conventions
-----------
File entity module allows one file to be tested against several file formatters until one successfully renders the file.

* File formatters for the preview view mode should always return an image.
* File formatters that can test without using the network should run before file formatters that rely on the network to render. For example, oEmbed should always run after the Image formatter.
  * For image file entities, `file_image` formatter should run early.
  * oEmbed should run later.
  * Last resort formatters such as `file_field_media_large_icon` should run last.

Precautions
-----------
This module removes File formatters that don't make any sense.

* `file_field_image` is not available because it is superseded by `file_image` which uses tokens for `alt` and `title` attributes.
* `file_field_file_table` is not available because the file formatter only works on one file at a time, adn the table formatter is intended to show multiple values.
* `file_field_file_rendered` is not available because it is confusing and potentially recursive.
* Other file formatters have descriptions.

WYSIWYG
-------
This module implements CKEditor style sets for floating media within a flow of text. File entities rendered by the media filter can be identified in the theme layer by checking render elements for the `#media_filter` boolean. (See `bangpoundmedia_preprocess_file_entity()`.)

Media filter
------------
This module overrides Media module's filter and renders an entire file entity with fields and all extras, including contextual links even inside text fields. This feature conflicts with Drupal's field and filter cache, so formats using media filter are no longer cacheable.
