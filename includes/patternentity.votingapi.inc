<?php
/**
 * implement some vote function based on votingapi framework.
 */

/**
 * used in theme/theme.inc to return a score of current pid.
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
  //$vote_score_now = _pattern_entity_get_voting_score($pid);
  //return $vote_score_now;
  
  drupal_goto("pattern/$pid");
}

/**
 * check whether certain user can vote or not.
 */
function _pattern_entity_check_whether_voted($pid) {
  global $user;
  $criteria = array(
    'entity_type' => 'patternentity',
    'entity_id' => $pid,
    'value_type' => 'points',
    'uid' => $user->uid,
    'vote_source' => ip_address(),
  );
  $votes = votingapi_select_votes($criteria);
  return count($votes);
  //dsm($votes);
  //return $votes;
}
