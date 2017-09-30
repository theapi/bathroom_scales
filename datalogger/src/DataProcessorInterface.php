<?php
namespace Theapi\Datalogger;

interface DataProcessorInterface {

    public function addInputHandler(InputHandlerInterface $inputHandler);

    public function getInputHandlers();

    public function addOutputHandler(OutputHandlerInterface $outputHandler);

    public function getOutputHandlers();

    public function run();
}
