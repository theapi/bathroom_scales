<?php
namespace Theapi\Datalogger\Output;

use Theapi\Datalogger\Data\DataRowInterface;


/**
 * Class CsvOutputHandler
 *
 * @package Theapi\Datalogger
 */
class CsvOutputHandler implements OutputHandlerInterface {

  /**
   * @var string The location of the csv file.
   */
  private $csv;

  /**
   * CsvOutputHandler constructor.
   *
   * @param $config
   */
  public function __construct($csv_file) {
    $this->csv = $csv_file;
  }

  /**
   * @inheritdoc
   */
  public function write(DataRowInterface $data) {
    $row = $data->person()
      . ','
      . $data->timestamp()
      . ','
      . $data->weight()
      . ','
      . $data->battery()
      . "\n";
    file_put_contents($this->csv, $row, FILE_APPEND);
  }

}
