<?php

namespace Theapi\Datalogger\Input;

/**
 * Class BatteryInputArgument
 *
 * @package Theapi\Datalogger
 */
class BatteryInputArgument extends BaseInputArgument implements InputArgumentInterface {

  /**
   * @inheritDoc
   */
  public function getName() {
    return 'Battery';
  }

  /**
   * @inheritDoc
   */
  public function validate() {
    $options = [
      'options' => [
        'min_range' => 0,
        'max_range' => 6000,
      ]
    ];
    if (filter_var($this->getValue(), FILTER_VALIDATE_INT, $options) === FALSE) {
      throw new \InvalidArgumentException('Invalid ' . $this->getName());
    }
  }

}
