<?php
namespace Theapi\Datalogger;

interface DataloggerInterface {

  /**
   * The class that collects the input.
   * @param InputHandlerInterface $inputHandler
   *
   * @return self
   */
  public function setInputHandler(InputHandlerInterface $inputHandler);

  /**
   * @return InputHandlerInterface
   */
  public function getInputHandler();

  /**
   * The class that saves the data.
   * @param OutputHandlerInterface $outputHandler
   *
   * @return mixed
   */
  public function setOutputHandler(OutputHandlerInterface $outputHandler);

  /**
   * @return OutputHandlerInterface
   */
  public function getOutputHandler();
}
