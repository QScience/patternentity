<?php

/**
 * this function return a html table. 
 * style: <div class='pattern-entity-list-table-wrap'>a table</div>
 * this is core function.
 * if it get a list table, it return the table. if not, it return false.
 * it can handle menus:
 *    pattern/uploader/$uid
 *    pattern/pid/$pid
 *    pattern/tags/field_tags_name/$tid
 *    pattern/category/[System]
 *    pattern/author/[QScience]
 * five menus.
 * these five is the basic table, a page can contain several tables. that 
 * means this function can be called any times. the output is a <div>table</div>.
 *
 */
function _pattern_entity_list($property, $arg, $operate = '=', $showupload = true) {
  drupal_add_js("misc/autocomplete.js");
  drupal_add_css(drupal_get_path('module', 'patternentity') . '/theme/patternentity.css');
  drupal_add_js(drupal_get_path('module', 'patternentity') . '/theme/jquery.autofill.min.js');
  drupal_add_js(drupal_get_path('module', 'patternentity') . '/theme/moment.min.js');
  drupal_add_js(drupal_get_path('module', 'patternentity') . '/theme/patternentity.js');

  $pos = strpos($property, 'field');
  $property_sign = $property;
  if ($pos !== false) {
    $property_sign = 'tag';
  }

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'patternentity');


  switch ($property_sign) {
    case 'uploader':
      $usr_obj = user_load($arg);
      if(!$usr_obj) {
        drupal_set_message("The pattern list doesn't exist.", "error");
        drupal_goto('all_pattern_entity_list');
      }
      drupal_set_title($property . ': '  . $usr_obj->name);
      $fieldset_title = $property . ': '  . $usr_obj->name;
      $query->propertyCondition($property, $arg, $operate);
      break;

    case 'pid':
      drupal_set_title('all patternentity:');
      $fieldset_title = 'Most Recent Patterns:';
      $query->propertyCondition($property, $arg, $operate);
      break;

    case 'tag':
      $tax = taxonomy_term_load($arg);
      drupal_set_title('tag: ' . $tax->name);
      $fieldset_title = "tag: " . $tax->name . " in $property field";
      $query->fieldCondition($property, 'tid', $arg, '=');
      break;

    default:
      drupal_set_title($property . ': ' . $arg);
      $fieldset_title = $property . ': ' . $arg;
      $query->propertyCondition($property, $arg, $operate);
  }

  $query->propertyOrderBy('created', 'DESC')
    ->pager(10)
    ->execute();
  if (isset($query->ordered_results) && count($query->ordered_results)) {
    if ($showupload) {
      $upload_button = _pattern_entity_upload_button();
    }
    else {
      $upload_button = '';
    }
    $list = "<div class='pattern-entity-list-table-wrap'><fieldset><legend>$fieldset_title$upload_button</legend><div class='fieldset-wrapper'>";
    $list .= _pattern_entity_list_page($query);
    $list .= '</div></fieldset></div>';
    return $list;
  }
  else {
    return false;
  }
}
