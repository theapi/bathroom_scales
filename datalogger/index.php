<?php
/**
 * Acknowledges a reading from the scales and updates the data log.
 *
 * Credential must have be setup with the cli script authorize_google_sheets.php
 */

require_once __DIR__ . '/vendor/autoload.php';
require_once 'config.php';

// PSR-4 autoloader
spl_autoload_register(function ($class) {
  if (strpos($class, 'Theapi\Datalogger') === 0) {
    if (file_exists((__DIR__ . '/src/' . str_replace('\\', '/', $class) . '.php'))) {
      include(__DIR__ . '/src/' . str_replace('\\', '/', $class) . '.php');
    }
  }
});

// Configuration for Google sheets.
$config = new Theapi\Datalogger\Config();
$config->setValue('spreadsheet_id', SPREADSHEET_ID)
  ->setValue('people', PEOPLE)
  ->setValue('CREDENTIALS_PATH', __DIR__ . '/' . CREDENTIALS_PATH)
  ->setValue('CLIENT_SECRET_PATH',  __DIR__ . '/' . CLIENT_SECRET_PATH);

$people = new Theapi\Datalogger\People($config);
$data_processor = new Theapi\Datalogger\DataProcessor();
$data_processor->process(
  new Theapi\Datalogger\HttpInputHandler(),
  new Theapi\Datalogger\GoogleSheetsOutputHandler(
    $config,
    new Theapi\Datalogger\People($config)
  )
);
