<?php
/**
 * Acknowledges a reading from the scales and updates the csv data log.
 */

use Theapi\Datalogger\BatteryInputArgument;
use Theapi\Datalogger\CliInputHandler;
use Theapi\Datalogger\CsvOutputHandler;
use Theapi\Datalogger\DataProcessor;
use Theapi\Datalogger\InputValidator;
use Theapi\Datalogger\People;
use Theapi\Datalogger\WeightInputArgument;

require_once __DIR__ . '/vendor/autoload.php';
require_once 'settings.php';


// Configuration.
$config = new Theapi\Datalogger\Config();
$config->setValue('people', PEOPLE)
  ->setValue('CSV_FILE', CSV_FILE);

$validator = new InputValidator();
$validator->addArgument(new WeightInputArgument());
$validator->addArgument(new BatteryInputArgument());
$people = new People($config);
$data_processor = new DataProcessor();
$data_processor
    ->addInputHandler(new CliInputHandler($people, $validator))
    ->addOutputHandler(new CsvOutputHandler($config));

try {
  $data_processor->run();
} catch (\InvalidArgumentException $e) {
  echo $e->getMessage() . "\n";
}
