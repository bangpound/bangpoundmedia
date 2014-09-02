<?php

/**
 * Implements hook_entity_view_mode_info().
 *
 * @return mixed
 */
function bangpoundmedia_entity_view_mode_info() {
  $view_modes['file']['embed'] = array(
    'label' => t('Embed'),
    'custom_settings' => TRUE,
  );
  return $view_modes;
}
