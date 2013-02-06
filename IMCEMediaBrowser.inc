<?php

/**
 * @file
 * Definition of MediaBrowserView.
 */

/**
 * Media browser plugin for displaying a specific view and display.
 */
class IMCEMediaBrowser extends MediaBrowserPlugin {

  /**
   * Implements MediaBrowserPluginInterface::__construct().
   */
  public function __construct($info, $params) {
    parent::__construct($info, $params);
  }

  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    return TRUE; //imce_access($account);
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    global $conf;

    $original = array();
    foreach (array('imce_custom_process', 'imce_custom_scan') as $key) {
      if (isset($conf[$key])) {
        $original[$key] = $conf[$key];
      }
    }

    $conf['imce_custom_process'] = array('bangpoundmedia_imce_process' => TRUE);
    $conf['imce_custom_scan'] = 'bangpoundmedia_imce_scan_directory';

    module_load_include('inc', 'imce', 'inc/imce.page');
    $scheme = 'public';
    $jsop = isset($_GET['jsop']) ? filter_input(INPUT_GET, 'jsop', FILTER_SANITIZE_STRING) : NULL;
    $output = imce_content($GLOBALS['user'], $scheme, $jsop);

    foreach (array('imce_custom_process', 'imce_custom_scan') as $key) {
      unset($conf[$key]);
      if (isset($original[$key])) {
        $conf[$key] = $original[$key];
      }
    }

    return array(
      '#markup' => $output,
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'bangpoundmedia') . '/imcemediabrowser.plugin.js',
        ),
      ),
    );
  }
}

