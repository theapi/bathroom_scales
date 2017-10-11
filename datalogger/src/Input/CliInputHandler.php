<?php

namespace Theapi\Datalogger\Input;

use Theapi\Datalogger\Data\DataRow;
use Theapi\Datalogger\People\PeopleInterface;

/**
 * Class CliInputHandler
 *
 * @package Theapi\Datalogger
 */
class CliInputHandler implements InputHandlerInterface {

  /**
   * @var PeopleInterface
   */
  private $people;

  /**
   * @var InputValidatorInterface
   */
  private $validator;

  /**
   * CsvIputHandler constructor.
   *
   * @param PeopleInterface $people
   */
  public function __construct(PeopleInterface $people, InputValidatorInterface $validator) {
    $this->people = $people;
    $this->validator = $validator;
  }

  /**
   * @inheritdoc
   */
  public function getValidator() {
    return $this->validator;
  }

  /**
   * @inheritdoc
   */
  public function getDataRow() {
    $options = getopt("w:b:");
    if (!isset($options['w'])) {
      throw new \InvalidArgumentException('Weight value missing, eg -w=90');
    }
    $weight = $options['w'];
    $this->getValidator()->getArgument('Weight')->setValue($weight);

    if (!isset($options['b'])) {
      throw new \InvalidArgumentException('Battery voltage value missing, eg -b=3700');
    }
    $battery = $options['b'];
    $this->getValidator()->getArgument('Battery')->setValue($battery);

    $this->getValidator()->validate();

    echo "OK\n";

    return (new DataRow())
      ->setPerson($this->people->getPersonByWeight($weight))
      ->setWeight($weight)
      ->setBattery($battery)
      ->setTimestamp();
  }

}
