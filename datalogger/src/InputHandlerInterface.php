<?php
namespace Theapi\Datalogger;

interface InputHandlerInterface {

  /**
   * @return InputValidatorInterface
   */
  public function getVerification();

  /**
   * The verified data;
   * @return DataRowInterface
   */
  public function getDataRow();

}
