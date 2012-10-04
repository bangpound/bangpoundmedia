<?php

function bangpoundmedia_media_wysiwyg_allowed_view_modes_alter(&$view_modes, $file) {
  foreach ($view_modes as $key => $value) {
    if ($key == 'embed') {
      continue;
    }
    else {
      unset($view_modes[$key]);
    }
  }
}

/**
 * Implementation of hook_media_token_to_markup_alter().
 *
 * Re-render the file entity with its fields for the selected view mode.
 */
function bangpoundmedia_media_token_to_markup_alter(&$element, $tag_info, $settings) {
  $file = $element['#file'];
  $view_mode = $element['#view_mode'];

  $new_element = file_view($file, $view_mode);

  // Copy the attributes from the original element to the new one.
  if (isset($element['#attributes'])) {
    if (!isset($new_element['file']['#attributes'])) {
      $new_element['file']['#attributes'] = array();
    }
    $new_element['file']['#attributes'] = array_merge_recursive($new_element['file']['#attributes'], $element['#attributes']);

    if (!isset($new_element['#attributes'])) {
      $new_element['#attributes'] = array();
    }
    $new_element['#attributes'] = array_merge_recursive($new_element['#attributes'], $element['#attributes']);

    if (isset($element['#alt'])) {
      $new_element['file']['#alt'] = $element['#alt'];
    }
  }

  $element = $new_element;

  $theme = $element['#theme'];

  $element['#theme'] =  $theme .'__'. $view_mode;
}
