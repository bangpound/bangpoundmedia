<?php

/**
 * Implementation of hook_media_token_to_markup_alter().
 *
 * Re-render the file entity with its fields for the selected view mode.
 */
function bangpoundmedia_media_wysiwyg_token_to_markup_alter(array &$element, array $tag_info, array $settings) {
  $langcode = $GLOBALS['language_content']->language;

  if (!isset($settings['wysiwyg'])) {
    $build = $element['content']['file'];

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
    $element = file_view($file, $view_mode, $langcode);
    $element['file'] = $build;

    // Add class to wrapper that indicates how the embedded media is aligned. Find this
    // as the image alignment from WYSIWYG image properties or as float attribute of
    if (isset($element['file']['#attributes']['align'])) {
      $element['#attributes']['class'][] = 'figure__'. $element['file']['#attributes']['align'];
    }

    if (isset($element['file']['#attributes']['style'])) {
      // Convert float on file to class attribute on container.
      $style = media_wysiwyg_parse_css_declarations($element['file']['#attributes']['style']);
      if (!isset($style['width']) && isset($element['file']['#file']->metadata['width'])) {
        $style['width'] = $element['file']['#file']->metadata['width'] .'px';
      }
      if (!isset($style['height']) && isset($element['file']['#file']->metadata['height'])) {
        $style['height'] = $element['file']['#file']->metadata['height'] .'px';
      }

      if (isset($style['float'])) {
        $element['#attributes']['class'][] = 'figure__'. $style['float'];
        // Prevent double floating.
        unset($style['float']);
      }

      $style = bangpoundmedia_compile_style_attribute($style);
      $element['file']['#attributes']['style'] = $style;

      if (isset($element['file']['#item'])) {
        $element['file']['#item']['attributes']['style'] = $style;
      }
    }

    // Only add class and style attribute from rendered file to the outer wrapper.
    if (isset($element['#attributes'])) {
      $element['#attributes'] = array_intersect_key($element['#attributes'], array('class' => ''));
    }

    $element['#theme'] .= '__'. $view_mode;
    $element['#media_filter'] = TRUE;
  }
}

function bangpoundmedia_compile_style_attribute($style) {
  $output = '';
  foreach ($style as $key => $value) {
    $output .= $key .':'. $value .';';
  }
  return $output;
}
