<?php

/**
 * @file
 * Describe hooks provided by the !&# Media module.
 */

/**
 * Alter the Media WYSIWYG filter tag embedded in a text field.
 *
 * @param array $tag_info
 *   The filter tag converted into an associative array by
 *   media_token_to_markup() with the following elements:
 *   - 'fid': The ID of the media file being rendered.
 *   - 'file': The object from file_load() of the media file being rendered.
 *   - 'view_mode': The view mode being used to render the file.
 *   - 'attributes': An additional array of attributes that could be output
 *     with media_get_file_without_label().
 *
 * @see media_wysiwyg_token_to_markup()
 */
function hook_bangpoundmedia_wysiwyg_token_alter(&$tag_info) {

  // Prevent exceptions by unsetting invalid view_mode values.
  $info = entity_get_info();
  $view_modes = array_keys($info['file']['view modes']);
  if (isset($tag_info['view_mode']) && !in_array($tag_info['view_mode'], $view_modes)) {
    unset($tag_info['view_mode']);
  }
}
