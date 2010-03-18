<?php

class views_modes_context_condition_views_modes extends context_condition {

  /**
   * Generate a list of database and module provided views.
   */
  function condition_values() {
    $options = array();

    $options['default'] = "Default";
    $views = views_get_all_views();
    foreach ($views as $view) {
      foreach ($view->display as $display_id => $display) {
        if ($display->display_plugin == 'mode') {
          if (!empty($display->display_options['mode_id']) && !empty($display->display_options['mode_name'])) {
            $mode_id = $display->display_options['mode_id'];
            $mode_name = $display->display_options['mode_name'];
            $options[$mode_id] = $mode_name;
          }
        }
      }
    }

    return $options;
  }

  function execute($mode) {
    $contexts = $this->get_contexts($mode);
    foreach ($contexts as $context) {
      $this->condition_met($context, $mode);
    }
  }
}
