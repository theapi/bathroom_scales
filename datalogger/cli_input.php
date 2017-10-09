<?php
/**
 * Acknowledges a reading from the scales and updates the data log.
 *
 * Credential must have be setup with the cli script authorize_google_sheets.php
 */

use Theapi\Datalogger\BatteryInputArgument;
use Theapi\Datalogger\CliInputHandler;
use Theapi\Datalogger\DataProcessor;
use Theapi\Datalogger\GoogleSheetsOutputHandler;
use Theapi\Datalogger\InputValidator;
use Theapi\Datalogger\People;
use Theapi\Datalogger\WeightInputArgument;

require_once __DIR__ . '/vendor/autoload.php';
require_once 'settings.php';


// Configuration for Google sheets.
$config = new Theapi\Datalogger\Config();
$config->setValue('spreadsheet_id', SPREADSHEET_ID)
  ->setValue('people', PEOPLE)
  ->setValue('CREDENTIALS_PATH', CREDENTIALS_PATH)
  ->setValue('CLIENT_SECRET_PATH', CLIENT_SECRET_PATH);

$validator = new InputValidator();
$validator->addArgument(new WeightInputArgument());
$validator->addArgument(new BatteryInputArgument());
$people = new People($config);
$data_processor = new DataProcessor();
$data_processor
    ->addInputHandler(new CliInputHandler($people, $validator))
    ->addOutputHandler(new GoogleSheetsOutputHandler($config));

try {
  $data_processor->run();
} catch (\InvalidArgumentException $e) {
  echo $e->getMessage() . "\n";
}
