<?php
namespace Theapi\Datalogger;

interface DataProcessorInterface {

  public function process(InputHandlerInterface $inputHandler, OutputHandlerInterface $outputHandler);
}
