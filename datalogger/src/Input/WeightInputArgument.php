<?php

namespace Theapi\Datalogger\Input;

/**
 * Class WeightInputArgument
 *
 * @package Theapi\Datalogger
 */
class WeightInputArgument extends BaseInputArgument implements InputArgumentInterface {

  /**
   * @inheritDoc
   */
  public function getName() {
    return 'Weight';
  }

  /**
   * @inheritDoc
   */
  public function validate() {
    $options = [
      'options' => [
        'min_range' => 0,
        'max_range' => 1500,
      ]
    ];
    if (filter_var($this->getValue(), FILTER_VALIDATE_INT, $options) === FALSE) {
      throw new \InvalidArgumentException('Invalid ' . $this->getName());
    }
  }

}
