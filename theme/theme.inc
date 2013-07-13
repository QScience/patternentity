<?php

/**
 * theme the 'pattern' field in 'patternentity' table.
 */
function _pattern_entity_parser_field_pattern($pattern)  {
  $content_this = NULL;
  foreach ($pattern as $key => $value) {
    if (is_numeric($key) && is_array($value)) {

              $value_keys = array_keys($value);
              foreach ($value_keys as $_key => $_value) {
                $content_this .= '<li >' . '- <span class="yaml_aa5500">' . $_value . '</span> :' ;
                if (is_array($value[$_value])) {
                  $content_this .= '</li><ul>';
                  $content_this .= _pattern_entity_parser_field_pattern($value[$_value]);
                }
                else {
                  $content_this .= '<span class="yaml_116644">' . $value[$_value] . '</spn>';
                  $content_this .= '</li><ul>';
                }
                $content_this .= '</ul>';
              }

    }
    elseif (!is_numeric($key) && is_array($value)) {
      $content_this .= '<li><span class="yaml_aa5500">' . $key . '</span> :' . '</li><ul>';
      $content_this .= _pattern_entity_parser_field_pattern($value);
      $content_this .= '</ul>';
    }
    elseif (is_numeric($key) && !is_array($value)) {
      $content_this .= '<li>' . '- <span class="yaml_116644">' . $value . '</span></li>';
    }
    else {
      $content_this .= '<li><span class="yaml_aa5500">' . $key . '</span> : <span class="yaml_221199">' . $value . '</span></li>';
    }
  }
  return $content_this;
}

/**
 * theme pattern description part
 */
function _pattern_entity_view_pattern_description($pe) {
  $content = '<div id="patternentity-page-pattern-description"><dl class="dl-horizontal">';
  $content .= '<dt>title</dt><dd>' . $pe->title . '</dd>';
  $content .= '<dt>description</dt><dd>' . $pe->description. '</dd>';
  $content .= '<dt>category</dt><dd>' . $pe->category. '</dd>';
  $content .= '<dt>author</dt><dd>' . $pe->author. '</dd>';
  $content .= '<dt>uploader</dt><dd>' . $pe->uploader. '</dd>';
  $content .= '<dt>file name</dt><dd>' . $pe->file_name. '</dd>';
  $content .= '</dl></div>';
  return $content;
}

/**
 * theme pattern list page.
 */
function _pattern_entity_list_page($query) {
  $header = array(
    t('Title'),
    t('Category'),
    t('Author'),
    t('Uploader'),
    t('Downloads'),
    t('Score'),
    t('File'),
    t('Like'),
  );
  $ids = array();
  foreach($query->ordered_results as $value) {
    $ids[] = $value->entity_id;
  }
  $entitys = entity_load('patternentity', $ids);
  dsm($entitys);
  $rows = array();
  foreach($entitys as $ety_obj) {
    $rows[] = _pattern_entity_list_table_row($ety_obj);
  }
  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('pattern-entity-list-table'))));
}

/**
 * generate pattern list table row.
 * used by _pattern_entity_list_page($query).
 */
function _pattern_entity_list_table_row($ety_obj) {
  $row = array();
  
  $row[] = l($ety_obj->title, '/pattern/' . $ety_obj->pid);
  $row[] = l($ety_obj->category, '/pattern/category/' . $ety_obj->category);
  $row[] = l($ety_obj->author, '/pattern/author/' . $ety_obj->author);
  $usr_obj = user_load($ety_obj->uploader);
  $row[] = l($usr_obj->name , '/pattern/uploader/' . $ety_obj->uploader);
  $row[] = $ety_obj->file_downloads;
  $row[] = 0;
  $row[] = l(t('download'), '/pattern/' . $ety_obj->pid . '/download', array('attributes' => array('class' => 'download-link')));
  $row[] = 0;

  return $row;
}
