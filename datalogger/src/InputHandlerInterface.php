<?php
namespace Theapi\Datalogger;

interface InputHandlerInterface {

  /**
   * Verifies the input arguments are valid.
   * @throws /InvalidArgumentException
   */
  public function verify();

  /**
   * The verified input;
   * @return array
   */
  public function getInput();

}
