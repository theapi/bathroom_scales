<?php

namespace Theapi\Datalogger;


class DataRow implements DataRowInterface {

  private $data = array();

  /**
   * @inheritDoc
   */
  public function setValue($key, $value) {
    $this->data[$key] = $value;

    return $this;
  }

  /**
   * @inheritDoc
   */
  public function getValue($key) {
    if (!isset($this->data[$key])) {
      throw new \InvalidArgumentException("DataRow value: $key is not set");
    }

    return $this->data[$key];
  }

  /**
   * @inheritDoc
   */
  public function toCSV() {
    // TODO: Implement toCSV() method.
  }

  /**
   * @inheritDoc
   */
  public function toString() {
    // TODO: Implement toString() method.
  }

}
