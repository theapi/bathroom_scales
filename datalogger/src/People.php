<?php

namespace Theapi\Datalogger;


class People implements PeopleInterface {

  private $data;

  public function __construct($json) {
    $this->data = json_decode($json);
  }

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
