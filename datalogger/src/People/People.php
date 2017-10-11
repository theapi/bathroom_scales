<?php

namespace Theapi\Datalogger\People;

/**
 * Class People
 *
 * @package Theapi\Datalogger\People
 */
class People implements PeopleInterface {

  private $data;

  /**
   * People constructor.
   *
   * @param $json
   */
  public function __construct($json) {
    $this->data = json_decode($json);
  }

  /**
   * @inheritdoc
   */
  public function getPersonByWeight($weight) {
    reset($this->data);
    foreach ($this->data as $person) {
      if ($person[1] < $weight && $weight < $person[2]) {
        return $person[0];
      }
    }

    return $this->data[0];
  }

}
