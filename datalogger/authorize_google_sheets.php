<?php
/**
 * See https://developers.google.com/sheets/api/quickstart/php
 *
 * Download credentials from https://console.developers.google.com/apis/credentials?project=bathroom-scales
 */

use Theapi\Datalogger\GoogleSheetsOutputHandler;
use Theapi\Datalogger\People;

require_once __DIR__ . '/vendor/autoload.php';
require_once 'config.php';

if (php_sapi_name() != 'cli') {
  throw new Exception('This application must be run on the command line.');
}

$config = new Theapi\Datalogger\Config();
$config->setValue('spreadsheet_id', SPREADSHEET_ID)
  ->setValue('people', PEOPLE)
  ->setValue('CREDENTIALS_PATH', __DIR__ . '/' . CREDENTIALS_PATH)
  ->setValue('CLIENT_SECRET_PATH',  __DIR__ . '/' . CLIENT_SECRET_PATH);

$people = new People($config);
$sheets = new GoogleSheetsOutputHandler($config, $people);

// Get the API client and construct the service object.
$client = $sheets->getClient();
$service = new Google_Service_Sheets($client);

// Check authentication
$range = $people->getPersonByWeight('90') . '!A1:B';
$response = $service->spreadsheets_values->get($config->getValue('spreadsheet_id'), $range);
$values = $response->getValues();
print_r($values);

