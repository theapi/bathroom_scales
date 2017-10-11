<?php
namespace Theapi\Datalogger\Input;

interface InputValidatorInterface {

  /**
   * Verifies the input arguments are valid.
   * @throws /InvalidArgumentException
   */
  public function validate();

  /**
   * Add values that need to be verified.
   *
   * @param InputArgumentInterface $value
   *
   * @return InputValidatorInterface
   */
  public function addArgument(InputArgumentInterface $value);

  /**
   * @param $name
   *
   * @return \Theapi\Datalogger\InputArgumentInterface
   */
  public function getArgument($name);

}
