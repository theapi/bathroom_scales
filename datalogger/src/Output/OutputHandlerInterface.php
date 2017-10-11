<?php
namespace Theapi\Datalogger\Output;

use Theapi\Datalogger\Data\DataRowInterface;

/**
 * Interface OutputHandlerInterface
 *
 * @package Theapi\Datalogger
 */
interface OutputHandlerInterface {

  /**
   * @param DataRowInterface $data
   *
   * @return mixed
   */
  public function write(DataRowInterface $data);
}
