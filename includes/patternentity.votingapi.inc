<?php
/**
 * implement some vote function based on votingapi framework.
 */

function _pattern_entity_get_voting_score($pid) {
  $criteria = array(
    'entity_type' => 'patternentity',
    'entity_id' => $pid,
    'value_type' => 'points',
    'function' => 'sum',
  );
  $vote = votingapi_select_results($criteria);
  //dsm($vote);
  if ($vote) {
    return $vote[0]['value'];
  }
  else {
    return 0;
  }
}

/**
 * callback hook_menu() for /pattern/pid/voting
 */
function _pattern_entity_voting_pattern($pid) {
  $votes = array(
    'entity_type' => 'patternentity',
    'entity_id' => $pid,
    'value_type' => 'points',
    'value' => '1',
  );
  votingapi_set_votes($votes);
  drupal_goto("pattern/$pid");
}
