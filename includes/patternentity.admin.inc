<?php

/**
 * Implements ENTITY_TYPE_form for admin UI.
 * all field in table: patternentity.
 * no need care: pid, uuuid, created, updated, file_downloads, 
 * need: title, description, category, pattern, author, file_name, file_format, file_path,
 */
function patternentity_form($form, &$form_state, $patternentity) {
  $form['pattern_file'] = array(
    '#type' => 'file',
    '#title' => t('Choose a pattern file'),
    '#description' => t('Upload a file, allowed extensions: yaml, xml'),
  ); 

  dsm($patternentity);

  field_attach_form('patternentity', $patternentity, $form, $form_state);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Upload and Parser'),
  );

  return $form;
}

/**
 * validate function for ENTITY_TYPE_form
 */
function patternentity_form_validate(&$form, &$form_state) {
  $validators = array('file_validate_extensions' => array('yaml xml'));
  $file = file_save_upload('pattern_file', $validators);
  dsm($file);
  $pattern = NULL;
  $file_extension = NULL;
  if ($file) {
    $file_extension = pathinfo($file->filename, PATHINFO_EXTENSION);

    // Choose appropriate function based on the file extension.
    // Can be FALSE, if no parser is found.
    $load_function = patterns_parser_get_parser_function($file_extension, PATTERNS_PARSER_LOAD);

    // Load and save pattern.
    if (!$load_function || !($pattern = $load_function($file->uri))) {
      form_set_error('pattern_file', t('parser pattern file failed.'));
    }

    if (!patterns_validate_pattern($pattern, $file_extension, PATTERNS_VALIDATE_SYNTAX)) {
      form_set_error('pattern_file', t('pattern file has wrong syntax.'));
    }


    dsm($pattern);
  }
  else {
    form_set_error('pattern_file', t('No file was uploaded.'));
  }
  
  $form_state['values']['title'] = $pattern['info']['title'];
  $form_state['values']['description'] = $pattern['info']['description'];
  $form_state['values']['category'] = $pattern['info']['category'];
  $form_state['values']['pattern'] = $pattern;
  $form_state['values']['author'] = $pattern['info']['author'];
  Global $user;
  dsm($user);
  $form_state['values']['uploader'] = $user->uid;
  $form_state['values']['file_name'] = $file->filename;
  $form_state['values']['file_format'] = $file_extension;
  $form_state['values']['file_path'] = $file->uri;
}

/**
 * submit function for ENTITY_TYPE_form.
 */
function patternentity_form_submit(&$form, &$form_state) {
  //$file = $form_state['storage']['pattern_file'];
  //$file->status = FILE_STATUS_PERMANENT;
  //file_save($file);

  dsm($form_state);

  $patternentity = entity_ui_form_submit_build_entity($form, $form_state);
  $patternentity->save();
  $form_state['redirect'] = 'admin/structure/patternentity';
}
