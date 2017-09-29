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


$data_processor = new Theapi\Datalogger\DataProcessor();
$data_processor->process(
  new Theapi\Datalogger\HttpInputHandler(),
  new Theapi\Datalogger\GoogleSheetsOutputHandler($spreadsheetId)
);
