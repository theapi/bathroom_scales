<?php

namespace Theapi\Datalogger;


class DataProcessor implements DataProcessorInterface {

    protected $inputHandlers = array();

    protected $outputHandlers = array();

    /**
     * @inheritdoc
     */
    public function addInputHandler(InputHandlerInterface $inputHandler) {
        $this->inputHandlers[] = $inputHandler;

        return $this;
    }

    /**
     * @inheritdoc
     */
    public function getInputHandlers() {
        return $this->inputHandlers;
    }


    /**
     * @inheritdoc
     */
    public function addOutputHandler(OutputHandlerInterface $outputHandler) {
        $this->outputHandlers[] = $outputHandler;

        return $this;
    }

    /**
     * @inheritdoc
     */
    public function getOutputHandlers() {
        return $this->outputHandlers;
    }

    /**
     * @inheritdoc
     */
    public function run() {
        $inputs = $this->getInputHandlers();
        $outputs = $this->getOutputHandlers();
        foreach($inputs as $input) {
            foreach ($outputs as $output) {
                $output->write($input->getDataRow());
            }
        }
    }

}
