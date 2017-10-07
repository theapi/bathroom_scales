<?php
namespace Theapi\Datalogger;


/**
 * Class CsvOutputHandler
 *
 * @package Theapi\Datalogger
 */
class CsvOutputHandler implements OutputHandlerInterface {

  /**
   * @var Config
   */
  private $config;

  /**
   * CsvOutputHandler constructor.
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
    $csv_file = $this->config->getValue('CSV_FILE');
    $row = $data->person()
      . ','
      . $data->timestamp()
      . ','
      . $data->weight()
      . ','
      . $data->battery()
      . "\n";
    file_put_contents($csv_file, $row, FILE_APPEND);
  }

}
