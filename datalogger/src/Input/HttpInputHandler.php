<?php

namespace Theapi\Datalogger\Input;

use Theapi\Datalogger\Data\DataRow;
use Theapi\Datalogger\People\PeopleInterface;


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

    if (!isset($_GET['w'])) {
      $msg = 'Weight value missing';
    }
    if (!isset($_GET['b'])) {
      $msg = 'Battery voltage value missing';
    }

    if (!isset($msg)) {
      $msg = 'OK';
      $weight = (int) $_GET['w'];
      $battery = (int) $_GET['b'];
      $this->getValidator()->getArgument('Weight')->setValue($weight);
      $this->getValidator()->getArgument('Battery')->setValue($battery);
      try {
        $this->getValidator()->validate();
      } catch (\InvalidArgumentException $e) {
        $msg = $e->getMessage();
      }
    }

    // Tell the client immediately that the message was received.
    ob_start();

    // Send response.
    echo $msg;

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

    if (isset($weight) && isset($battery)) {
      return (new DataRow())
        ->setPerson($this->people->getPersonByWeight($weight))
        ->setWeight($weight)
        ->setBattery($battery)
        ->setTimestamp();
    }

    throw new \InvalidArgumentException($msg);
  }

}
