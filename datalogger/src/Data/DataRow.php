<?php

namespace Theapi\Datalogger\Data;

/**
 * Class DataRow
 *
 * @package Theapi\Datalogger\Data
 */
class DataRow implements DataRowInterface {

  /**
   * @var array
   */
  private $data = array();

  /**
   * @inheritDoc
   */
  protected function setValue($key, $value) {
    $this->data[$key] = $value;

    return $this;
  }

  /**
   * @inheritDoc
   */
  protected function getValue($key) {
    if (!isset($this->data[$key])) {
      throw new \InvalidArgumentException("DataRow value: $key is not set");
    }

    return $this->data[$key];
  }

  /**
   * @inheritDoc
   */
  public function setBattery($value) {
    return $this->setValue('battery', $value);
  }

  /**
   * @inheritDoc
   */
  public function setPerson($value) {
    return $this->setValue('person', $value);
  }

  /**
   * @inheritDoc
   */
  public function setWeight($value) {
    return $this->setValue('weight', $value);
  }

  /**
   * @inheritDoc
   */
  public function setTimestamp() {
    return $this->setValue('timestamp', date('c'));
  }
  
  /**
   * @inheritDoc
   */
  public function battery() {
    return $this->getValue('battery');
  }

  /**
   * @inheritDoc
   */
  public function person() {
    return $this->getValue('person');
  }

  /**
   * @inheritDoc
   */
  public function weight() {
    return $this->getValue('weight');
  }

  /**
   * @inheritDoc
   */
  public function timestamp() {
    return $this->getValue('timestamp');
  }
  
}
