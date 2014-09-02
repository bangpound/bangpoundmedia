!&# Media
=========
This module pulls together best practices for media in Drupal.

Dependencies
------------
* Media
* File Entity
* oEmbed

WYSIWYG
-------
This module implements CKEditor style sets for floating media within a flow of text. File entities rendered by the media filter can be identified in the theme layer by checking render elements for the `#media_filter` boolean. (See `bangpoundmedia_preprocess_file_entity()`.)

Media filter
------------
This module overrides Media module's filter and renders an entire file entity with fields and all extras, including contextual links even inside text fields. This feature conflicts with Drupal's field and filter cache, so formats using media filter are no longer cacheable.
