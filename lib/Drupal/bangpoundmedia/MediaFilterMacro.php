<?php

/**
 * @file
 * Contains Drupal\bangpoundmedia\MediaFilterMacro.
 */

namespace Drupal\bangpoundmedia;

use Drupal\inline\MacroBase;

class MediaFilterMacro extends MacroBase {

  protected $macroType = 'media_filter';

  protected $tag;

  public function getParameters() {
    $args = array();
    $args['tag'] = array(
      '#datatype' => 'string',
      '#required' => TRUE,
      '#title' => t('Tag'),
    );
    return $args;
  }

  public function validate(array $context) {
    if (empty($this->params['tag'])) {
      return t('A media filter tag is required');
    }
    if (!base64_decode($this->params['tag'], TRUE)) {
      return t('The tag parameter is not valid base64.');
    }

    // TODO: Also check for validity of JSON?
  }

  public function prepareView(array $context) {
    module_load_include('inc', 'media', 'includes/media.filter');
    $this->tag = base64_decode($this->params['tag']);
  }

  public function view(array $context) {
    return media_wysiwyg_token_to_markup(array($this->tag));
  }
}
