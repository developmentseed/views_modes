<?php

class views_modes_plugin_display_mode extends views_plugin_display {
  function is_attached_to($display_id) {
    $displays = $this->get_option('displays');
    if (!empty($displays[$display_id])) {
      return TRUE;
    }
    return FALSE;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['displays'] = array('default' => array());
    $options['mode_id'] = array('default' => '');
    $options['mode_name'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);
    $categories['mode'] = array('title' => t('Mode settings'));

    $displays = array_filter($this->get_option('displays'));
    if (count($displays) > 1) {
      $attach_to = t('Multiple displays');
    }
    else if (count($displays) == 1) {
      $display = array_shift($displays);
      if (!empty($this->view->display[$display])) {
        $attach_to = check_plain($this->view->display[$display]->display_title);
      }
    }
    if (!isset($attach_to)) {
      $attach_to = t('None');
    }

    $options['displays'] = array(
      'category' => 'mode',
      'title' => t('Attach to'),
      'value' => $attach_to,
    );
    $options['mode_id'] = array(
      'category' => 'mode',
      'title' => t('Mode ID'),
      'value' => $this->get_option('mode_id'),
    );
    $options['mode_name'] = array(
      'category' => 'mode',
      'title' => t('Name'),
      'value' => $this->get_option('mode_name'),
    );
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    switch ($form_state['section']) {
      case 'mode_id':
        $form['#title'] .= t('Mode ID');
        $form['mode_id'] = array(
          '#required' => TRUE,
          '#type' => 'textfield',
          '#default_value' => $this->get_option('mode_id'),
          '#description' => t('This ID will be used as the CSS class for display mode links.')
        );
        break;
      case 'mode_name':
        $form['#title'] .= t('Name');
        $form['mode_name'] = array(
          '#required' => TRUE,
          '#type' => 'textfield',
          '#default_value' => $this->get_option('mode_name'),
        );
        break;
      case 'displays':
        $form['#title'] .= t('Attach to');
        $displays = array();
        foreach ($this->view->display as $display_id => $display) {
          if (!empty($display->handler) && $display->handler->accept_attachments() && $display->display_plugin == 'page') {
            $displays[$display_id] = $display->display_title;
          }
        }
        $form['displays'] = array(
          '#type' => 'checkboxes',
          '#options' => $displays,
          '#default_value' => $this->get_option('displays'),
        );
        break;
    }
  }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
  function options_submit($form, &$form_state) {
    parent::options_submit($form, $form_state);
    switch ($form_state['section']) {
      case 'mode_name':
      case 'mode_id':
      case 'displays':
        $this->set_option($form_state['section'], $form_state['values'][$form_state['section']]);
        break;
    }
  }

  /**
   * Attach to another view.
   */
  function attach_to($display_id) { return; }
}
