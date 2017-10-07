<?php
namespace Theapi\Datalogger;

use Google_Service_Sheets;
use Google_Service_Sheets_ValueRange;

define('APPLICATION_NAME', 'Google Sheets API');
// If modifying these scopes, delete the previously saved credentials
// at ~/.credentials/sheets.googleapis.com-php-bathroom_scales.json
define('SCOPES', implode(' ', array(
    Google_Service_Sheets::SPREADSHEETS)
));

/**
 * Class GoogleSheetsOutputHandler
 *
 * @package Theapi\Datalogger
 */
class GoogleSheetsOutputHandler implements OutputHandlerInterface {

  /**
   * @var Config
   */
  private $config;

  /**
   * GoogleSheetsOutputHandler constructor.
   *
   * @param $config
   */
  public function __construct($config) {
    $this->config = $config;
  }

  /**
   * @inheritdoc
   */
  public function write(DataRowInterface $data) {
    // Get the Google API client and construct the service object.
    $google_client = $this->getClient();
    $google_service = new Google_Service_Sheets($google_client);
    $this->updateSheet($google_service, $this->config->getValue('spreadsheet_id'), $data);
  }

  /**
   * Add data to the Google spreadsheet.
   *
   * @param Google_Service_Sheets $google_service
   * @param string $spreadsheet_id
   * @param DataRowInterface $row_data
   *
   */
  public function updateSheet($google_service, $spreadsheet_id, DataRowInterface $row_data) {
    $range = $row_data->person() . '!A1:C';
    $requestBody = new Google_Service_Sheets_ValueRange();
    $requestBody->setValues([
      [
        $row_data->timestamp(),
        $row_data->weight(),
        $row_data->battery(),
      ]
    ]);
    $optParams['insertDataOption'] = 'INSERT_ROWS';
    $optParams['valueInputOption'] = 'RAW';
    try {
      $response = $google_service->spreadsheets_values->append(
        $spreadsheet_id,
        $range,
        $requestBody,
        $optParams
      );
    } catch (\Exception $e) {
      print $e->getMessage();
    }
  }

  /**
   * Returns an authorized API client.
   * @return \Google_Client the authorized client object
   */
  public function getClient() {
    $client = new \Google_Client();
    $client->setApplicationName(APPLICATION_NAME);
    $client->setScopes(SCOPES);
    $client->setAuthConfig($this->config->getValue('CLIENT_SECRET_PATH'));
    $client->setAccessType('offline');

    // Load previously authorized credentials from a file.
    $credentialsPath = $this->config->getValue('CREDENTIALS_PATH');
    if (file_exists($credentialsPath)) {
      $accessToken = json_decode(file_get_contents($credentialsPath), true);
    } else {
      // Request authorization from the user.
      $authUrl = $client->createAuthUrl();
      printf("Open the following link in your browser:\n%s\n", $authUrl);
      print 'Enter verification code: ';
      $authCode = trim(fgets(STDIN));

      // Exchange authorization code for an access token.
      $accessToken = $client->fetchAccessTokenWithAuthCode($authCode);

      // Store the credentials to disk.
      if(!file_exists(dirname($credentialsPath))) {
        mkdir(dirname($credentialsPath), 0700, true);
      }
      file_put_contents($credentialsPath, json_encode($accessToken));
      printf("Credentials saved to %s\n", $credentialsPath);
    }
    $client->setAccessToken($accessToken);

    // Refresh the token if it's expired.
    if ($client->isAccessTokenExpired()) {
      $client->fetchAccessTokenWithRefreshToken($client->getRefreshToken());
      file_put_contents($credentialsPath, json_encode($client->getAccessToken()));
    }
    return $client;
  }

}
