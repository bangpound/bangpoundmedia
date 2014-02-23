<?php


/**
 * Implements hook_field_formatter_info().
 */
function bangpoundmedia_field_formatter_info() {
  $info = array();
  $info['file_rendered_image'] = array(
    'label' => t('Rendered file image'),
    'description' => t('Display the file in a specific view mode and override the image style'),
    'field types' => array('file', 'image'),
    'settings' => array(
      'file_view_mode' => 'default',
      'image_style' => '',
      'image_link' => '',
    ),
    'file formatter' => array(
      'hidden' => TRUE,
    ),
  );
  return $info;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function bangpoundmedia_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();

  if ($display['type'] == 'file_rendered_image') {
    $element['file_view_mode'] = array(
      '#title'   => t('View mode'),
      '#type'    => 'select',
      '#options' => file_entity_view_mode_labels(),
      '#default_value' => $settings['file_view_mode'],
      // Never empty, so no #empty_option
    );

    $image_styles = image_style_options(FALSE, PASS_THROUGH);
    $element['image_style'] = array(
      '#title' => t('Image style'),
      '#type' => 'select',
      '#default_value' => $settings['image_style'],
      '#empty_option' => t('None (original image)'),
      '#options' => $image_styles,
    );

    $link_types = array(
      'content' => t('Content'),
      'file' => t('File'),
    );
    $element['image_link'] = array(
      '#title' => t('Link image to'),
      '#type' => 'select',
      '#default_value' => $settings['image_link'],
      '#empty_option' => t('Nothing'),
      '#options' => $link_types,
    );
  }
  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function bangpoundmedia_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = array();

  if ($display['type'] === 'file_rendered_image') {
    $view_mode_label = file_entity_view_mode_label($settings['file_view_mode'], t('Unknown'));
    $summary[] = t('View mode: %mode', array('%mode' => $view_mode_label));

    $image_styles = image_style_options(FALSE, PASS_THROUGH);
    // Unset possible 'No defined styles' option.
    unset($image_styles['']);
    // Styles could be lost because of enabled/disabled modules that defines
    // their styles in code.
    if (isset($image_styles[$settings['image_style']])) {
      $summary[] = t('Image style: @style', array('@style' => $image_styles[$settings['image_style']]));
    }
    else {
      $summary[] = t('Original image');
    }

    $link_types = array(
      'content' => t('Linked to content'),
      'file' => t('Linked to file'),
    );
    // Display this setting only if image is linked.
    if (isset($link_types[$settings['image_link']])) {
      $summary[] = $link_types[$settings['image_link']];
    }
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function bangpoundmedia_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $settings = $display['settings'];
  $element = array();

  if ($display['type'] == 'file_rendered_image') {
    $view_mode = $settings['file_view_mode'];

    // To prevent infinite recursion caused by reference cycles, we store
    // diplayed nodes in a recursion queue.
    $recursion_queue = &drupal_static(__FUNCTION__, array());

    // If no 'referencing entity' is set, we are starting a new 'reference
    // thread' and need to reset the queue.
    // @todo Bug: $entity->referencing_entity on files referenced in a different
    // thread on the page.
    // E.g: 1 references 1+2 / 2 references 1+2 / visit homepage.
    // We'd need a more accurate way...
    if (!isset($entity->referencing_entity)) {
      $recursion_queue = array();
    }

    // The recursion queue only needs to track files.
    if ($entity_type == 'file') {
      list($id) = entity_extract_ids($entity_type, $entity);
      $recursion_queue[$id] = $id;
    }

    // Prevent 'empty' fields from causing a WSOD.
    $items = array_filter($items);

    // Check the recursion queue to determine which nodes should be fully
    // displayed, and which nodes will only be displayed as a title.
    $files_display = array();
    foreach ($items as $delta => $item) {
      if (!isset($recursion_queue[$item['fid']])) {
        $files_display[$item['fid']] = file_load($item['fid']);
        if (!empty($item['description'])) {
          $files_display[$item['fid']]->description = $item['description'];
        }
      }
    }

    // Load and build the fully displayed nodes.
    if ($files_display) {
      foreach ($files_display as $fid => $file) {
        $files_display[$fid]->referencing_entity = $entity;
        $files_display[$fid]->referencing_field = $field['field_name'];
      }
      $output = file_view_multiple($files_display, $view_mode);
      // Remove the first level from the output array.
      $files_built = reset($output);
    }

    // Check if the formatter involves a link.
    if ($display['settings']['image_link'] == 'content') {
      $uri = entity_uri($entity_type, $entity);
    }
    elseif ($display['settings']['image_link'] == 'file') {
      $link_file = TRUE;
    }

    foreach (element_children($files_built) as $child_key) {
      if ($files_built[$child_key]['file']['#theme'] == 'image_formatter') {
        if (isset($link_file)) {
          $uri = array(
            'path' => file_create_url($files_built[$child_key]['file']['#item']['uri']),
            'options' => array(),
          );
        }
        $files_built[$child_key]['file']['#image_style'] = $display['settings']['image_style'];
        $files_built[$child_key]['file']['#path'] = isset($uri) ? $uri : '';
      }
    }

    // Assemble the render array.
    foreach ($items as $delta => $item) {
      if (isset($files_built[$item['fid']])) {
        $element[$delta] = $files_built[$item['fid']];
      }
    }
  }
  return $element;
}
