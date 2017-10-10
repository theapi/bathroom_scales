<?php

namespace Theapi\Datalogger;


class InputValidator implements InputValidatorInterface {

  private $data = array();

  /**
   * @inheritDoc
   */
  public function addArgument(InputArgumentInterface $value) {
    $this->data[$value->getName()] = $value;

    return $this;
  }

  public function getArgument($name) {
    if (isset($this->data[$name])) {
      return $this->data[$name];
    }
    throw new \InvalidArgumentException("Argument not set: $name");
  }

  public function validate() {
    foreach($this->data as $arg) {
      $arg->validate();
    }
  }

  /**
   * @inheritDoc
   */
  public function verify() {
    foreach($this->data as $arg) {
      if (filter_var($arg->getValue(), $arg->getFilter(), $arg->getFilterOptions()) === FALSE) {
        throw new \InvalidArgumentException('Invalid ' . $arg->getName());
      }
    }
  }

}
