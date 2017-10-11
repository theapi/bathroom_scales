<?php
namespace Theapi\Datalogger\Input;

use Theapi\Datalogger\Data\DataRowInterface;

interface InputHandlerInterface {

  /**
   * @return InputValidatorInterface
   */
  public function getValidator();

  /**
   * The verified data;
   * @return DataRowInterface
   */
  public function getDataRow();

}
