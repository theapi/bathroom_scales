<?php

namespace Theapi\Datalogger;


class People implements PeopleInterface {

  /**
   * @var Config
   */
  private $config;

  private $data;

  public function __construct(Config $config) {
    $this->config = $config;
    $this->data = json_decode($config->getValue('people'));
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
