<?php

namespace Theapi\Datalogger;


class CliInputHandler implements InputHandlerInterface {

  /**
   * @inheritdoc
   */
  public function verify() {

    if (!isset($this->weight)) {
      throw new \InvalidArgumentException('Weight value missing');
    }

    $filter_options = array(
      'options' => array(
        'min_range' => 0,
        'max_range' => 150,
      )
    );
    if (filter_var($this->weight, FILTER_VALIDATE_INT, $filter_options) === FALSE) {
      throw new \InvalidArgumentException('Invalid weight');
    }
  }

  /**
   * @inheritdoc
   */
  public function getInput() {
    $options = getopt("w:");
    $this->weight = $options['w'];

    $this->verify();

    echo "OK\n";

    return [
      'weight' => (int) $this->weight,
      'timestamp' => date('c'),
    ];
  }

}
