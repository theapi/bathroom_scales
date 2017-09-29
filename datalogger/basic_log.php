<?php
/**
 * Acknowledges a reading from the scales and updates the Google sheet.
 *
 * Credential must have be setup with the cli script authorize_google_sheets.php
 */

require_once __DIR__ . '/vendor/autoload.php';
require_once 'config.php';
require_once 'google.php';

validateInput();

// Update the sheet after sending the response.
ob_start();

// Send response.
echo "OK";

// Get the size of the output.
$size = ob_get_length();

// Disable compression (in case content length is compressed).
header("Content-Encoding: none");

// Set the content length of the response.
header("Content-Length: {$size}");

// Close the connection.
header("Connection: close");

// Flush all output.
ob_end_flush();
ob_flush();
flush();

// Now try to update the Google Sheet.

// Get the Google API client and construct the service object.
$google_client = getClient();
$google_service = new Google_Service_Sheets($google_client);

$row_data = [
  date('c'),
  (int) $_GET['w'],
];
updateSheet($google_service, $spreadsheetId, $row_data);


/**
 * If the input is no good, exit with a message.
 */
function validateInput() {
  if (!isset($_GET['w'])) {
    exit("ERROR: no weight");
  }

  $filter_options = array(
    'options' => array(
      'min_range' => 0,
      'max_range' => 150,
    )
  );
  if (filter_var($_GET['w'], FILTER_VALIDATE_INT, $filter_options) === FALSE) {
    exit("ERROR: bad weight");
  }
}

/**
 * Add data to the Google spreadsheet.
 *
 * @param Google_Service_Sheets $google_service
 * @param string $spreadsheetId
 * @param array $row_data
 *
 */
function updateSheet($google_service, $spreadsheetId, $row_data) {
  $range = 'Peter!A1:B';
  $requestBody = new Google_Service_Sheets_ValueRange();
  $requestBody->setValues(array(array_values($row_data)));
  $optParams['insertDataOption'] = 'INSERT_ROWS';
  $optParams['valueInputOption'] = 'RAW';
  try {
    $response = $google_service->spreadsheets_values->append(
      $spreadsheetId,
      $range,
      $requestBody,
      $optParams
    );
  } catch (Exception $e) {
    print $e->getMessage();
  }
}
