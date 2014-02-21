<?php

/**
 * Implement hook_media_browser_plugin_info().
 */
function bangpoundmedia_media_browser_plugin_info() {
  $info = array();

  if (module_exists('imce')) {
    $info['imce'] = array(
      'title' => t('IMCE'),
      'class' => 'IMCEMediaBrowser',
      'weight' => 10,
    );
  }

  return $info;
}
