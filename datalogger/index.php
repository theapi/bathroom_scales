<?php
/**
 * Acknowledges a reading from the scales and updates the data log.
 *
 * Credential must have be setup with the cli script authorize_google_sheets.php
 */

use Theapi\Datalogger\Config\Config;
use Theapi\Datalogger\Data\DataLogger;
use Theapi\Datalogger\Input\BatteryInputArgument;
use Theapi\Datalogger\Input\HttpInputHandler;
use Theapi\Datalogger\Input\InputValidator;
use Theapi\Datalogger\Input\WeightInputArgument;
use Theapi\Datalogger\Output\GoogleSheetsOutputHandler;
use Theapi\Datalogger\People\People;

require_once __DIR__ . '/vendor/autoload.php';
require_once 'settings.php';


// Configuration for Google sheets.
$config = (new Config())
  ->setValue('spreadsheet_id', SPREADSHEET_ID)
  ->setValue('CREDENTIALS_PATH', CREDENTIALS_PATH)
  ->setValue('CLIENT_SECRET_PATH', CLIENT_SECRET_PATH);

$validator = (new InputValidator())
  ->addArgument(new WeightInputArgument())
  ->addArgument(new BatteryInputArgument());
$people = new People(PEOPLE);

$logger = (new DataLogger())
  ->addInputHandler(new HttpInputHandler($people, $validator))
  ->addOutputHandler(new GoogleSheetsOutputHandler($config));

try {
  $logger->run();
} catch (\InvalidArgumentException $e) {
  echo $e->getMessage() . "\n";
}
