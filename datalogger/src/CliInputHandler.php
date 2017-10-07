<?php

namespace Theapi\Datalogger;

/**
 * Class CliInputHandler
 *
 * @package Theapi\Datalogger
 */
class CliInputHandler implements InputHandlerInterface {

  protected $weight;

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
  public function getDataRow() {
    $options = getopt("w:");
    if (!isset($options['w'])) {
      throw new \InvalidArgumentException('Weight value missing, eg -w=90');
    }
    $this->weight = $options['w'];

    $this->verify();

    echo "OK\n";

    return (new DataRow())
      ->setValue('person', $this->people->getPersonByWeight($this->weight))
      ->setValue('weight', $this->weight)
      ->setValue('timestamp', date('c'));
  }

}
