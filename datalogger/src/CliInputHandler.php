<?php

namespace Theapi\Datalogger;

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
  private $verification;

  /**
   * CsvIputHandler constructor.
   *
   * @param \Theapi\Datalogger\PeopleInterface $people
   */
  public function __construct(PeopleInterface $people, InputValidatorInterface $verification) {
    $this->people = $people;
    $this->verification = $verification;
  }

  /**
   * @inheritdoc
   */
  public function getVerification() {
    return $this->verification;
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
    $this->getVerification()->getArgument('Weight')->setValue($weight);

    if (!isset($options['b'])) {
      throw new \InvalidArgumentException('Battery voltage value missing, eg -b=3700');
    }
    $battery = $options['b'];
    $this->getVerification()->getArgument('Battery')->setValue($battery);

    $this->getVerification()->verify();

    echo "OK\n";

    return (new DataRow())
      ->setPerson($this->people->getPersonByWeight($weight))
      ->setWeight($weight)
      ->setBattery($battery)
      ->setTimestamp();
  }

}
