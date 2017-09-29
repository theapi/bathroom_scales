<?php

namespace Theapi\Datalogger;


class DataProcessor implements DataProcessorInterface {

  /**
   * @inheritdoc
   */
  public function process(InputHandlerInterface $inputHandler, OutputHandlerInterface $outputHandler) {
    $outputHandler->write($inputHandler->getInput());
  }

}
