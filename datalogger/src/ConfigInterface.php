<?php
namespace Theapi\Datalogger;

interface ConfigInterface {

  /**
   * Set a config value.
   * @param string $key
   *
   * @return self
   */
  public function setValue($key, $value);

  /**
   * Get a config value.
   *
   * @return string
   */
  public function getValue($key);
}
