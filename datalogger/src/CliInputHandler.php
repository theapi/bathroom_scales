<?php

namespace Theapi\Datalogger;

/**
 * Class CliInputHandler
 *
 * @package Theapi\Datalogger
 */
class CliInputHandler implements InputHandlerInterface {

  protected $weight;

  protected $battery;

  /**
   * @var PeopleInterface
   */
  private $people;

  /**
   * CsvIputHandler constructor.
   *
   * @param \Theapi\Datalogger\PeopleInterface $people
   */
  public function __construct(PeopleInterface $people) {
    $this->people = $people;
  }

  /**
   * @inheritdoc
   */
  public function verify() {

    $filter_options = array(
      'options' => array(
        'min_range' => 0,
        'max_range' => 150,
      )
    );
    if (filter_var($this->weight, FILTER_VALIDATE_INT, $filter_options) === FALSE) {
      throw new \InvalidArgumentException('Invalid weight');
    }
    if (filter_var($this->battery, FILTER_VALIDATE_INT) === FALSE) {
      throw new \InvalidArgumentException('Invalid battery voltage');
    }
  }

  /**
   * @inheritdoc
   */
  public function getDataRow() {
    $options = getopt("w:b:");
    if (!isset($options['w'])) {
      throw new \InvalidArgumentException('Weight value missing, eg -w=90');
    }
    $this->weight = $options['w'];

    if (!isset($options['b'])) {
      throw new \InvalidArgumentException('Battery voltage value missing, eg -b=3700');
    }
    $this->battery = $options['b'];

    $this->verify();

    echo "OK\n";

    return (new DataRow())
      ->setPerson($this->people->getPersonByWeight($this->weight))
      ->setWeight($this->weight)
      ->setBattery($this->battery)
      ->setTimestamp();
  }

}
