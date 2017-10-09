<?php
namespace Theapi\Datalogger;

interface InputValidatorInterface {

  /**
   * Verifies the input arguments are valid.
   * @throws /InvalidArgumentException
   */
  public function verify();

  /**
   * Add values that need to be verified.
   *
   * @param \Theapi\Datalogger\InputArgumentInterface $value
   *
   * @return \Theapi\Datalogger\InputValidatorInterface
   */
  public function addArgument(InputArgumentInterface $value);

  /**
   * @param $name
   *
   * @return \Theapi\Datalogger\InputArgumentInterface
   */
  public function getArgument($name);

}
