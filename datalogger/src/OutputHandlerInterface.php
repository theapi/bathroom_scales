<?php
namespace Theapi\Datalogger;

/**
 * Interface OutputHandlerInterface
 *
 * @package Theapi\Datalogger
 */
interface OutputHandlerInterface {

  /**
   * @param \Theapi\Datalogger\DataRowInterface $data
   *
   * @return mixed
   */
  public function write(DataRowInterface $data);
}
