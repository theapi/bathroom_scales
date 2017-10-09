<?php

namespace Theapi\Datalogger;

/**
 * Class HttpInputHandler
 *
 * @package Theapi\Datalogger
 */
class HttpInputHandler implements InputHandlerInterface {

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
    if (!isset($_GET['w'])) {
      throw new \InvalidArgumentException('Weight value missing');
    }
    $weight = (int) $_GET['w'];

    if (!isset($_GET['b'])) {
      throw new \InvalidArgumentException('Battery voltage value missing');
    }
    $battery = (int) $_GET['b'];

    $this->getVerification()->getArgument('Weight')->setValue($weight);
    $this->getVerification()->getArgument('Battery')->setValue($battery);

    $this->getVerification()->verify();

    // Tell the client immediately that the message was received.
    ob_start();

    // Send response.
    echo "OK";

    // Get the size of the output.
    $size = ob_get_length();

    // Disable compression (in case content length is compressed).
    header("Content-Encoding: none");

    // Set the content length of the response.
    header("Content-Length: {$size}");

    // Close the connection.
    header("Connection: close");

    // Flush all output.
    ob_end_flush();
    ob_flush();
    flush();

    return (new DataRow())
      ->setPerson($this->people->getPersonByWeight($weight))
      ->setWeight($weight)
      ->setBattery($battery)
      ->setTimestamp();
  }

}
