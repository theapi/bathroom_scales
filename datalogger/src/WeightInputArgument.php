<?php

namespace Theapi\Datalogger;

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
        'max_range' => 150,
      ]
    ];
    if (filter_var($this->getValue(), FILTER_VALIDATE_INT, $options) === FALSE) {
      throw new \InvalidArgumentException('Invalid ' . $this->getName());
    }
  }

}
