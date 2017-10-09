<?php

namespace Theapi\Datalogger;

/**
 * Class WeightInputArgument
 *
 * @package Theapi\Datalogger
 */
class WeightInputArgument extends BaseInputArgument implements InputArgumentInterface {

  /**
   * WeightInputArgument constructor.
   */
  public function __construct() {
    $this->setFilter(FILTER_VALIDATE_INT);
    $options = [
      'options' => [
        'min_range' => 0,
        'max_range' => 150,
      ]
    ];
    $this->setFilterOptions($options);
  }

  /**
   * @inheritDoc
   */
  public function getName() {
    return 'Weight';
  }

}
