<?php

/**
 * Implement hook_file_displays_alter().
 *
 * @todo remove when 'default view callback' does anything.
 */
function bangpoundmedia_file_displays_alter(&$displays, $file, $view_mode) {

  // Disable mediaelement displays if the format settings exclude the file's URI scheme.
  // This option only exists on the file entity module's file display settings.
  $types = array('file_field_mediaelement_video', 'file_field_mediaelement_audio');
  $types = array_intersect($types, array_keys($displays));
  if (!empty($types)) {
    $scheme = file_uri_scheme($file->uri);
    foreach ($types as $type) {
      if (isset($displays[$type]['settings']['allowed_schemes']) && !in_array($scheme, array_keys(array_filter($displays[$type]['settings']['allowed_schemes'])))) {
        $displays[$type]['status'] = 0;
      }
    }
  }
}

/**
 * Implement hook_field_formatter_info_alter().
 */
function bangpoundmedia_field_formatter_info_alter(&$info) {
  $types = array('mediaelement_video', 'mediaelement_audio');
  foreach ($types as $type) {
    if (isset($info[$type])) {
      $info[$type]['settings']['allowed_schemes'] = array('public', 'private');
    }
  }
}
