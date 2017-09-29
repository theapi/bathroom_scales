<?php
namespace Theapi\Datalogger;

use Google_Service_Sheets;
use Google_Service_Sheets_ValueRange;

define('APPLICATION_NAME', 'Google Sheets API');
define('CREDENTIALS_PATH', '.credentials/sheets.googleapis.com-php-bathroom_scales.json');
define('CLIENT_SECRET_PATH', '.credentials/bathroom_scales_client_secret.json');
// If modifying these scopes, delete the previously saved credentials
// at ~/.credentials/sheets.googleapis.com-php-bathroom_scales.json
define('SCOPES', implode(' ', array(
    Google_Service_Sheets::SPREADSHEETS)
));


class GoogleSheetsOutputHandler implements OutputHandlerInterface {

  /**
   * @var string
   */
  private $spreadsheetId;

  public function __construct($spreadsheet_id) {
    $this->spreadsheetId = $spreadsheet_id;
  }

  /**
   * @inheritdoc
   */
  public function write($data) {
    // Get the Google API client and construct the service object.
    $google_client = $this->getClient();
    $google_service = new Google_Service_Sheets($google_client);

    $this->updateSheet($google_service, $this->spreadsheetId, $data);
  }

  /**
   * Add data to the Google spreadsheet.
   *
   * @param Google_Service_Sheets $google_service
   * @param string $spreadsheetId
   * @param array $row_data
   *
   */
  public function updateSheet($google_service, $spreadsheetId, $row_data) {
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
    $client->setAuthConfig(CLIENT_SECRET_PATH);
    $client->setAccessType('offline');

    // Load previously authorized credentials from a file.
    $credentialsPath = $this->expandHomeDirectory(CREDENTIALS_PATH);
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

  /**
   * Expands the home directory alias '~' to the full path.
   * @param string $path the path to expand.
   * @return string the expanded path.
   */
  public function expandHomeDirectory($path) {
    $homeDirectory = getenv('HOME');
    if (empty($homeDirectory)) {
      $homeDirectory = getenv('HOMEDRIVE') . getenv('HOMEPATH');
    }
    return str_replace('~', realpath($homeDirectory), $path);
  }

}
