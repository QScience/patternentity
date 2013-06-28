<?php

/**
 * Implements ENTITY_TYPE_form for admin UI.
 */
function patternentity_form($form, &$form_state, $patternentity) {
  $form['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#default_value' => isset($patternentity->label) ? $patternentity->label : '',
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save pattern entity'),
  );
  return $form;
}

/**
 * submit function for ENTITY_TYPE_form.
 */
function patternentity_form_submit(&$form, &$form_state) {
  $patternentity = entity_ui_form_submit_build_entity($form, $form_state);
  $patternentity->save();
  $form_state['redirect'] = 'admin/structure/patternentity';
}
