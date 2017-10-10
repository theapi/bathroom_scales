<?php
namespace Theapi\Datalogger;

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
