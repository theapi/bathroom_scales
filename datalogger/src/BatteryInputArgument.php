<?php

namespace Theapi\Datalogger;

/**
 * Class BatteryInputArgument
 *
 * @package Theapi\Datalogger
 */
class BatteryInputArgument extends BaseInputArgument implements InputArgumentInterface {

  /**
   * BatteryInputArgument constructor.
   */
  public function __construct() {
    $this->setFilter(FILTER_VALIDATE_INT);
    $options = [
      'options' => [
        'min_range' => 0,
        'max_range' => 6000,
      ]
    ];
    $this->setFilterOptions($options);
  }

  /**
   * @inheritDoc
   */
  public function getName() {
    return 'Battery';
  }

}
