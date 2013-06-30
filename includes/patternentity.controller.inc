<?php

/**
 * customise entity controller class.
 */
class PatternEntityController extends EntityAPIController {

  /**
   * Implements EntityAPIControllerInterface.
   *
   * @param $transaction
   *   Optionally a DatabaseTransaction object to use. Allows overrides to pass
   *   in their transaction object.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {

    $entity->created = REQUEST_TIME;

    return parent::save($entity, $transaction);
  }
 
}
