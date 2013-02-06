<?php

/**
 * Implement hook_file_displays_alter().
 *
 * @todo remove when 'default view callback' does anything.
 */
function bangpoundmedia_file_displays_alter(&$displays, $file, $view_mode) {
  if ($view_mode == 'preview') {
    _file_sort_array_by_weight($displays);
    $display = end($displays);
    $displays['file_field_media_large_icon'] = array(
      'weight' => ++$display['weight'],
      'status' => TRUE,
      'settings' => NULL,
    );
  }
}
