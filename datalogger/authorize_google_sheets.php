<?php
/**
 * See https://developers.google.com/sheets/api/quickstart/php
 *
 * Download credentials from https://console.developers.google.com/apis/credentials?project=bathroom-scales
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


if (php_sapi_name() != 'cli') {
  throw new Exception('This application must be run on the command line.');
}

$sheets = new Theapi\Datalogger\GoogleSheetsOutputHandler($spreadsheetId);

// Get the API client and construct the service object.
$client = $sheets->getClient();
$service = new Google_Service_Sheets($client);

// Check authentication
$range = 'Peter!A1:B';
$response = $service->spreadsheets_values->get($spreadsheetId, $range);
$values = $response->getValues();
print_r($values);

