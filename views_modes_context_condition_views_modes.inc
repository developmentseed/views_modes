<?php
// $Id: context_condition_views.inc,v 1.1.2.1 2009/12/14 22:34:05 yhahn Exp $

class views_modes_context_condition_views_modes extends context_condition {

  /**
   * Generate a list of database and module provided views.
   */
  function condition_values() {
    $options = array();

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
    $this->values[$mode] = array();
    foreach ($contexts as $context) {
      $this->values[$mode][] = $context->name;
      context_set('context', $context->name, $context);
    }
  }
}
