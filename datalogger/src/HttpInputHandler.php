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
    if (!isset($_GET['w'])) {
      throw new \InvalidArgumentException('Weight value missing');
    }

    if (!isset($_GET['b'])) {
      throw new \InvalidArgumentException('Battery voltage value missing');
    }

    $filter_options = array(
      'options' => array(
        'min_range' => 0,
        'max_range' => 150,
      )
    );
    if (filter_var($_GET['w'], FILTER_VALIDATE_INT, $filter_options) === FALSE) {
      throw new \InvalidArgumentException('Invalid weight');
    }
    if (filter_var($_GET['b'], FILTER_VALIDATE_INT) === FALSE) {
      throw new \InvalidArgumentException('Invalid battery voltage');
    }
  }

  /**
   * @inheritdoc
   */
  public function getDataRow() {
    $this->verify();

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

    $weight = (int) $_GET['w'];
    return (new DataRow())
      ->setPerson($this->people->getPersonByWeight($weight))
      ->setWeight($weight)
      ->setBattery((int) $_GET['b'])
      ->setTimestamp();
  }

}
