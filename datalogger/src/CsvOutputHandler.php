<?php
namespace Theapi\Datalogger;



class CsvOutputHandler implements OutputHandlerInterface {

  /**
   * @var Config
   */
  private $config;

  /**
   * @var PeopleInterface
   */
  private $people;

  public function __construct($config, PeopleInterface $people) {
    $this->config = $config;
    $this->people = $people;
  }

  /**
   * @inheritdoc
   */
  public function write($data) {
    $csv_file = $this->config->getValue('CSV_FILE');
    $row = $this->people->getPersonByWeight($data['weight'])
      . ','
      . $data['timestamp']
      . ','
      . $data['weight']
      . "\n";
    file_put_contents($csv_file, $row, FILE_APPEND);
  }

}
