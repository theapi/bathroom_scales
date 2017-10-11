<?php
/**
 * Acknowledges a reading from the scales and updates the csv data log.
 */

use Theapi\Datalogger\Data\DataLogger;
use Theapi\Datalogger\Input\BatteryInputArgument;
use Theapi\Datalogger\Input\CliInputHandler;
use Theapi\Datalogger\Input\InputValidator;
use Theapi\Datalogger\Input\WeightInputArgument;
use Theapi\Datalogger\Output\CsvOutputHandler;
use Theapi\Datalogger\People\People;

require_once __DIR__ . '/vendor/autoload.php';
require_once 'settings.php';

$validator = (new InputValidator())
  ->addArgument(new WeightInputArgument())
  ->addArgument(new BatteryInputArgument());
$people = new People(PEOPLE);

$logger = (new DataLogger())
  ->addInputHandler(new CliInputHandler($people, $validator))
  ->addOutputHandler(new CsvOutputHandler(CSV_FILE));

try {
  $logger->run();
} catch (\InvalidArgumentException $e) {
  echo $e->getMessage() . "\n";
}
