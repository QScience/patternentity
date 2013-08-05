<?php

/**
 * this function return a html table. 
 * style: <div class='pattern-entity-list-table-wrap'>a table</div>
 * this is core function.
 * if it get a list table, it return the table. if not, it return false.
 * it can handle menus:
 *    pattern/uploader/$uid ====> $property: uploader, $arg: $uid.
 *    pattern/tags/$field_tags_name/$tid ====> $property: field_tags_name, $arg: $tid.
 *    pattern/category/[System] ====> $property: category, $arg: [System].
 *    pattern/author/[QScience] ====> $property: author, $arg: [QScience].
 * if can hanndle another pid $property and $pid $arg. 
 * all five kinds of property: four menus and the special pid $property.
 *
 * these five is the basic table, a page can contain several tables. that 
 * means this function can be called any times. the output is a <div>table</div>.
 *
 */
function _pattern_entity_list($property, $arg, $operate = '=', $showupload = true) {

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
    $list = _pattern_entity_list_page($query, $fieldset_title);
    return $list;
  }
  else {
    return false;
  }
}

/**
 * callback hook_menu() for /pattern/search/arg1/arg2 path
 * search type: title, category, author, uuid, tags. five types.
 * this is a core function.
 */
function _pattern_entity_search($selected, $value) {

  drupal_set_title('search :');
  drupal_add_js(drupal_get_path('module', 'patternentity') . '/styles/js/patternentity.search.js');
  $form = drupal_get_form('patternentity_search', $selected, $value);
  $list = drupal_render($form);

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'patternentity');
  switch ($selected) {
    case 0:
      $query->propertyCondition('title', '%' . db_like($value) . '%', 'LIKE');
      $fieldset_title = "pattern with title: $value";
      break;
    case 1:
      $query->propertyCondition('category', '%' . db_like($value) . '%', 'LIKE');
      $fieldset_title = "pattern in category: $value";
      break;
    case 2:
      $query->propertyCondition('author', '%' . db_like($value) . '%', 'LIKE');
      $fieldset_title = "pattern of author: $value";
      break;
    case 3:
      $query->propertyCondition('uuuid', '%' . db_like($value) . '%', 'LIKE');
      $fieldset_title = "pattern with uuuid: $value";
      break;
    case 4:
      $query->propertyCondition('pid', $value, '=');
      $fieldset_title = "pattern with pid: $value";
      break;
    case 5:
      $tagtids = _pattern_entity_findtagtid_by_tagname($value);
      dsm($tagtids);
      $tags_table_db = _pattern_entity_get_all_taxonomyfields_name('patternentity');
      dsm($tags_table_db);
      //$entity_ids = _pattern_entity_findentityid_by_tagvid($tagtids, $tags_table_db);
      //$entity_ids = array_keys($entity_ids);
      //if (count($entity_ids) == 0) {
      //  $entity_ids = array('-1');
      //}
      //$query->propertyCondition('pid', $entity_ids);
      $fieldset_title = "pattern with tag: $value";
      if (count($tags_table_db) && count($tagtids)) {
        foreach($tags_table_db as $field_name) {
          foreach ($tagtids as $tid => $_temp) {
            $list .= _pattern_entity_list($field_name, $tid);
          }
        }
      }
      else {
        $list .= t('no search result.');
      }
      return $list;
      break;
  }
  
  $query->propertyOrderBy('created', 'DESC')
    ->pager(10)
    ->execute();

  if (isset($query->ordered_results) && count($query->ordered_results)) {
    $list = _pattern_entity_list_page($query, $fieldset_title);
  }
  else {
    $list = t('no search result.');
  }
  return $list;
}
