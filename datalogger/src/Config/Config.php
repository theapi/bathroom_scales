<?php

namespace Theapi\Datalogger\Config;


class Config implements ConfigInterface {

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
      throw new \InvalidArgumentException("Config value: $key is not set");
    }

    return $this->data[$key];
  }

}
