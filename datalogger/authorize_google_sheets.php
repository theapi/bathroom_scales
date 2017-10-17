<?php
/**
 * See https://developers.google.com/sheets/api/quickstart/php
 *
 * Download credentials from
 * https://console.developers.google.com/apis/credentials?project=bathroom-scales
 */

use Theapi\Datalogger\Config\Config;
use Theapi\Datalogger\Output\GoogleSheetsOutputHandler;
use Theapi\Datalogger\People\People;

require_once __DIR__ . '/vendor/autoload.php';
require_once 'settings.php';

if (php_sapi_name() != 'cli') {
  throw new Exception('This application must be run on the command line.');
}

$config = new Config();
$config->setValue('spreadsheet_id', SPREADSHEET_ID)
  ->setValue('CREDENTIALS_PATH', CREDENTIALS_PATH)
  ->setValue('CLIENT_SECRET_PATH', CLIENT_SECRET_PATH);

$people = new People(PEOPLE);
$sheets = new GoogleSheetsOutputHandler($config);

// Get the API client and construct the service object.
$client = $sheets->getClient();
$service = new Google_Service_Sheets($client);

// Check authentication
$range = $people->getPersonByWeight('90') . '!A1:C';
$response = $service->spreadsheets_values->get($config->getValue('spreadsheet_id'), $range);
$values = $response->getValues();
print_r($values);

