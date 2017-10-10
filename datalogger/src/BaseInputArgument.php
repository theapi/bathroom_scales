<?php

namespace Theapi\Datalogger;


abstract class BaseInputArgument implements InputArgumentInterface {

  protected $value;

  protected $options;

  protected $filter;

  /**
   * @inheritDoc
   */
  public function setValue($value) {
    $this->value = $value;

    return $this;
  }

  /**
   * @inheritDoc
   */
  public function getValue() {
    return $this->value;
  }

}
