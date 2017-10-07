<?php
namespace Theapi\Datalogger;

interface InputHandlerInterface {

  /**
   * Verifies the input arguments are valid.
   * @throws /InvalidArgumentException
   */
  public function verify();

  /**
   * The verified data;
   * @return DataRowInterface
   */
  public function getDataRow();

}
