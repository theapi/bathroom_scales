<?php
namespace Theapi\Datalogger\Input;

interface InputArgumentInterface {

  /**
   * The name of the value.
   * @return string
   */
  public function getName();

  /**
   * Validates the input argument.
   */
  public function validate();

  /**
   * The value that needs to be verified.
   * @return self
   */
  public function setValue($value);

  /**
   * The value that needs to be verified.
   * @return mixed
   */
  public function getValue();
}
