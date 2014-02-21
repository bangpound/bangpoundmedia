<?php

/**
 * Implementation of hook_media_token_to_markup_alter().
 *
 * Re-render the file entity with its fields for the selected view mode.
 */
function bangpoundmedia_media_wysiwyg_token_to_markup_alter(array &$element, array $tag_info, array $settings) {
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }
  if (!isset($settings['wysiwyg'])) {

    // Copy the attributes from file's render array to add to the outer wrapper.
    $attributes = $element['content']['file']['#attributes'] + $settings['attributes'];

    // Regenerate embedded media from file entity already loaded.
    $file = $element['content']['file']['#file'];
    $view_mode = $element['content']['file']['#view_mode'];

    // Allow modules to change the view mode.
    $context = array(
      'entity_type' => 'file',
      'entity' => $file,
      'langcode' => $langcode,
    );
    drupal_alter('entity_view_mode', $view_mode, $context);

    // Regenerate render array for file.
    $element = file_view($file, $view_mode);

    // Replace the attributes on the file itself, but remove class which will be on
    // wrapper. The width and height from WYSIWYG settings need to be on the actual image.
    if (!isset($element['file']['#attributes'])) {
      $element['file']['#attributes'] = array();
    }
    $element['file']['#attributes'] = array_merge($element['file']['#attributes'], $attributes);
    unset($element['file']['#attributes']['class']);

    // Copy style attribute to the outer wrapper but remove the height and reset width
    // if it's not in style but only part of element attributes.
    $style = media_wysiwyg_parse_css_declarations(isset($attributes['style']) ? $attributes['style'] : '');
    if (isset($style['height'])) {
      unset($style['height']);
    }
    if (isset($style['width'])) {
      unset($style['width']);
    }

    // Add class to wrapper that indicates how the embedded media is aligned. Find this
    // as the image alignment from WYSIWYG image properties or as float attribute of
    if (isset($attributes['align'])) {
      $attributes['class'][] = 'media-image-'. $attributes['align'];
    }
    else if (isset($style['float'])) {
      $attributes['class'][] = 'media-image-'. $style['float'];
    }

    // Prevent double floating.
    unset($style['float']);

    // Regenerate style attribute from remaining properties.
    $attributes['style'] = '';
    foreach ($style as $key => $value) {
      $attributes['style'] .= $key .':'. $value .';';
    }

    $style = media_wysiwyg_parse_css_declarations(isset($element['file']['#attributes']['style']) ? $element['file']['#attributes']['style'] : '');
    unset($style['float']);
    $element['file']['#attributes']['style'] = '';
    foreach ($style as $key => $value) {
      $element['file']['#attributes']['style'] .= $key .':'. $value .';';
    }

    // Only add class and style attribute from rendered file to the outer wrapper.
    $element['#attributes'] = array_intersect_key(array_filter($attributes), array_flip(array('class', 'style')));

    $element['#theme'] .= '__'. $view_mode;
    $element['#media_filter'] = TRUE;
  }
}
