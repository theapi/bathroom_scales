<?php
namespace Theapi\Datalogger\Data;

use Theapi\Datalogger\Input\InputHandlerInterface;
use Theapi\Datalogger\Output\OutputHandlerInterface;

/**
 * Interface DataLoggerInterface
 *
 * @package Theapi\Datalogger\Data
 */
interface DataLoggerInterface {

  /**
   * @param \Theapi\Datalogger\Input\InputHandlerInterface $inputHandler
   *
   * @return self
   */
  public function addInputHandler(InputHandlerInterface $inputHandler);

  /*
   * Gets the registered input handlers.
   *
   * @return array of InputHandlerInterface
   */
  public function getInputHandlers();

  /**
   * @param \Theapi\Datalogger\Output\OutputHandlerInterface $outputHandler
   *
   * @return self
   */
  public function addOutputHandler(OutputHandlerInterface $outputHandler);

  /*
   * Gets the registered output handlers.
   *
   * @return array of OutputHandlerInterface
   */
  public function getOutputHandlers();

  /**
   * Do the data logging.
   */
  public function run();
}
