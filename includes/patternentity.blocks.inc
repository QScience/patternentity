<?php

/**
 * build several blocks for patternentity.
 */

/**
 * most prolific author 
 * used by patternentity_block_view.
 */
function _pattern_entity_block_most_prolific_author() {
  drupal_add_css(drupal_get_path('module', 'patternentity') . '/styles/css/patternentity.block.css');
  $result = array();
  $result['type'] = "ul";
  $result['attributes'] = array('class' => 'patternentity-most-prolific-authors');


  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'patternentity')
    ->execute();

  $authors_score = array();
  if (isset($query->ordered_results) && count($query->ordered_results)) {
    foreach($query->ordered_results as $value) {
      $ids[] = $value->entity_id;
    }
    $entities = entity_load('patternentity', $ids);
    foreach($entities as $pe) {
      $pe->author = strtolower($pe->author);
      if (isset($authors_score[$pe->author])) {
        $authors_score[$pe->author]++;
      }
      else {
        $authors_score[$pe->author] = 1;
      }
    }
  }
  if (!count($authors_score)) {
    return t('no available authors.');
  }
  arsort($authors_score);
  $authors_score = array_slice($authors_score, 0, 10, true);

  $items = array();
  foreach ($authors_score as $author => $score) {
    $items[] = array(
      'data' => l($author, 'pattern/author/' . $author) . ' × ' . $score,
    );
  }

  $result['items'] = $items;

  return theme('item_list', $result);

}

/**
 * hottest tags
 * used by patternentity_block_view.
 */
function _pattern_entity_block_hottest_tags() {
  drupal_add_css(drupal_get_path('module', 'patternentity') . '/styles/css/patternentity.block.css');
  $result = array();
  $result['type'] = "ul";
  $result['attributes'] = array('class' => 'patternentity-most-popular-tags');

  //get all tags field for patternentity.
  $tags_table_db = array();
  $fields_info = field_info_instances('patternentity');
  if (isset($fields_info['patternentity']) && count($fields_info['patternentity'])) {
    $fields_info = $fields_info['patternentity'];
    foreach ($fields_info as $field_name => $_value) {
      $field_info = field_info_field($field_name);
      if ($field_info['type'] == 'taxonomy_term_reference') {
        $tags_table_db[] = $field_name;
      }
    }
  }
  //dsm($tags_table_db);
  if (!count($tags_table_db)) {
    return t('no available tags.');
  }
  
  $query = array();
  foreach ($tags_table_db as $table) {
    $table_name = 'field_data_' . $table;
    $query[$table] = db_select($table_name)
      ->fields($table_name, array($table . '_tid'))
      ->execute()
      ->fetchAll();
  }
 // dsm($query);

  $tags_score = array();
  foreach ($query as $tb => $value) {
    $key = $tb . '_tid';
    foreach ($value as $tag) {
      if (isset($tags_score[$tag->$key])) {
        $tags_score[$tag->$key]['score']++;
      }
      else {
        $tags_score[$tag->$key]['score'] = 1;
        $tags_score[$tag->$key]['table'] = $tb;
      }
    }
  }
  arsort($tags_score);
  $tags_score = array_slice($tags_score, 0, 10, true);

  $items = array();
  foreach ($tags_score as $tid => $score_tb) {
    $tagname = _pattern_entity_tagname_by_tagid($tid);
    $items[] = array(
      'data' => l($tagname['name'], 'pattern/alltags/' . $tid) . ' × ' . $score_tb['score'],
    );
  }

  $result['items'] = $items;

  return theme('item_list', $result);
}

/**
 * find vocabulary by tags id.
 */
function _pattern_entity_tagname_by_tagid($tagid) {
  $name = db_select('taxonomy_term_data', 'ttd')
    ->fields('ttd', array('name'))
    ->condition('tid', $tagid)
    ->execute()
    ->fetchAssoc();
  
  return $name;
}

/**
 * get an entity's all taxonomy fields' name.
 */
function _pattern_entity_get_all_taxonomyfields_name($entity_type) {
 
  //get all tags field for patternentity.
  $tags_table_db = array();
  $fields_info = field_info_instances($entity_type);
  if (isset($fields_info[$entity_type]) && count($fields_info[$entity_type])) {
    $fields_info = $fields_info[$entity_type];
    foreach ($fields_info as $field_name => $_value) {
      $field_info = field_info_field($field_name);
      if ($field_info['type'] == 'taxonomy_term_reference') {
        $tags_table_db[] = $field_name;
      }
    }
  }
  if (!count($tags_table_db)) {
    return false;
  }
  else {
    return $tags_table_db;
  }
}
